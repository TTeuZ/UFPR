# frozen_string_literal: true

class Subject < ApplicationRecord
  has_and_belongs_to_many :student, dependent: :destroy

  # Validacoes
  validates :name, :code, presence: true
end
