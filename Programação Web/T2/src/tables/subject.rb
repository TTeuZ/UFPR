class Subject<ActiveRecord::Base
    has_and_belongs_to_many :student, dependent: :destroy

    # Validacoes
    validates :name, :code, presence: true
end