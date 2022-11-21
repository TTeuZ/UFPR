package semana5;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        WebCard cards[];
        Scanner input;
        int count, cardType, qtd;
        String destination;

        input = new Scanner(System.in);

        System.out.printf("Informe quantas cartas que enviar\n");
        qtd = input.nextInt();

        cardType = 0;
        cards = new WebCard[qtd];
        for (count = 0; count < qtd; ++count) {
            System.out.printf("Informe o destinatário: \n");
            destination = input.next();

            switch (cardType) {
                case 0:
                    cards[count] = new ValentinesCard(destination);
                    break;
                case 1:
                    cards[count] = new ChristimasCard(destination);
                    break;
                case 2:
                    cards[count] = new BirthdayCard(destination);
                    break;
            }
            if (++cardType == 3)
                cardType = 0;
        }

        for (count = 0; count < qtd; ++count) {
            System.out.printf("----------------------------\n");
            cards[count].returnMessage("Paulo");
            System.out.printf("----------------------------\n");
        }

        input.close();
    }
}
