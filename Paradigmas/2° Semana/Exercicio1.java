import java.util.Scanner;

public class Exercicio1 {
    public static void main (String[] args) {
        int[] oddNumbers, pairNumbers;
        int currentNumber, oddPos, pairPos, count, pairSum;
        Scanner input;

        input = new Scanner (System.in);
        oddNumbers = new int[10];
        pairNumbers = new int[10];
        oddPos = pairPos = pairSum =  0;

        for (count = 0; count < 10; count++) {
            System.out.print("Digite o numero inteiro: ");
            currentNumber = input.nextInt ();
            if (currentNumber % 2 == 0) {
                pairNumbers[pairPos] = currentNumber;
                pairPos++;
            } else {
                oddNumbers[oddPos] = currentNumber;
                oddPos++;
            }
        }

        System.out.print("Os numeros pares são: ");
        for (count = 0; count < pairPos; count++) {
            System.out.printf("%d ", pairNumbers[count]);
            pairSum += pairNumbers[count];
        }
        System.out.printf("\n");
        System.out.printf("A soma dos pares é: %d\n", pairSum);

        System.out.print("Os numeros impares são: ");
        for (count = 0; count < oddPos; count++)
            System.out.printf("%d ", oddNumbers[count]);
        System.out.printf("\n");
        System.out.printf("A quantidade de numeros impares é: %d\n", oddPos);
    }
}