class College<ActiveRecord::Base
    has_many :student, dependent: :destroy

    # Validacoes
    validates :name, :type, presence: true
end