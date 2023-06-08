# frozen_string_literal: true

class Student < ApplicationRecord
  has_one :address, dependent: :destroy
  belongs_to :college, required: true
  has_and_belongs_to_many :subject, dependent: :destroy

  accepts_nested_attributes_for :address, allow_destroy: true
  validates :name, :age, :register, presence: true
end
