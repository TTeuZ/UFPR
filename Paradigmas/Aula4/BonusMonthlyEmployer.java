public class BonusMonthlyEmployer extends MonthlyEmployer {
    private double bonusSalary;

    // Getters
    public double getBonusSalary() {
        return this.bonusSalary;
    }

    // Setters
    public void setBonusSalary(double bonusSalary) {
        this.bonusSalary = bonusSalary;
    }

    // Constructors
    public BonusMonthlyEmployer(String name, int register, boolean isForeign, double salary) {
        super(name, register, isForeign, salary);
    }
}