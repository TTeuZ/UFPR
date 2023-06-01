# frozen_string_literal: true

require 'application_system_test_case'

class StudentsSubjectsTest < ApplicationSystemTestCase
  setup do
    @students_subject = students_subjects(:one)
  end

  test 'visiting the index' do
    visit students_subjects_url
    assert_selector 'h1', text: 'Students subjects'
  end

  test 'should create students subject' do
    visit students_subjects_url
    click_on 'New students subject'

    fill_in 'Student', with: @students_subject.student_id
    fill_in 'Subject', with: @students_subject.subject_id
    click_on 'Create Students subject'

    assert_text 'Students subject was successfully created'
    click_on 'Back'
  end

  test 'should update Students subject' do
    visit students_subject_url(@students_subject)
    click_on 'Edit this students subject', match: :first

    fill_in 'Student', with: @students_subject.student_id
    fill_in 'Subject', with: @students_subject.subject_id
    click_on 'Update Students subject'

    assert_text 'Students subject was successfully updated'
    click_on 'Back'
  end

  test 'should destroy Students subject' do
    visit students_subject_url(@students_subject)
    click_on 'Destroy this students subject', match: :first

    assert_text 'Students subject was successfully destroyed'
  end
end
