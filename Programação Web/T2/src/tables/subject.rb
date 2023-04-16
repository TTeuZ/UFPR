class Subject<ActiveRecord::Base
    has_and_belongs_to_many :student, dependent: :destroy

    # Validacoes
    validates :name, :code, presence: true

    def tableView
        puts "#{self.id}|#{self.name}|#{self.code}"
    end
end