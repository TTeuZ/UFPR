class College<ActiveRecord::Base
    has_many :student, dependent: :destroy
end