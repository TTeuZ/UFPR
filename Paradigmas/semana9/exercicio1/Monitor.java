package semana9.exercicio1;

public class Monitor implements Comparable<Monitor> {
    private String name;
    private int registration;
    private String classCode;

    // Constructors
    public Monitor(String name, int registration, String classCode) {
        this.setName(name);
        this.setRegistration(registration);
        this.setClassCode(classCode);
    }

    // Getters
    public String getName() {
        return name;
    }

    public int getRegistration() {
        return registration;
    }

    public String getClassCode() {
        return classCode;
    }

    // Setters
    public void setName(String name) {
        this.name = name;
    }

    public void setRegistration(int registration) {
        this.registration = registration;
    }

    public void setClassCode(String classCode) {
        this.classCode = classCode;
    }

    // Methods
    @Override
    public int compareTo(Monitor monitor) {
        return this.getName().compareTo(monitor.getName());
    }
}