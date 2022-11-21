package semana5;

public abstract class WebCard {
    protected String destination;

    // Constructors
    public WebCard(String destination) {
        this.destination = destination;
    }

    // Getters
    public String getDestination() {
        return destination;
    }

    // Setters
    public void setDestination(String destination) {
        this.destination = destination;
    }

    // Methods
    public abstract void returnMessage(String sender);
}
