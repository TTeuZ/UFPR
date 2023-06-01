require "test_helper"

class StudentsSubjectsControllerTest < ActionDispatch::IntegrationTest
  setup do
    @students_subject = students_subjects(:one)
  end

  test "should get index" do
    get students_subjects_url
    assert_response :success
  end

  test "should get new" do
    get new_students_subject_url
    assert_response :success
  end

  test "should create students_subject" do
    assert_difference("StudentsSubject.count") do
      post students_subjects_url, params: { students_subject: { student_id: @students_subject.student_id, subject_id: @students_subject.subject_id } }
    end

    assert_redirected_to students_subject_url(StudentsSubject.last)
  end

  test "should show students_subject" do
    get students_subject_url(@students_subject)
    assert_response :success
  end

  test "should get edit" do
    get edit_students_subject_url(@students_subject)
    assert_response :success
  end

  test "should update students_subject" do
    patch students_subject_url(@students_subject), params: { students_subject: { student_id: @students_subject.student_id, subject_id: @students_subject.subject_id } }
    assert_redirected_to students_subject_url(@students_subject)
  end

  test "should destroy students_subject" do
    assert_difference("StudentsSubject.count", -1) do
      delete students_subject_url(@students_subject)
    end

    assert_redirected_to students_subjects_url
  end
end
