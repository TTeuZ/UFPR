class Address < ApplicationRecord
  belongs_to :student, required: true

  validates :streat, :number, presence: true
end
