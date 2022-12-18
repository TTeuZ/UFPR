package patterns;

public class Student extends People {
    private String grr;

    // Constructors
    public Student(String name, String email, String grr) {
        super(name, email);
        this.grr = grr;
    }

    // Getters
    public String getGrr() {
        return grr;
    }

    // Setters
    public void setGrr(String grr) {
        this.grr = grr;
    }

}
