package semana8;

import java.util.Random;

public class OldImmobile extends Immobile {
    // Constructors
    public OldImmobile(Address immobileAddress, double price) {
        super(immobileAddress, price);
    }

    // Methods
    @Override
    public double calcImmobileValue() {
        Random random;
        double multiplier;

        random = new Random();

        multiplier = (double) (random.nextInt(2) + 1) / 10;
        return this.getPrice() - (this.getPrice() * multiplier);
    }
}
