# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the bin/rails db:seed command (or created alongside the database with db:setup).
#
# Examples:
#
#   movies = Movie.create([{ name: "Star Wars" }, { name: "Lord of the Rings" }])
#   Character.create(name: "Luke", movie: movies.first)

# College
colleges = College.create([
    {name: "UFPR", c_type: "Publica"},
    {name: "UFRJ", c_type: "Publica"},
    {name: "PUC", c_type: "Privada"},
    {name: "Uninter", c_type: "Privada"}
])

# Student
seedStudents = Student.create([
    {name: "Paulo Mateus Luza Alves", age: "22", register: "GRR20203945", college_id: "1"},
    {name: "Luis", age: "22", register: "GRR20200001", college_id: "1"},
    {name: "Ariel", age: "22", register: "GRR20200002", college_id: "2"},
    {name: "Fernanda", age: "22", register: "GRR20200003", college_id: "2"},
    {name: "Heric", age: "22", register: "GRR20200004", college_id: "3"},
    {name: "Claudinei", age: "22", register: "GRR20200005", college_id: "3"},
    {name: "Guilherme", age: "22", register: "GRR20200006", college_id: "4"}
])

# Addresses
seedAddresses = Address.create([
    {streat: "Rua teste um", number: "11", student_id: "1"},
    {streat: "Rua teste dois", number: "22", student_id: "2"},
    {streat: "Rua teste tres", number: "33", student_id: "3"},
    {streat: "Rua teste quatro", number: "44", student_id: "4"},
    {streat: "Rua teste cinco", number: "55", student_id: "5"},
    {streat: "Rua teste seis", number: "66", student_id: "6"},
    {streat: "Rua teste sete", number: "77", student_id: "7"}
])

seedSubjects = Subject.create([
    {name: "Matéria 1", code: "CI11"},
    {name: "Matéria 2", code: "CI22"},
    {name: "Matéria 3", code: "CI33"},
    {name: "Matéria 4", code: "CI44"},
    {name: "Matéria 5", code: "CI55"},
    {name: "Matéria 6", code: "CI66"},
    {name: "Matéria 7", code: "CI77"}
])

seedStudentsSubjects = StudentsSubject.create([
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
])
