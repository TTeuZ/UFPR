# frozen_string_literal: true

Rails.application.routes.draw do
  resources :subjects
  resources :students_subjects
  resources :addresses
  resources :students
  resources :colleges
  resources :home
  # Define your application routes per the DSL in https://guides.rubyonrails.org/routing.html

  # Defines the root path route ("/")
  root 'home#index'
end
