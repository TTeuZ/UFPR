# frozen_string_literal: true

class CollegesController < ApplicationController
  before_action :set_college, only: %i[show edit update destroy]

  # GET /colleges or /colleges.json
  def index
    @colleges = College.all
  end

  # GET /colleges/1 or /colleges/1.json
  def show; end

  # GET /colleges/new
  def new
    @college = College.new
  end

  # GET /colleges/1/edit
  def edit; end

  # POST /colleges or /colleges.json
  def create
    @college = College.new(college_params)

    respond_to do |format|
      if @college.save
        format.html { redirect_to college_url(@college), notice: 'College was successfully created.' }
        format.json { render :show, status: :created, location: @college }
      else
        format.html { render :new, status: :unprocessable_entity }
        format.json { render json: @college.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /colleges/1 or /colleges/1.json
  def update
    respond_to do |format|
      if @college.update(college_params)
        format.html { redirect_to college_url(@college), notice: 'College was successfully updated.' }
        format.json { render :show, status: :ok, location: @college }
      else
        format.html { render :edit, status: :unprocessable_entity }
        format.json { render json: @college.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /colleges/1 or /colleges/1.json
  def destroy
    @college.destroy

    respond_to do |format|
      format.html { redirect_to colleges_url, notice: 'College was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private

  # Use callbacks to share common setup or constraints between actions.
  def set_college
    @college = College.find(params[:id])
  end

  # Only allow a list of trusted parameters through.
  def college_params
    params.require(:college).permit(:name, :c_type)
  end
end
