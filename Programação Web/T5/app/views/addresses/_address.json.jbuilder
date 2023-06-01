# frozen_string_literal: true

json.extract! address, :id, :streat, :number, :student_id, :created_at, :updated_at
json.url address_url(address, format: :json)
