# frozen_string_literal: true

class ApplicationController < ActionController::Base
  def check_user_permission
    return unless current_user.user_type != 'admin'

    render 'errors/forbidden', status: :forbidden
  end
end
