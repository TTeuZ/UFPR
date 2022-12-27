package src.characters;

import src.BoardPosition;
import src.constants.*;

public abstract class Character extends BoardPosition implements Constants {
    protected int attack;
    protected int defense;

    // Constructors
    public Character(int x, int y, int attack, int defense) {
        super(x, y);
        this.setAttack(attack);
        this.setDefense(defense);
    }

    // Setters
    public void setAttack(int attack) {
        this.attack = attack;
    }

    public void setDefense(int defense) {
        this.defense = defense;
    }

    // Getters
    public int getAttack() {
        return attack;
    }

    public int getDefense() {
        return defense;
    }

    // ---------------------------- Public Methods ----------------------------
    public abstract void attack();
}
