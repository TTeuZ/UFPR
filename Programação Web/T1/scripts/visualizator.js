// --------------------------------------------------------------------------------
//                                  variables
// --------------------------------------------------------------------------------

let students
let selectedStudent

let subjects = [
    'CI068', 'CI210', 'CI212', 'CI215', 'CI162', 'CI163', 'CI221', 'OPT',
    'CI055', 'CI056', 'CI057', 'CI062', 'CI065', 'CI165', 'CI211', 'OPT',
    'CM046', 'CI067', 'CI064', 'CE003', 'CI059', 'CI209', 'OPT', 'OPT',
    'CM045', 'CM005', 'CI237', 'CI058', 'CI061', 'CI218', 'OPT', 'OPT',
    'CM201', 'CM202', 'CI166', 'CI164', 'SA214', 'CI220', 'TG I', 'TG II'
]

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
    let tempStudent

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

function getTCC() {
    return {
        tcc1: selectedStudent.subjects.findLast(s => s.type == 'Trabalho de Graduação I'),
        tcc2: selectedStudent.subjects.findLast(s => s.type == 'Trabalho de Graduação II')
    }
}

function getOpt() {
    let temp

    temp = selectedStudent.subjects.filter(s => s.type == 'Optativas')
    return temp.slice(0, 6).toReversed()
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
    let temp, localStudents, tempStudent, tempSubject

    temp = json.DATA.ALUNO
    localStudents = []

    temp.forEach(item => {
        tempStudent = localStudents.find(student => student.grr == item.MATR_ALUNO)
        if (tempStudent == undefined) {
            tempStudent = createStudent(item)
            localStudents.push(tempStudent)
        } else {
            addSubject(tempStudent, item)
        }
    })

    students = localStudents
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
    let gradeStruct, temp, tempSubject, tempTCC, tempOpt, count

    gradeStruct = "<tr>"
    for (count = 1; count <= numCols; ++count)
        gradeStruct += `<td class="grade__cell grade_header__cell ${count <= 3 ? 'approved' : 'unapproved'}">${count}°</td>`
    gradeStruct += "</tr>"

    gradeStruct += '<tr class="header_divisor__wrapper">'
    for (count = 1; count <= numCols; ++count)
        gradeStruct += `<td class="header__divisor"></td>`
    gradeStruct += "</tr><tr>"

    tempTCC = getTCC()
    tempOpt = getOpt()

    subjects.forEach((subject, index) => {
        tempSubject = selectedStudent.subjects.findLast(s => s.code == subject)
        if (tempSubject == undefined) {
            switch (subject) {
                case 'OPT':
                    temp = tempOpt.pop()
                    if (temp != undefined)
                        gradeStruct += `<td class="grade__cell pointer ${temp.innerStatus}" oncontextmenu="showPopUp('${temp.code}')" onclick="showHistory('${temp.code}')"><span> ${temp.code} </span></td>`
                    else
                        gradeStruct += `<td class="grade__cell ditNotAttended"><span> ${subject} </span></td>`
                    break
                case 'TG I':
                    if (tempTCC.tcc1 != undefined)
                        gradeStruct += `<td class="grade__cell pointer ${tempTCC.tcc1.innerStatus}" oncontextmenu="showPopUp('${tempTCC.tcc1.code}')" onclick="showHistory('${tempTCC.tcc1.code}')"><span> ${tempTCC.tcc1.code} </span></td>`
                    else
                        gradeStruct += `<td class="grade__cell ditNotAttended"><span> ${subject} </span></td>`
                    break
                case 'TG II':
                    if (tempTCC.tcc2 != undefined)
                        gradeStruct += `<td class="grade__cell pointer ${tempTCC.tcc2.innerStatus}" oncontextmenu="showPopUp('${tempTCC.tcc2.code}')" onclick="showHistory('${tempTCC.tcc2.code}')"><span> ${tempTCC.tcc2.code} </span></td>`
                    else
                        gradeStruct += `<td class="grade__cell ditNotAttended"><span> ${subject} </span></td>`
                    break
                default:
                    gradeStruct += `<td class="grade__cell ditNotAttended"><span> ${subject} </span></td>`
                    break
            }
        } else
            gradeStruct += `<td class="grade__cell pointer ${tempSubject.innerStatus}" oncontextmenu="showPopUp('${subject}')" onclick="showHistory('${subject}')"><span> ${subject} </span></td>`

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