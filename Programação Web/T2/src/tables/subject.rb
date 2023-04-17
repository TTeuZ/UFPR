class Subject<ActiveRecord::Base
    has_and_belongs_to_many :student, dependent: :destroy

    # Validacoes
    validates :name, :code, presence: true

    def tableView
        puts "#{self.id}|#{self.name}|#{self.code}"
    end

    def printInfo(space: '')
        puts "#{space}Matéria id: #{self.id}"
        puts "#{space}Nome: #{self.name}"
        puts "#{space}Código: #{self.code}"
        puts ""
    end
end