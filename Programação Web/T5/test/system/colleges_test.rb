require "application_system_test_case"

class CollegesTest < ApplicationSystemTestCase
  setup do
    @college = colleges(:one)
  end

  test "visiting the index" do
    visit colleges_url
    assert_selector "h1", text: "Colleges"
  end

  test "should create college" do
    visit colleges_url
    click_on "New college"

    fill_in "C type", with: @college.c_type
    fill_in "Name", with: @college.name
    click_on "Create College"

    assert_text "College was successfully created"
    click_on "Back"
  end

  test "should update College" do
    visit college_url(@college)
    click_on "Edit this college", match: :first

    fill_in "C type", with: @college.c_type
    fill_in "Name", with: @college.name
    click_on "Update College"

    assert_text "College was successfully updated"
    click_on "Back"
  end

  test "should destroy College" do
    visit college_url(@college)
    click_on "Destroy this college", match: :first

    assert_text "College was successfully destroyed"
  end
end
