package semana4.Exercicio2;

public class CabinTicket extends VipTicket {
    protected double cabinValue;

    // Setters
    public double getCabinValue() {
        return cabinValue;
    }

    // Getters
    public void setCabinValue(double cabinValue) {
        this.cabinValue = cabinValue;
    }

    // Constructors
    public CabinTicket(double value, double aditionalValue, double cabinValue) {
        super(value, aditionalValue);
        this.cabinValue = cabinValue;
    }

    @Override
    public void printValue() {
        double totalValue;

        totalValue = this.getAditionalValue() + this.getValue() + this.getCabinValue();
        System.out.printf("Valor do ingresso: %f\n", totalValue);
    }
}
