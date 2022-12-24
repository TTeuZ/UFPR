package src;

public abstract class BoardPosition {
    protected int x;
    protected int y;

    // Constructors
    public BoardPosition(int x, int y) {
        this.setX(x);
        this.setY(y);
    }

    // Setters
    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    // Getters
    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    // Methods
    // public void attPos(char move) {
    // switch (move) {
    // case 'U':
    // this.setY(this.getY() + 1);
    // break;
    // case 'L':
    // this.setX(this.getX() - 1);
    // break;
    // case 'R':
    // this.setX(this.getX() + 1);
    // break;
    // case 'D':
    // this.setY(this.getY() + 1);
    // break;
    // }
    // }
}
