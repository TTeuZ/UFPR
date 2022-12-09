package semana8;

public abstract class Immobile {
    protected Address immobileAddress;
    protected double price;

    // Constructors
    public Immobile(Address immobileAddress, double price) {
        this.setImmobileAddress(immobileAddress);
        this.setPrice(price);
    }

    // Getters
    public Address getImmobileAddress() {
        return immobileAddress;
    }

    public double getPrice() {
        return price;
    }

    // Setters
    public void setPrice(double price) {
        this.price = price;
    }

    public void setImmobileAddress(Address immobileAddress) {
        this.immobileAddress = immobileAddress;
    }

    public abstract double calcImmobileValue();
}