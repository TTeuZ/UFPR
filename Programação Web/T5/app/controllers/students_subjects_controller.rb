# frozen_string_literal: true

class StudentsSubjectsController < ApplicationController
  before_action :set_students_subject, only: %i[show edit update destroy]

  # GET /students_subjects or /students_subjects.json
  def index
    @students_subjects = StudentsSubject.all
  end

  # GET /students_subjects/1 or /students_subjects/1.json
  def show; end

  # GET /students_subjects/new
  def new
    @students_subject = StudentsSubject.new
  end

  # GET /students_subjects/1/edit
  def edit; end

  # POST /students_subjects or /students_subjects.json
  def create
    @students_subject = StudentsSubject.new(students_subject_params)

    respond_to do |format|
      if @students_subject.save
        format.html do
          redirect_to students_subject_url(@students_subject), notice: 'Students subject was successfully created.'
        end
        format.json { render :show, status: :created, location: @students_subject }
      else
        format.html { render :new, status: :unprocessable_entity }
        format.json { render json: @students_subject.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /students_subjects/1 or /students_subjects/1.json
  def update
    respond_to do |format|
      if @students_subject.update(students_subject_params)
        format.html do
          redirect_to students_subject_url(@students_subject), notice: 'Students subject was successfully updated.'
        end
        format.json { render :show, status: :ok, location: @students_subject }
      else
        format.html { render :edit, status: :unprocessable_entity }
        format.json { render json: @students_subject.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /students_subjects/1 or /students_subjects/1.json
  def destroy
    @students_subject.destroy

    respond_to do |format|
      format.html { redirect_to students_subjects_url, notice: 'Students subject was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private

  # Use callbacks to share common setup or constraints between actions.
  def set_students_subject
    @students_subject = StudentsSubject.find(params[:id])
  end

  # Only allow a list of trusted parameters through.
  def students_subject_params
    params.require(:students_subject).permit(:student_id, :subject_id)
  end
end
