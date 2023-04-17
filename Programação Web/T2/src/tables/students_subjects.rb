class StudentsSubjects<ActiveRecord::Base
    belongs_to :student, required: true
    belongs_to :subject, required: true

    def tableView
        puts "#{self.student_id}|#{self.subject_id}"
    end

    def printInfo(space: '')
        puts "#{space}Id do estudante: #{self.student_id}"
        puts "#{space}Id da matéria: #{self.subject_id}"
        puts ""
    end
end