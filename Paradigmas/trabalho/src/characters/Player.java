package src.characters;

public abstract class Player extends Character {
    protected boolean canSearch;
    protected boolean canMove;

    // Contructors
    public Player(int center, int attack, int defense, boolean canSearch, boolean canMove) {
        super(center, center, attack, defense);
        this.setCanSearch(canSearch);
        this.setCanMove(canMove);
    }

    // Setters
    public void setCanSearch(boolean canSearch) {
        this.canSearch = canSearch;
    }

    public void setCanMove(boolean canMove) {
        this.canMove = canMove;
    }

    // Getters
    public boolean isCanSearch() {
        return canSearch;
    }

    public boolean isCanMove() {
        return canMove;
    }

    // ---------------------------- Public Methods ----------------------------
    public abstract boolean move();

    public abstract void search();
}