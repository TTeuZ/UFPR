package semana8;

public class Address {
    private String street;
    private int number;
    private String neighborhood;
    private String city;
    private String region;

    // Constructors
    public Address(String street, int number, String neighborhood, String city, String region) {
        this.setStreet(street);
        this.setNumber(number);
        this.setNeighborhood(neighborhood);
        this.setCity(city);
        this.setRegion(region);
    }

    // Getters
    public String getStreet() {
        return street;
    }

    public int getNumber() {
        return number;
    }

    public String getNeighborhood() {
        return neighborhood;
    }

    public String getCity() {
        return city;
    }

    public String getRegion() {
        return region;
    }

    // Setters
    public void setStreet(String street) {
        this.street = street;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public void setNeighborhood(String neighborhood) {
        this.neighborhood = neighborhood;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public void setRegion(String region) {
        this.region = region;
    }
}
