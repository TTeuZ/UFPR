package src.sectors;

import src.characters.*;

public class HiddenSector extends Sector {
    // Constructors
    public HiddenSector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y, isSource, found, sides);
    }

    public HiddenSector(int x, int y) {
        super(x, y, false, false, null);
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
