// --------------------------------------------------------------------------------
//                                  variables
// --------------------------------------------------------------------------------

let subjects
let students
let selectedStudent

// --------------------------------------------------------------------------------
//                         Student/subejects functions
// --------------------------------------------------------------------------------
function setStatus(status) {
    let temp
    switch (status) {
        case 'Aprovado':
        case 'Dispensa de Disciplinas (com nota)':
            temp = 'approved'
            break
        case 'Equivalência de Disciplina':
            temp = 'equivalence'
            break
        case 'Reprovado por nota':
        case 'Reprovado por Frequência':
            temp = 'unapproved'
            break
        case 'Cancelado':
            temp = 'canceled'
            break
        case 'Matrícula':
            temp = 'registered'
            break
        case 'Trancamento Administrativo':
        case 'Trancamento Total':
            temp = 'locked'
            break
    }

    return temp
}

function addSubject(student, item) {
    let tempSubject

    tempSubject = {
        name: item.NOME_ATIV_CURRIC,
        code: item.COD_ATIV_CURRIC,
        status: item.SITUACAO,
        innerStatus: setStatus(item.SITUACAO),
        frequency: item.FREQUENCIA,
        type: item.DESCR_ESTRUTURA,
        totalOfHours: item.CH_TOTAL,
        semester: item.PERIODO,
        finalGrade: item.MEDIA_FINAL,
        year: item.ANO
    }

    student.subjects.push(tempSubject)
}

function createStudent(item) {
    let tempStudent, tempSubject

    tempStudent = {
        id: item.ID_CURSO_ALUNO,
        name: item.NOME_ALUNO,
        grr: item.MATR_ALUNO,
        course: item.NOME_CURSO,
        subjects: []
    }
    addSubject(tempStudent, item)

    return tempStudent
}

function createSubject(item) {
    let tempSubject
    tempSubject = {
        name: item.NOME_ATIV_CURRIC,
        code: item.COD_ATIV_CURRIC,
        type: item.DESCR_ESTRUTURA,
        totalOfHours: item.CH_TOTAL,
    }

    return tempSubject
}

// --------------------------------------------------------------------------------
//                               Main functions
// --------------------------------------------------------------------------------

function loadJson(path) {
    const xhttp = new XMLHttpRequest();
    let temp

    xhttp.open("GET", path, true);
    xhttp.send();

    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            temp = JSON.parse(xhttp.responseText)

            treatJson(temp)
            setLoadedStudents()
            setStudentInfo()
            setStudentTable()
        }
    };
}

function treatJson(json) {
    let temp, localSubjects, localStudents, tempStudent, tempSubject

    temp = json.DATA.ALUNO
    localStudents = []
    localSubjects = []

    temp.forEach(item => {
        tempStudent = localStudents.find(student => student.grr == item.MATR_ALUNO)
        if (tempStudent == undefined) {
            tempStudent = createStudent(item)
            localStudents.push(tempStudent)
        } else {
            addSubject(tempStudent, item)
        }

        tempSubject = localSubjects.find(subject => subject.code == item.COD_ATIV_CURRIC)
        if (tempSubject == undefined) {
            tempSubject = createSubject(item)
            localSubjects.push(tempSubject)
        }
    })

    students = localStudents
    subjects = localSubjects
    selectedStudent = students[0]
}

function cleanHTML() {
    const studentInfo = document.querySelector('#studentInfo')
    const history = document.querySelector('#history')
    const grade = document.querySelector('#grade')

    studentInfo.innerHTML = ''
    history.innerHTML = ''
    grade.innerHTML = ''
}

function changeSelectedStudent(value) {
    selectedStudent = students.find(student => student.grr == value)
    cleanHTML()
    setStudentInfo()
    setStudentTable()
}

function showPopUp(code) {
    let tempSubject

    tempSubject = selectedStudent.subjects.findLast(s => s.code == code)

    alert(
        `${tempSubject.code} - ${tempSubject.name} \nAno/Semestre: ${tempSubject.year}/${tempSubject.semester} \nNota: ${tempSubject.finalGrade} \nFrequência: ${tempSubject.frequency}`
    )
}

// --------------------------------------------------------------------------------
//                            HTML update functions
// --------------------------------------------------------------------------------

function setLoadedStudents() {
    const studentsSelector = document.querySelector('#students')
    let studentOptions, temp

    // Prenchimento do seletor
    studentOptions = ""
    students.forEach(student => {
        temp = `<option value="${student.grr}">
                    ${student.name} - ${student.grr}
                </option>`
        studentOptions += temp
    })
    studentsSelector.innerHTML = studentOptions
}

function setStudentInfo() {
    const studentInfo = document.querySelector('#studentInfo')
    let temp

    temp = `
        <div class="d-flex flex-row mt-3">
            <span class="me-3"> Nome: ${selectedStudent.name} </span>
            <span> GRR: ${selectedStudent.grr} </span>
        </div>
    `
    studentInfo.innerHTML = temp
}

function showHistory(code) {
    const history = document.querySelector('#history')
    let subjects, temp

    subjects = selectedStudent.subjects.filter(s => s.code == code)

    temp = `<h4> Histórico de ${subjects[0].code}: </h4>`
    temp += `<span> Nome: ${subjects[0].name} </span>`
    temp += '<div class="history__wrapper">'
    subjects.forEach((subject, index) => {
        temp += `<div class="d-flex flex-column history__cell ${index != (subjects.length - 1) ? 'divisor' : ''}">`
        temp += `<span>${index + 1}° vez</span>`
        temp += `<span>Ano: ${subject.year}</span>`
        temp += `<span>Semestre: ${subject.semester}</span>`
        temp += `<span>Nota final: ${subject.finalGrade}</span>`
        temp += `<span>Frequência: ${subject.frequency}</span>`
        temp += '</div>'
    })
    temp += '</div>'

    history.innerHTML = temp
}

function setStudentTable() {
    const grade = document.querySelector('#grade')
    const numCols = 8
    let gradeStruct, tempSubject

    gradeStruct = "<tr>"
    subjects.forEach((subject, index) => {
        tempSubject = selectedStudent.subjects.findLast(s => s.code == subject.code)
        if (tempSubject == undefined)
            gradeStruct += `<td class="grade__cell ditNotAttended"><span> ${subject.code} </span></td>`
        else
            gradeStruct += `<td class="grade__cell ${tempSubject.innerStatus}" oncontextmenu="showPopUp('${subject.code}')" onclick="showHistory('${subject.code}')"><span> ${tempSubject.code} </span></td>`

        if (index % numCols == 7)
            gradeStruct += "</tr><tr>"
    })

    gradeStruct += "</tr>"
    grade.innerHTML = gradeStruct
}
// --------------------------------------------------------------------------------
//                                     main
// --------------------------------------------------------------------------------

loadJson("../data/students.json")