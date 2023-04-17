require 'rubygems'
require 'active_record'

# Funcionais
require_relative 'src/commandHandler'
require_relative 'src/createDatabase'
require_relative 'src/inputHandler'

# Tabelas
require_relative 'src/tables/address'
require_relative 'src/tables/college'
require_relative 'src/tables/student'
require_relative 'src/tables/subject'
require_relative 'src/tables/students_subjects'

# Seeder
require_relative 'src/seeds/seeder'

def commands
    %w[insere altera exclui lista]
end

def commandsThatNeedValues
    %w[altera exclui]
end

def tables
    %w[addresses colleges students subjects students_subjects]
end

def models
    %w[Address College Student Subject StudentsSubjects]
end

# variaveis
input = ''
error = []
command = {}

lineWidth = 100

puts '#' * lineWidth
puts '#' + ' '.center(lineWidth - 2) + '#'

puts '#' + 'Interface de acesso ao Banco de Dados'.center(lineWidth - 2) + '#'
puts '#' + ' '.center(lineWidth - 2) + '#'
puts '#' + '      Modelo de requisição:'.ljust(lineWidth - 2) + '#'
puts '#' + ' '.center(lineWidth - 2) + '#'
puts '#' + '      < operação > < tabela > { atributo = valor }'.ljust(lineWidth - 2) + '#'
puts '#' + ' '.center(lineWidth - 2) + '#'
puts '#' + '      - < operação > pode ser "insere", "altera", "exclui", "lista";'.ljust(lineWidth - 2) + '#'
puts '#' + '      - < tabela > indica o nome da tabela (addresses, colleges, students, subjects);'.ljust(lineWidth - 2) + '#'
puts '#' + '      - atributo = valor indica o valor do atributo envolvido na operação (0..n valores);'.ljust(lineWidth - 2) + '#'
puts '#' + '      - {...} indica repetição, os colchetes não devem ser adicionados.'.ljust(lineWidth - 2) + '#'
puts '#' + ' '.center(lineWidth - 2) + '#'
puts '#' + '      Exemplos:'.ljust(lineWidth - 2) + '#'
puts '#' + '      - insere colleges name="UFPR" type="publica"'.ljust(lineWidth - 2) + '#'
puts '#' + '      - lista colleges'.ljust(lineWidth - 2) + '#'
puts '#' + '      - exclui colleges name="PUC"'.ljust(lineWidth - 2) + '#'
puts '#' + ' '.center(lineWidth - 2) + '#'
puts '#' + '      Comando uteis:'.ljust(lineWidth - 2) + '#'
puts '#' + '      - schema: retorna o schema da tabela (copiado do sqlite3);'.ljust(lineWidth - 2) + '#'
puts '#' + '      - exit: sai do programa.'.ljust(lineWidth - 2) + '#'

puts '#' + ' '.center(lineWidth - 2) + '#'
puts '#' * lineWidth
puts

puts 'Insira um comando:'
input = gets.chomp

while command != 'exit'
    case command
    when 'schema'
        showSchema
    else
        command = treatInput input
        if command != nil
            error = verifyCommandAndTable command

            if error == []
                treatCommand command
            else
                puts error
            end
        else
            puts "Por favor, insira valores em formatos validos!"
        end
    end

    puts "\nInsira um comando:"
    input = gets.chomp
end