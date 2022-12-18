package patterns;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        RegisterStudent register;
        Scanner input;
        int isToRegister;
        String name, email, grr;

        register = new RegisterStudent();
        input = new Scanner(System.in);

        System.out.println("Deseja cadastrar um estudante (1) sim, (0) não");
        isToRegister = input.nextInt();

        while (isToRegister == 1) {
            System.out.printf("Informe o nome:\n");
            name = input.next();
            System.out.printf("Informe o email:\n");
            email = input.next();
            System.out.printf("Informe o grr:\n");
            grr = input.next();

            register.register(name, email, grr);

            System.out.println("Deseja cadastrar outro estudante (1) sim, (0) não");
            isToRegister = input.nextInt();
        }

        register.printStudentList();

        input.close();
    }
}
