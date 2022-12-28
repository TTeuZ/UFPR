package src.sectors;

import src.characters.*;

public class PrivateSector extends Sector {
    // Constructors
    public PrivateSector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y, isSource, found, sides);
    }

    public PrivateSector(int x, int y) {
        super(x, y, false, false, null);
    }

    // Methods
    @Override
    public void generateEnemies() {
        System.out.println("batata private");
    }

    public void reachSector(Player player) {
        super.reachSector(player);
        player.setCanSearch(false);
    }
}
