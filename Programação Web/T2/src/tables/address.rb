class Address<ActiveRecord::Base
    belongs_to :student, required: true

    # Validacoes
    validates :streat, :number, presence: true

    def tableView
        puts "#{self.id}|#{self.streat}|#{self.number}"
    end
end