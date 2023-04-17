class Address<ActiveRecord::Base
    belongs_to :student, required: true

    # Validacoes
    validates :streat, :number, presence: true

    def tableView
        puts "#{self.id}|#{self.streat}|#{self.number}"
    end

    def printInfo(space: '')
        if space == "" 
            puts ""
        end
        puts "#{space}Endereço Id: #{self.id}"
        puts "#{space}Endereço: #{self.streat}, #{self.number}"
    end
end