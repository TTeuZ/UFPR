package src.sectors;

import src.characters.*;

public class HiddenSector extends Sector {
    // Constructors
    public HiddenSector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y, isSource, found, sides);
    }

    // Methods
    @Override
    public void generateEnemies() {
        System.out.println("batata Hidden");
    }

    public void reachSector(Player player) {
        super.reachSector(player);
        player.setCanSearch(true);
    }
}
