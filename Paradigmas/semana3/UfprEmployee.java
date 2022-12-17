public class UfprEmployee {
    private String name;
    private String registry;
    private String role;
    private Date birthDate;

    // Getters
    public String getName() {
        return name;
    }

    public String getRegistry() {
        return registry;
    }

    public String getRole() {
        return role;
    }

    public Date getBirthDate() {
        return birthDate;
    }

    // Setters
    public void setName(String name) {
        this.name = name;
    }

    public void setRegistry(String registry) {
        this.registry = registry;
    }

    public void setRole(String role) {
        this.role = role;
    }

    public void setBirthDate(Date birthDate) {
        this.birthDate = birthDate;
    }

    public UfprEmployee(String name, String registry, String role, Date birthDate) {
        this.name = name;
        this.registry = registry;
        this.role = role;
        this.birthDate = birthDate;
    }
}