class StudentsSubject < ApplicationRecord
  belongs_to :student, required: true
  belongs_to :subject, required: true
end
