# frozen_string_literal: true

class CreateStudents < ActiveRecord::Migration[7.0]
  def change
    create_table :students do |t|
      t.string :name
      t.integer :age
      t.string :register
      t.references :college, null: false, foreign_key: true

      t.timestamps
    end
  end
end
