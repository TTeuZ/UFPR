package src.sectors;

import src.characters.*;

public class PrivateSector extends Sector {
    // Constructors
    public PrivateSector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y, isSource, found, sides);
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
