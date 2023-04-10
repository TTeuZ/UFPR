class Student<ActiveRecord::Base
    has_one :address
    belongs_to :college
    has_and_belongs_to_many :subject
end