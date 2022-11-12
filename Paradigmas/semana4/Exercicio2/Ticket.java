package semana4.Exercicio2;

import java.lang.Double;

public class Ticket {
    protected double value;

    // Getters
    public double getValue() {
        return value;
    }

    // Setters
    public void setValue(double value) {
        if (Double.compare(value, 0.0) > 0) {
            this.value = value;
        }
    }

    // Constructors
    public Ticket(double value) {
        this.value = value;
    }

    public void printValue() {
        System.out.printf("Valor do ingresso: %f\n", this.getValue());
    }
}
