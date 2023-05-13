// --------------------------------------------------------------------------------
//                                  variables
// --------------------------------------------------------------------------------

let students = [
    {
        name: "Aluno 0",
        grr: "GRR00000000",
        course: "BCC"
    },
    {
        name: "Aluno 1",
        grr: "GRR11111111",
        course: "BCC"
    },
    {
        name: "Aluno 2",
        grr: "GRR22222222",
        course: "BCC"
    },
    {
        name: "Aluno 3",
        grr: "GRR33333333",
        course: "BCC"
    },
    {
        name: "Aluno 4",
        grr: "GRR44444444",
        course: "BCC"
    }
]

let selectedStudent

// --------------------------------------------------------------------------------
//                                  functions
// --------------------------------------------------------------------------------

function loadJson(path) {
    const xhttp = new XMLHttpRequest();
    xhttp.open("GET", path, true);
    xhttp.send();

    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            // tratamento
        }
    };
}

function changeSelectedStudent(value) {
    selectedStudent = students.find(student => student.grr == value)
    setStudentInfo()
}

// --------------------------------------------------------------------------------
//                            HTML update functions
// --------------------------------------------------------------------------------

function setLoadedStudents() {
    const studentsSelector = document.querySelector('#students')
    let studentOptions = ""
    let temp

    selectedStudent = students[0]

    // Prenchimento do seletor
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

// --------------------------------------------------------------------------------
//                                     main
// --------------------------------------------------------------------------------

// loadJson("../data/students.json")
setLoadedStudents()
setStudentInfo()