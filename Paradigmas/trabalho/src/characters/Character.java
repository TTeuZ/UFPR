package src.characters;

import src.BoardPosition;

public abstract class Character extends BoardPosition {
    protected int attack;
    protected int defense;
    protected boolean alive;

    // ---------------------------- Constructors ----------------------------
    public Character(int x, int y, int attack, int defense) {
        super(x, y);
        this.setAttack(attack);
        this.setDefense(defense);
        this.alive = true;
    }

    // ---------------------------- Setters ----------------------------
    public void setAttack(int attack) {
        this.attack = attack;
    }

    public void setDefense(int defense) {
        if (defense <= 0) {
            this.defense = 0;
            this.alive = false;
        } else
            this.defense = defense;
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
