public class UfprPayroll {
    private UfprEmployee employee;
    private int paymentDay, paymentMonth;
    private double value;

    // Getters
    public UfprEmployee getEmployee() {
        return employee;
    }

    public int getPaymentDay() {
        return paymentDay;
    }

    public int getPaymentMonth() {
        return paymentMonth;
    }

    public double getValue() {
        return value;
    }

    // Setters
    public void setEmployee(UfprEmployee employee) {
        this.employee = employee;
    }

    public void setPaymentDay(int paymentDay) {
        this.paymentDay = paymentDay;
    }

    public void setPaymentMonth(int paymentMonth) {
        this.paymentMonth = paymentMonth;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public UfprPayroll(UfprEmployee employee, int paymentDay, int paymentMonth, double value) {
        this.employee = employee;
        this.paymentDay = paymentDay;
        this.paymentMonth = paymentMonth;
        this.value = value;
    }

    public void printPayroll() {
        System.out.printf("----------------------------------------------------------------\n");
        System.out.printf("Funcionário: %s\n", this.employee.getName());
        System.out.printf("Dia de pagamento: %2d/%2d\n", this.paymentDay, this.paymentMonth);
        System.out.printf("Valor do pagamento: %f\n", this.value);
        System.out.printf("----------------------------------------------------------------\n");
    }
}
