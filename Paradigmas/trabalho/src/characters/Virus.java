package src.characters;

public class Virus extends Character {
    private boolean canAvoid;

    // ---------------------------- Constructors ----------------------------
    public Virus(int x, int y, int status, boolean canAvoid) {
        super(x, y, status, status);
        this.setCanAvoid(canAvoid);
    }

    // ---------------------------- Setters ----------------------------
    public void setCanAvoid(boolean canAvoid) {
        this.canAvoid = canAvoid;
    }

    // ---------------------------- Getters ----------------------------
    public boolean isCanAvoid() {
        return canAvoid;
    }

    // ---------------------------- Public Methods ----------------------------
    @Override
    public void attack() {
    }
}
