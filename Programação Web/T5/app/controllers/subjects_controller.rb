# frozen_string_literal: true

class SubjectsController < ApplicationController
  before_action :set_subject, only: %i[show edit update destroy]
  before_action :authenticate_user!

  # GET /subjects or /subjects.json
  def index
    @subjects = Subject.all
  end

  # GET /subjects/1 or /subjects/1.json
  def show; end

  # GET /subjects/new
  def new
    @subject = Subject.new
  end

  # GET /subjects/1/edit
  def edit; end

  # POST /subjects or /subjects.json
  def create
    @subject = Subject.new(subject_params)

    respond_to do |format|
      if @subject.save
        format.html { redirect_to subjects_url, notice: 'Materia adicionada com sucesso!' }
        format.json { render action: 'index', status: :created, location: @subject }
      else
        format.html { render :new, status: :unprocessable_entity }
        format.json { render json: @subject.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /subjects/1 or /subjects/1.json
  def update
    respond_to do |format|
      if @subject.update(subject_params)
        format.html { redirect_to subjects_url, notice: 'Materia atualizada com sucesso!' }
        format.json { render action: 'index', status: :ok, location: @subject }
      else
        format.html { render :edit, status: :unprocessable_entity }
        format.json { render json: @subject.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /subjects/1 or /subjects/1.json
  def destroy
    @subject.destroy

    respond_to do |format|
      format.html { redirect_to subjects_url, notice: 'Materia apagada com sucesso!' }
      format.json { head :no_content }
    end
  end

  private

  # Use callbacks to share common setup or constraints between actions.
  def set_subject
    @subject = Subject.find(params[:id])
  end

  # Only allow a list of trusted parameters through.
  def subject_params
    params.require(:subject).permit(:name, :code)
  end
end
