import java.util.Scanner;

public class Exercicio4 {
    public static void main (String[] args) {
        int array[], count, maxValue, minValue;
        Scanner input;

        input = new Scanner (System.in);
        array = new int[7];

        System.out.print ("Digite os valores do array: \n");

        maxValue = minValue = input.nextInt();;
        for (count = 0; count < 6; count++) {
            array[count] = input.nextInt();
            if (array[count] > maxValue) maxValue = array[count];
            else if (array[count] < minValue) minValue = array[count];
        }

        System.out.printf ("Maior elemento do vetor é: %d\n", maxValue);
        System.out.printf ("Menor elemento do vetor é: %d\n", minValue);

        input.close();
    }
}