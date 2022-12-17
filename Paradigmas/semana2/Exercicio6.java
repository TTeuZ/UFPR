import java.util.Scanner;

public class Exercicio6 {
    public static void main (String[] args) {
        int line, col, number;
        int matrix[][];
        boolean hasFound;
        Scanner input;

        input = new Scanner (System.in);
        matrix = new int[4][4];
        line = col = 0;
        hasFound = false;

        System.out.println ("Digite os elementos da matriz: ");
        for (line = 0; line < 4; line++)
            for (col = 0; col < 4; col++)
                matrix[line][col] = input.nextInt ();

        System.out.println ("Digite o elemtno que deseja buscar: ");
        number = input.nextInt ();

        for (line = 0; line < 4 && !hasFound; line++)
            for (col = 0; col < 4 && !hasFound; col++) 
                if (matrix[line][col] == number) hasFound = true;
        
        if (hasFound)
            System.out.printf ("Elemento encontrado. Linha: %d, Coluna: %d\n", line, col);
        else
            System.out.printf ("Elemento não encontrado.\n");

            input.close();
    }
}