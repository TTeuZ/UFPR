# frozen_string_literal: true

class Student < ApplicationRecord
  has_one :address, dependent: :destroy
  belongs_to :college, required: true
  has_and_belongs_to_many :subject, dependent: :destroy

  validates :name, :age, :register, presence: true
end
