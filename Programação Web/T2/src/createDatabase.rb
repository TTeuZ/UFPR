ActiveRecord::Base.establish_connection :adapter => "sqlite3", :database => "database/BD.sqlite3"

if not ActiveRecord::Base.connection.table_exists? 'colleges'
    ActiveRecord::Base.connection.create_table :colleges do |college|
        college.string :name
        college.string :c_type
        college.timestamps
    end
end

if not ActiveRecord::Base.connection.table_exists? 'students'
    ActiveRecord::Base.connection.create_table :students do |student|
        student.string :name
        student.integer :age
        student.string :register
        student.belongs_to :college, foreign_key: true
        student.timestamps
    end
end

if not ActiveRecord::Base.connection.table_exists? 'addresses'
    ActiveRecord::Base.connection.create_table :addresses do |address|
        address.string :streat
        address.integer :number
        address.references :student, foreign_key: true
        address.timestamps
    end
end

if not ActiveRecord::Base.connection.table_exists? 'subjects'
    ActiveRecord::Base.connection.create_table :subjects do |subject|
        subject.string :name
        subject.string :code
        subject.timestamps
    end
end

if not ActiveRecord::Base.connection.table_exists? 'students_subjects'
    ActiveRecord::Base.connection.create_table :students_subjects do |ss|
        ss.references :student
        ss.references :subject
    end
end