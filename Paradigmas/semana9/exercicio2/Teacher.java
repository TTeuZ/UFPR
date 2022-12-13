package semana9.exercicio2;

public class Teacher {
    private String name;
    private int registration;

    // Constructors
    public Teacher(String name, int registration) {
        this.setName(name);
        this.setRegistration(registration);
    }

    // Getters
    public String getName() {
        return name;
    }

    public int getRegistration() {
        return registration;
    }

    // Setters
    public void setName(String name) {
        this.name = name;
    }

    public void setRegistration(int registration) {
        this.registration = registration;
    }
}
