def showSchema
    puts
    puts 'CREATE TABLE IF NOT EXISTS "colleges" ("id" integer PRIMARY KEY AUTOINCREMENT NOT NULL, "name" varchar, "type" varchar);'
    puts 'CREATE TABLE sqlite_sequence(name,seq);'
    puts 'CREATE TABLE IF NOT EXISTS "students" ("id" integer PRIMARY KEY AUTOINCREMENT NOT NULL, "name" varchar, "age" integer, "register" varchar, "college_id" integer, CONSTRAINT "fk_rails_1d4ff93d0b"'
    puts 'FOREIGN KEY ("college_id")'
    puts '  REFERENCES "colleges" ("id")'
    puts ');'
    puts 'CREATE INDEX "index_students_on_college_id" ON "students" ("college_id");'
    puts 'CREATE TABLE IF NOT EXISTS "adresses" ("id" integer PRIMARY KEY AUTOINCREMENT NOT NULL, "country" varchar, "state" varchar, "city" varchar, "streat" varchar, "number" integer, "student_id" integer, CONSTRAINT "fk_rails_6b75d5575f"'
    puts 'FOREIGN KEY ("student_id")'
    puts '  REFERENCES "students" ("id")'
    puts ');'
    puts 'CREATE INDEX "index_adresses_on_student_id" ON "adresses" ("student_id");'
    puts 'CREATE TABLE IF NOT EXISTS "subjects" ("id" integer PRIMARY KEY AUTOINCREMENT NOT NULL, "name" varchar, "code" varchar);'
    puts 'CREATE TABLE IF NOT EXISTS "students_subjects" ("student_id" integer, "subject_id" integer);'
    puts 'CREATE INDEX "index_students_subjects_on_student_id" ON "students_subjects" ("student_id");'
    puts 'CREATE INDEX "index_students_subjects_on_subject_id" ON "students_subjects" ("subject_id");'
    puts
end

def treatCommand input
    treatedInput = {}
    inputSplited = []
    valueTemp = []
    temp = ''

    inputSplited = input.split(/ /, 3)
    treatedInput['command'] = inputSplited[0]
    treatedInput['table'] = inputSplited[1]
    temp = inputSplited[2]

    if temp != nil
    temp = temp.gsub /( |(".*?"))/, "\\2-"
        temp = temp.split('"--')

        treatedInput['values'] = {}
        for value in temp do
            valueTemp = value.delete!('"-').split('=')
            treatedInput['values'][valueTemp[0]] = valueTemp[1]
        end
    end

    treatedInput
end

def verifyCommandAndTable command
    commands = ['insere', 'altera', 'exclui', 'lista']
    tables = ['addresses', 'colleges', 'students', 'subjects']
    error = []

    if not commands.include? command['command']
        error.push('Por favor, insira um comando valido')
    end
    if not tables.include? command['table']
        error.push('Por favor, insira uma tabela valida')
    end

    error
end