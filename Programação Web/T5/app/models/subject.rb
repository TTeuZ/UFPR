class Subject < ApplicationRecord
  has_and_belongs_to_many :student, dependent: :destroy
  belongs_to :college, required: true

  validates :name, :code, presence: true
end
