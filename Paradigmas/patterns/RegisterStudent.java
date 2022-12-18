package patterns;

import java.util.Observable;

public class RegisterStudent extends Observable {
    public void register(String name, String email, String grr) {
        StudentList list;
        Student temp;

        temp = new Student(name, email, grr);
        list = StudentList.getInstance();

        list.insert(temp);
        setChanged();
        notifyObservers();
    }

    public void printStudentList() {
        StudentList list;
        Student temp;

        list = StudentList.getInstance();

        System.out.printf("%d\n", list.size());

        while (list.hasNext()) {
            temp = list.next();
            System.out.printf("Nome: %s; Email: %s; Grr: %s\n", temp.getName(), temp.getEmail(), temp.getGrr());
        }
    }
}
