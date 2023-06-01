# frozen_string_literal: true

class Address < ApplicationRecord
  belongs_to :student, required: true

  validates :streat, :number, presence: true
end
