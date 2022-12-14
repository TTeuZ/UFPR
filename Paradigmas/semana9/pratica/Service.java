package semana9.pratica;

public class Service implements Shop {
    private String name;
    private int time;
    private double price;

    // Constructors
    public Service(String name, int time, double price) {
        this.setName(name);
        this.setTime(time);
        this.setPrice(price);
    }

    // Getters
    public String getName() {
        return name;
    }

    public int getTime() {
        return time;
    }

    public double getPrice() {
        return price;
    }

    // Setters
    public void setName(String name) {
        this.name = name;
    }

    public void setTime(int time) {
        this.time = time;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    // Methods
    @Override
    public void sell() {
        System.out.printf("Vendendo o serviço %s\n", this.getName());
    }

    @Override
    public void warranty() {
        System.out.printf("Acionando garantia do serviço %s\n", this.getName());
    }
}