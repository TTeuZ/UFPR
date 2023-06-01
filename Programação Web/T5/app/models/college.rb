# frozen_string_literal: true

class College < ApplicationRecord
  has_many :student, dependent: :destroy

  validates :name, :c_type, presence: true
end
