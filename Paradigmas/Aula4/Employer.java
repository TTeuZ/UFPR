public class Employer {
    protected String name;
    protected int register;
    protected boolean isForeign;

    // Getters
    public String getName() {
        return this.name;
    }

    public int getRegister() {
        return this.register;
    }

    public boolean isForeign() {
        return this.isForeign;
    }

    // Setters
    public void setName(String name) {
        this.name = name;
    }

    public void setRegister(int register) {
        this.register = register;
    }

    public void setIsForeign(boolean isForeign) {
        this.isForeign = isForeign;
    }

    // Constructors
    public Employer(String name, int register, boolean isForeign) {
        this.setName(name);
        this.setRegister(register);
        this.setIsForeign(isForeign);
    }

    public Employer(String name, int register) {
        this.setName(name);
        this.setRegister(register);
    }

    public Employer(String name) {
        this.setName(name);
    }

    // Methods
    protected void print() {
        System.out.printf("Funcionário: %s\n", this.getName());
        System.out.printf("Numero do registro: %d\n", this.getRegister());
        System.out.printf("Estrangeiro: %s\n", this.isForeign() ? "Sim" : "Não");
    }

    protected double calcSalary() {
        return 0.0;
    }
}