import java.util.Scanner;

public class Exercicio7 {
    public static void main(String[] args) {
        String str1, str2;
        int count;
        Scanner input;

        input = new Scanner(System.in);

        System.out.println("Digite a primeira string: ");
        str1 = input.nextLine();
        System.out.println("Digite a segunda string: ");
        str2 = input.nextLine();

        str1 = str1.replace('a', '*');
        str1 = str1.replace('A', '*');

        str2 = str2.replace('a', '*');
        str2 = str2.replace('a', '*');

        for (count = str1.length() - 1; count >= 0; count--)
            System.out.printf("%c", str1.charAt(count));
        System.out.printf("\n");

        for (count = str2.length() - 1; count >= 0; count--)
            System.out.printf("%c", str2.charAt(count));
        System.out.printf("\n");

        input.close();
    }
}