class College<ActiveRecord::Base
    has_many :student, dependent: :destroy

    # Validacoes
    validates :name, :c_type, presence: true

    def tableView
        puts "#{self.id}|#{self.name}|#{self.c_type}"
    end

    def printInfo(space: '')
        puts "#{space}Faculdade id: #{self.id}"
        puts "#{space}Nome: #{self.name}"
        puts "#{space}tipo: #{self.c_type}"

        puts "\n#{space}\tEstudantes:"
        self.student.find_each { |obj| obj.printInfo(space: "#{space}\t") }
    end
end