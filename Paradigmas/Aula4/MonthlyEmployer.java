public class MonthlyEmployer extends Employer {
    protected double salary;

    // Getters
    public double getSalary() {
        return this.salary;
    }

    // Setters
    public void setSalary(double salary) {
        this.salary = salary;
    }

    // Constructors
    public MonthlyEmployer(String name, int register, boolean isForeign, double salary) {
        super(name, register, isForeign);
        this.setSalary(salary);
    }

    public MonthlyEmployer(String name, int register, double salary) {
        super(name, register);
        this.setSalary(salary);
    }

    public MonthlyEmployer(String name, double salary) {
        super(name);
        this.setSalary(salary);
    }

    // Methods
    public void print() {
        super.print();
        System.out.printf("Salario: %f\n", this.getSalary());
    }

    public final void askForBonus() {
        System.out.println("Quero um bonus!");
    }

    @Override
    public double calcSalary() {
        return this.getSalary();
    }
}