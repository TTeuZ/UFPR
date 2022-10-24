import java.util.Scanner;

public class Exercicio2 {
    public static void main (String[] args) {
        int line, col, sum;
        int[][] matrix;
        Scanner input;

        input = new Scanner (System.in);
        matrix = new int[3][3];


        for (line = 0; line < 3; line++)
            for (col = 0; col < 3; col++) 
                matrix[line][col] = input.nextInt ();

        for (col = 0; col < 3; col++) {
            sum = 0;
            for (line = 0; line < 3; line++)
                sum += matrix[line][col];
            System.out.printf ("%d ", sum);
        }
        System.out.printf ("\n ");
    }
}