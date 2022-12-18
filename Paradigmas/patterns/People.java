package patterns;

public abstract class People {
    protected String name;
    protected String email;

    // Constructors
    public People(String name, String email) {
        this.name = name;
        this.email = email;
    }

    // Setters
    public String getName() {
        return this.name;
    }

    public String getEmail() {
        return this.email;
    }

    // Getters
    public void setName(String name) {
        this.name = name;
    }

    public void setEmail(String email) {
        this.email = email;
    }
}
