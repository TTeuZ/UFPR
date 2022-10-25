import java.util.Scanner;

public class Exercicio2 {
    public static void main (String[] args) {
        int num;
        Scanner input = new Scanner (System.in);

        System.out.print ("Informe o número: ");
        num = input.nextInt();

        if (num % 2 == 0) System.out.println ("O número é par!");
        else System.out.println ("O número é impar!");

        input.close();
    }
}