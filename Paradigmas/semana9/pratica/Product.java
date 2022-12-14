package semana9.pratica;

public class Product implements Shop{
    private String name;
    private double size;
    private double price;

    // Constructors
    public Product(String name, double size, double price) {
        this.setName(name);
        this.setSize(size);
        this.setPrice(price);
    }

    // Getters
    public String getName() {
        return name;
    }

    public double getSize() {
        return size;
    }

    public double getPrice() {
        return price;
    }

    // Setters
    public void setName(String name) {
        this.name = name;
    }

    public void setSize(double size) {
        this.size = size;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    // Methods
    @Override
    public void sell() {
        System.out.printf("Vendendo o protudo %s\n", this.getName());
    }

    @Override
    public void warranty() {
        System.out.printf("Acionando garantia do protudo %s\n", this.getName());
    }
}