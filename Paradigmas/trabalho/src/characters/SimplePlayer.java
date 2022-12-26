package src.characters;

public class SimplePlayer extends Player {
    // Constructors
    public SimplePlayer(int center, int attack, int defense, boolean canSearch, boolean canMove) {
        super(center, attack, defense, canSearch, canMove);
    }

    // ---------------------------- Public Methods ----------------------------
    @Override
    public boolean move() {
        return true;
    }

    @Override
    public void search() {
    }

    @Override
    public void attack() {
    }
}
