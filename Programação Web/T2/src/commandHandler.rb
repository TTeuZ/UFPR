def verifyCommandAndTable command
    error = []

    if !commands.include? command['command']
        error.push('Por favor, insira um comando valido')
    end
    if !tables.include? command['table']
        error.push('Por favor, insira uma tabela valida')
    end
    if commandsThatNeedValues.include?(command['command']) && (command['values'] == nil)
        error.push('Por favor, informe o valor para busca')
    end

    error
end

def treatCommand command
    selectedTable = models.find { |model| model.constantize.table_name == command['table'] }
    selectedTable = selectedTable.constantize

    case command['command']
    when 'insere'
        insertHandler(table: selectedTable, command: command)
    when 'altera'
        updateHandler(table: selectedTable, command: command)
    when 'exclui'
        deleteHandler(table: selectedTable, command: command)
    when 'lita'
        listHandler(table: selectedTable, command: command)
    end
end

def insertHandler (table:, command:)
    begin
        object = table.new (command['values'])
        if !object.valid?
            for error in object.errors.objects do
                puts error.full_message
            end
        else
            puts "adicionado com sucesso! \n"
        end

        object.save
    rescue => exception
        puts exception
    end
end

def updateHandler (table:, command:)
    index = 0
    begin
        objects = table.where(command['values'])
        if objects.size != 0 
            if objects.size > 1 
                puts "Existe mais de uma opção para atualizar, qual delas você deseja fazer a alteração?"
                for obj in objects do
                    obj.tableView
                end
                index = gets.chomp.to_i - 1
            end

            if index >= 0 && index <= (objects.size - 1)
                puts "Quais valores você deseja alterar?"
                updateString = gets.chomp
                updateHash = treatUpdateString updateString
        
                objects[index].update(updateHash)
                puts "Atualização Executada com sucesso!"
            else
                puts "Tupla selecionada não existe!"
            end
        else
            puts "Nenhuma tupla registrada!"
        end
    rescue => exception
        puts exception
    end
end

def updateHandler (table:, command:)
    index = 0
    begin
        objects = table.where(command['values'])
        if objects.size != 0 
            if objects.size > 1 
                puts "Existe mais de uma opção para atualizar, qual delas você deseja fazer a alteração?"
                for obj in objects do
                    obj.tableView
                end
                index = gets.chomp.to_i - 1
            end

            if index >= 0 && index <= (objects.size - 1)
                puts "Quais valores você deseja alterar?"
                updateString = gets.chomp
                updateHash = treatUpdateString updateString
        
                objects[index].update(updateHash)
                puts "Atualização Executada com sucesso!"
            else
                puts "Tupla selecionada não existe!"
            end
        else
            puts "Nenhuma tupla registrada!"
        end
    rescue => exception
        puts exception
    end
end