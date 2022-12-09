package semana8;

import java.util.Random;

public class NewImmobile extends Immobile {
    // Constructors
    public NewImmobile(Address immobileAddress, double price) {
        super(immobileAddress, price);
    }

    // Methods
    @Override
    public double calcImmobileValue() {
        Random random;
        double multiplier;

        random = new Random();

        multiplier = (double) (random.nextInt(2) + 1) / 10;
        return this.getPrice() + (this.getPrice() * multiplier);
    }
}
