class Student<ActiveRecord::Base
    has_one :address, dependent: :destroy
    belongs_to :college, required: true
    has_and_belongs_to_many :subject, dependent: :destroy

    # Validacoes
    validates :name, :age, :register, presence: true

    def tableView
        puts "#{self.id}|#{self.name}|#{self.age}|#{self.register}"
    end

    def printInfo(space: '')
        puts "#{space}Estudante id: #{self.id}"
        puts "#{space}Nome: #{self.name}"
        puts "#{space}Idade: #{self.age}"
        puts "#{space}Registro: #{self.register}"

        if self.address != nil
            puts "\n#{space}\tEndereço:"
            self.address.printInfo(space: "#{space}\t")
        end

        if self.subject != nil
            puts "\n#{space}\t\tMatérias:"
            self.subject.find_each { |obj| obj.printInfo(space: "#{space}\t\t") }
        end
    end
end