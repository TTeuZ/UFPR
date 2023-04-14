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

def treatCommand command
    teste = College.new (command['values'])

    puts teste.valid?
    
    # puts command.values
end