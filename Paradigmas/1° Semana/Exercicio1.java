import java.util.Scanner;

public class Exercicio1 {
    public static void main (String[] args) {
        int num;
        Scanner input = new Scanner (System.in);
        
        System.out.print ("Informe o número: ");
        num = input.nextInt ();

        if (num >= 0) System.out.println ("O número é positivo!");
        else System.out.println ("O número é negativo!");
    }
}