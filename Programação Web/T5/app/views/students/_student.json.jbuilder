# frozen_string_literal: true

json.extract! student, :id, :name, :age, :register, :college_id, :created_at, :updated_at
json.url student_url(student, format: :json)
