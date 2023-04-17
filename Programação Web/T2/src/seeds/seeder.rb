# College
seedColleges = [
    {name: "UFPR", c_type: "Publica"},
    {name: "UFRJ", c_type: "Publica"},
    {name: "PUC", c_type: "Privada"},
    {name: "Uninter", c_type: "Privada"}
]

# Student
seedStudents = [
    {name: "Paulo Mateus Luza Alves", age: "22", register: "GRR20203945", college_id: "1"},
    {name: "Luis", age: "22", register: "GRR20200001", college_id: "1"},
    {name: "Ariel", age: "22", register: "GRR20200002", college_id: "2"},
    {name: "Fernanda", age: "22", register: "GRR20200003", college_id: "2"},
    {name: "Heric", age: "22", register: "GRR20200004", college_id: "3"},
    {name: "Claudinei", age: "22", register: "GRR20200005", college_id: "3"},
    {name: "Guilherme", age: "22", register: "GRR20200006", college_id: "4"}
]

# Addresses
seedAddresses = [
    {streat: "Rua teste um", number: "11", student_id: "1"},
    {streat: "Rua teste dois", number: "22", student_id: "2"},
    {streat: "Rua teste tres", number: "33", student_id: "3"},
    {streat: "Rua teste quatro", number: "44", student_id: "4"},
    {streat: "Rua teste cinco", number: "55", student_id: "5"},
    {streat: "Rua teste seis", number: "66", student_id: "6"},
    {streat: "Rua teste sete", number: "77", student_id: "7"}
]

seedSubjects = [
    {name: "Matéria 1", code: "CI11"},
    {name: "Matéria 2", code: "CI22"},
    {name: "Matéria 3", code: "CI33"},
    {name: "Matéria 4", code: "CI44"},
    {name: "Matéria 5", code: "CI55"},
    {name: "Matéria 6", code: "CI66"},
    {name: "Matéria 7", code: "CI77"}
]

seedStudentsSubjects = [
    {student_id: "1", subject_id: "1"},
    {student_id: "1", subject_id: "2"},
    {student_id: "1", subject_id: "5"},
    {student_id: "2", subject_id: "3"},
    {student_id: "2", subject_id: "2"},
    {student_id: "2", subject_id: "1"},
    {student_id: "2", subject_id: "7"},
    {student_id: "3", subject_id: "7"},
    {student_id: "3", subject_id: "6"},
    {student_id: "3", subject_id: "5"},
    {student_id: "4", subject_id: "3"},
    {student_id: "4", subject_id: "1"},
    {student_id: "5", subject_id: "2"},
    {student_id: "6", subject_id: "2"},
    {student_id: "6", subject_id: "7"},
    {student_id: "6", subject_id: "6"},
    {student_id: "7", subject_id: "2"},
    {student_id: "7", subject_id: "3"}
]

for sCollege in seedColleges do
    College.find_or_create_by(sCollege)
end

for sStudent in seedStudents do
    Student.find_or_create_by(sStudent)
end

for sAddress in seedAddresses do
    Address.find_or_create_by(sAddress)
end

for sSubjects in seedSubjects do
    Subject.find_or_create_by(sSubjects)
end

for sStudentSubject in seedStudentsSubjects do
    StudentsSubjects.find_or_create_by(sStudentSubject)
end