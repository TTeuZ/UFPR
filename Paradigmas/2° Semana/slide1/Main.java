import java.util.Scanner;

public class Main {
    public static void main (String[] args) {
        int day, month, year, count;
        Scanner input;
        Date[] dates;

        input = new Scanner (System.in);
        dates = new Date[10];

        for (count = 0; count < 10; count++) {
            System.out.println ("Informe o dia de nascimento: ");
            day = input.nextInt ();
            System.out.println ("Informe o mes de nascimento: ");
            month = input.nextInt ();
            System.out.println ("Informe o ano de nascimento: ");
            year = input.nextInt ();

            dates[count] = new Date (day, month, year);
        }

        for (count = 0; count < 10; count++) {
            dates[count].print ();
        }
    }
}