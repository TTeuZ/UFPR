ActiveRecord::Base.establish_connection :adapter => "sqlite3", :database => "database/BD.sqlite3"

if not ActiveRecord::Base.connection.table_exists? 'colleges'
    ActiveRecord::Base.connection.create_table :colleges do |college|
        college.string :name
        college.string :type
    end
end

if not ActiveRecord::Base.connection.table_exists? 'students'
    ActiveRecord::Base.connection.create_table :students do |student|
        student.string :name
        student.integer :age
        student.string :register
        student.belongs_to :college, foreign_key: true
    end
end

if not ActiveRecord::Base.connection.table_exists? 'adresses'
    ActiveRecord::Base.connection.create_table :adresses do |address|
        address.string :country
        address.string :state
        address.string :city
        address.string :streat
        address.integer :number
        address.references :student, foreign_key: true
    end
end

if not ActiveRecord::Base.connection.table_exists? 'subjects'
    ActiveRecord::Base.connection.create_table :subjects do |subject|
        subject.string :name
        subject.string :code
    end
end

if not ActiveRecord::Base.connection.table_exists? 'students_subjects'
    ActiveRecord::Base.connection.create_table :students_subjects, id: false do |ss|
        ss.references :student
        ss.references :subject
    end
end