package src.sectors;

import java.util.ArrayList;

import src.BoardPosition;
import src.characters.*;

public abstract class Sector extends BoardPosition {
    protected boolean isSource;
    protected boolean found;
    protected int sides[];
    protected ArrayList<Virus> enemies;

    // ---------------------------- Constructors ----------------------------
    public Sector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y);
        this.isSource = isSource;
        this.setSides(sides);
        this.setFound(found);
        this.enemies = new ArrayList<Virus>();
    }

    // ---------------------------- Setters ----------------------------
    public void setFound(boolean found) {
        this.found = found;
    }

    public void setSides(int[] sides) {
        if (this.sides == null)
            this.sides = sides;
    }

    // ---------------------------- Getters ----------------------------
    public boolean isSource() {
        return isSource;
    }

    public boolean isFound() {
        return found;
    }

    public int[] getSides() {
        return sides;
    }

    public ArrayList<Virus> getEnemies() {
        return enemies;
    }

    // ---------------------------- Public Methods ----------------------------
    public boolean hasAliveEnemies() {
        boolean temp;

        temp = false;
        for (Virus virus : this.enemies)
            if (virus.isAlive())
                temp = true;

        return temp;
    }

    public ArrayList<String> verifyMoves() {
        ArrayList<String> temp;
        temp = new ArrayList<String>();

        if (this.sides[TOP] != WALL)
            temp.add("Up");
        if (this.sides[RIGHT] != WALL)
            temp.add("Right");
        if (this.sides[BOTTOM] != WALL)
            temp.add("Down");
        if (this.sides[LEFT] != WALL)
            temp.add("Left");

        return temp;
    }

    public abstract void generateEnemies();

    public boolean reachSector(Player player) {
        if (!this.found && !this.isSource) {
            this.setFound(true);
            this.generateEnemies();
        }
        player.setCanMove(!hasAliveEnemies());

        return this.isSource;
    }
}
