package src;

public abstract class BoardPosition {
    protected int x;
    protected int y;

    // ---------------------------- Constructors ----------------------------s
    public BoardPosition(int x, int y) {
        this.setX(x);
        this.setY(y);
    }

    // ---------------------------- Setters ----------------------------
    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    // ---------------------------- Getters ----------------------------
    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
