class CreateAddresses < ActiveRecord::Migration[7.0]
  def change
    create_table :addresses do |t|
      t.string :streat
      t.integer :number
      t.references :student, null: false, foreign_key: true

      t.timestamps
    end
  end
end
