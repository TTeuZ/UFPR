class Student<ActiveRecord::Base
    has_one :address, dependent: :destroy
    belongs_to :college, required: true
    has_and_belongs_to_many :subject, dependent: :destroy

    # Validacoes
    validates :name, :age, :register, presence: true
    def tableView
        puts "#{self.id}|#{self.name}|#{self.age}|#{self.register}"
    end
end