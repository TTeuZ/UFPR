package semana4.Exercicio2;

public class VipTicket extends Ticket {
    protected double aditionalValue;

    // Getters
    public double getAditionalValue() {
        return aditionalValue;
    }

    // Setters
    public void setAditionalValue(double aditionalValue) {
        this.aditionalValue = aditionalValue;
    }

    // Constructors
    public VipTicket(double value, double aditionalValue) {
        super(value);
        this.aditionalValue = aditionalValue;
    }

    @Override
    public void printValue() {
        double totalValue;

        totalValue = this.getAditionalValue() + this.getValue();
        System.out.printf("Valor do ingresso: %f\n", totalValue);
    }
}
