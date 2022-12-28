package src.characters;

import src.BoardPosition;
import src.constants.*;

public abstract class Character extends BoardPosition implements Constants {
    protected int attack;
    protected int defense;
    protected boolean alive;

    // ---------------------------- Constructors ----------------------------
    public Character(int x, int y, int attack, int defense) {
        super(x, y);
        this.setAttack(attack);
        this.setDefense(defense);
        this.setAlive(true);
    }

    // ---------------------------- Setters ----------------------------
    public void setAttack(int attack) {
        this.attack = attack;
    }

    public void setDefense(int defense) {
        if (defense <= 0) {
            this.defense = 0;
            this.setAlive(false);
        } else
            this.defense = defense;
    }

    public void setAlive(boolean alive) {
        this.alive = alive;
    }

    // ---------------------------- Getters ----------------------------
    public int getAttack() {
        return attack;
    }

    public int getDefense() {
        return defense;
    }

    public boolean isAlive() {
        return alive;
    }

    // ---------------------------- Public Methods ----------------------------
    public void reciveDamage(int damage) {
        int newDefense;

        newDefense = this.defense - damage;
        this.setDefense(newDefense);
    }
}
