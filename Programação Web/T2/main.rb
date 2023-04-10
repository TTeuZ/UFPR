require 'rubygems'
require 'active_record'

# Funcionais
require_relative 'src/createDatabase'
require_relative 'src/commandHandler'

# Tabelas
require_relative 'src/tables/address'
require_relative 'src/tables/college'
require_relative 'src/tables/student'
require_relative 'src/tables/subject'

# variaveis
command = ''
error = []
treatedCommand = {}

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

puts 'Insera um comando:'
command = gets.chomp

while command != 'exit'
    case command
    when 'schema'
        showSchema
    else
        treatedCommand = treatCommand command
        error = verifyCommandAndTable treatedCommand

        if error == []
            puts 'valido'
        else
            puts error
        end
    end

    puts 'Insera um comando:'
    command = gets.chomp
end