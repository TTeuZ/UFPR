package semana4.Exercicio1;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        FluorescentBulb fluorescentBulb;
        LedBulb ledBulb;
        Bulb bulb;
        Scanner input;
        int action;

        input = new Scanner(System.in);

        fluorescentBulb = new FluorescentBulb();
        ledBulb = new LedBulb();
        bulb = new Bulb();
        action = 0;

        do {
            System.out.println("Ações: ");
            System.out.printf("%s a lampada normal -- 1\n", bulb.isStatus() ? "desligar" : "ligar");
            System.out.printf("%s a lampada flourescente -- 2\n", fluorescentBulb.isStatus() ? "desligar" : "ligar");
            System.out.printf("%s a lampada led -- 1\n", ledBulb.isStatus() ? "desligar" : "ligar");
            System.out.printf("sair -- 0\n");
            System.out.printf("----------------------------------------------------\n");
            System.out.println("Estados: ");
            System.out.printf("Lampada normal: %s\n", bulb.isStatus() ? "ligada" : "desligada");
            System.out.printf("Lampada flourescente: %s\n", fluorescentBulb.isStatus() ? "ligada" : "desligada");
            System.out.printf("Lampada led: %s\n", ledBulb.isStatus() ? "ligada" : "desligada");

            action = input.nextInt();

            switch (action) {
                case 1:
                    bulb.changeStatus();
                    break;
                case 2:
                    fluorescentBulb.changeStatus();
                    break;
                case 3:
                    ledBulb.changeStatus();
                    break;
            }
        } while (action != 0);

        input.close();
    }
}
