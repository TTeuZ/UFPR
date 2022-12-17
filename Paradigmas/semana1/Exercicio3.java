import java.util.Scanner;

public class Exercicio3 {
    public static void main (String[] args) {
        int sum, num;
        Scanner input = new Scanner (System.in);

        System.out.println ("Digite os numeros. (-1 encerra a soma): ");

        sum = 0;
        num = input.nextInt ();
        while (num != -1) {
            sum = sum + num;
            num = input.nextInt ();
        }
        System.out.println ("A soma é: " + sum);

        input.close();
    }
}