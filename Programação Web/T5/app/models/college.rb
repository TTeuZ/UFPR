class College < ApplicationRecord
    has_many :student, dependent: :destroy
    has_many :subject, dependent: :destroy

    validates :name, :c_type, presence: true
end
