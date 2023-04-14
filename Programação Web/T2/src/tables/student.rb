class Student<ActiveRecord::Base
    has_one :address, dependent: :destroy
    belongs_to :college
    has_and_belongs_to_many :subject, dependent: :destroy

    # Validacoes
    validates :name, :age, :register, presence: true
    validates_associated :address, :college
end