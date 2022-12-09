package semana8;

import java.util.Scanner;

import javax.swing.text.StyledEditorKit;

import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Immobile immobiles[];
        Address address;
        Scanner input;
        Random random;
        double price;
        int count, immobileType;

        input = new Scanner(System.in);
        random = new Random();
        immobiles = new Immobile[10];
        address = new Address("Rua Batata", 255, "Batatoes", "Batatopolis", "Batafi");

        for (count = 0; count < 10; ++count) {
            System.out.printf("Informe o valor da casa\n");
            price = input.nextDouble();

            immobileType = random.nextInt(2);
            switch (immobileType) {
                case 0:
                    immobiles[count] = new NewImmobile(address, price);
                    break;
                case 1:
                    immobiles[count] = new OldImmobile(address, price);
                    break;
            }
        }

        for (count = 0; count < 10; ++count)
            System.out.printf("O valor da casa %d, é %f\n", count + 1, immobiles[count].calcImmobileValue());

        input.close();
    }
}
