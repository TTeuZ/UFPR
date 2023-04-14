class Address<ActiveRecord::Base
    belongs_to :student

    # Validacoes
    validates :country, :state, :city, :streat, :number, presence: true
end