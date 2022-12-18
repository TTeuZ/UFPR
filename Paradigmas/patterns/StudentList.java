package patterns;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;

// Implementando o padrão singleton
public class StudentList implements Observer {
    private ArrayList<Student> list;
    private int iterator;
    private static StudentList instance;

    // Constructors
    private StudentList() {
        this.list = new ArrayList<Student>();
        this.iterator = 0;
    }

    // Methods
    public static StudentList getInstance() {
        if (instance == null)
            instance = new StudentList();
        return instance;
    }

    public Student next() {
        Student temp;
        temp = this.list.get(this.iterator);
        this.iterator++;
        return temp;
    }

    public boolean hasNext() {
        return (this.iterator < this.list.size());
    }

    public void insert(Student student) {
        this.list.add(student);
    }

    public int size() {
        return this.list.size();
    }

    public boolean isEnpty() {
        return this.list.size() == 0;
    }

    @Override
    public void update(Observable Student, Object arg1) {
        System.out.printf("A quantidade de estudantes da lista agora é: %d\n", this.list.size());
    }
}
