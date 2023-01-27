package src;

import src.constants.Constants;

public abstract class BoardPosition implements Constants {
    protected int x;
    protected int y;

    // ---------------------------- Constructors ----------------------------s
    public BoardPosition(int x, int y) {
        this.setX(x);
        this.setY(y);
    }

    // ---------------------------- Setters ----------------------------
    public void setX(int x) {
        if (x < BOARD_SIZE)
            this.x = x;
    }

    public void setY(int y) {
        if (y < BOARD_SIZE)
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
