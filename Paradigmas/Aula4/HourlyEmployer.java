public class HourlyEmployer extends Employer {
    private double valuePerHour;
    private double workedHours;

    // Getters
    public double getValuePerHour () {
        return this.valuePerHour;
    }
    public double getWorkedHours () {
        return this.workedHours;
    }

    // Setters
    public void setValuePerHour (double valuePerHour) {
        this.valuePerHour = valuePerHour;
    }
    public void setWorkedHours (double workedHours) {
        this.workedHours = workedHours;
    }

    // Constructor
    public HourlyEmployer (String name, int register, boolean isForeign, double valuePerHour, double workedHours) {
        super (name, register, isForeign);
        this.setValuePerHour (valuePerHour);
        this.setWorkedHours (workedHours);
    }
    public HourlyEmployer (String name, int register, double valuePerHour, double workedHours) {
        super (name, register);
        this.setValuePerHour (valuePerHour);
        this.setWorkedHours (workedHours);
    }
    public HourlyEmployer (String name, double valuePerHour, double workedHours) {
        super (name);
        this.setValuePerHour (valuePerHour);
        this.setWorkedHours (workedHours);
    }

    // Methods
    public void print ()  {
        super.print ();
        System.out.printf ("Valor por hora: %f\n", this.getValuePerHour ());
        System.out.printf ("Horas trabalhadas: %f\n", this.getWorkedHours ());
    }

    @Override        
    public double calcSalary () {
        return this.getValuePerHour () * this.getWorkedHours ();
    }
}