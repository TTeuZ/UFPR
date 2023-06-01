# frozen_string_literal: true

json.array! @students_subjects, partial: 'students_subjects/students_subject', as: :students_subject
