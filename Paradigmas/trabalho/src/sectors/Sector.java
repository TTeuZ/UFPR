package src.sectors;

import java.util.ArrayList;

import src.BoardPosition;
import src.constants.Constants;

public abstract class Sector extends BoardPosition implements Constants {
    protected boolean isSource;
    protected boolean found;
    protected int sides[];

    // Constructors
    public Sector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y);
        this.isSource = isSource;
        this.setSides(sides);
        this.setFound(found);
    }

    // Setters
    public void setFound(boolean found) {
        this.found = found;
    }

    public void setSides(int[] sides) {
        if (this.sides == null)
            this.sides = sides;
    }

    // Getters
    public boolean isSource() {
        return isSource;
    }

    public boolean isFound() {
        return found;
    }

    public int[] getSides() {
        return sides;
    }

    // ---------------------------- Public Methods ----------------------------
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

    // Função responsável por gerar os inimigos do setor como especificado
    public abstract void generateEnemies();

    // Função que realiza as verificações quando o jogador entra no setor
    public abstract void reachSector();
}
