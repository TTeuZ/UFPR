class College<ActiveRecord::Base
    has_many :student, dependent: :destroy

    # Validacoes
    validates :name, :c_type, presence: true

    def tableView
        puts "#{self.id}|#{self.name}|#{self.c_type}"
    end
end