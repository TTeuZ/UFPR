package semana4.Exercicio1;

public class Bulb {
    protected boolean status;

    // Getters
    public boolean isStatus() {
        return status;
    }

    // Setters
    public void setStatus(boolean status) {
        this.status = status;
    }

    public void changeStatus() {
        this.setStatus(!this.isStatus());
    }

    public void printStatus() {
        System.out.printf("Estado: " + this.isStatus());
    }
}
