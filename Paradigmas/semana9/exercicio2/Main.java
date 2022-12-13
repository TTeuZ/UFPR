package semana9.exercicio2;

import java.util.LinkedList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int registration, index;
        LinkedList<Teacher> list;
        Scanner input;
        Teacher temp;

        input = new Scanner(System.in);
        list = new LinkedList<Teacher>();

        temp = new Teacher("Hexsel", 01);
        list.add(temp);
        temp = new Teacher("Castilho", 02);
        list.add(temp);
        temp = new Teacher("Todt", 03);
        list.add(temp);
        temp = new Teacher("Eduardo", 04);
        list.add(temp);
        temp = new Teacher("Bona", 05);
        list.add(temp);

        System.out.printf("Lista de professores:\n");
        for (Teacher t : list)
            System.out.printf("%s\n", t.getName());

        System.out.printf("Digite a matricula do professor que deseja deletar: \n");
        registration = input.nextInt();

        index = -1;
        for (Teacher t : list) {
            if (t.getRegistration() == registration)
                index = list.indexOf(t);
        }
        if (index != -1)
            list.remove(index);

        System.out.printf("\nNova lista de professores:\n");
        for (Teacher t : list)
            System.out.printf("%s\n", t.getName());

        input.close();
    }
}
