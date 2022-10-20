import java.util.Scanner;
import java.lang.Float;

public class Exercicio8 {
    public static void main (String[] args) {
        int fatCount;
        float currentHeight, currentSize;
        Scanner input = new Scanner (System.in);
        
        fatCount = -1;

        do {
            System.out.print ("Digite o valor da altura: ");
            currentHeight = input.nextFloat ();

            System.out.print ("Digite o valor do peso: ");
            currentSize = input.nextFloat ();

            if (Float.compare ((currentSize / (currentHeight * currentHeight)), 25.0f) <= 0) 
                fatCount++;
        } while (currentHeight != -1 && currentSize != -1);

        System.out.printf ("A quantidade de pessoas acima do peso é: %d\n", fatCount);
    }
}