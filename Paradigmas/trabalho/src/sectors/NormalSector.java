package src.sectors;

import src.characters.*;

public class NormalSector extends Sector {
    // ---------------------------- Constructors ----------------------------
    public NormalSector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y, isSource, found, sides);
    }

    public NormalSector(int x, int y) {
        super(x, y, false, false, null);
    }

    // ---------------------------- Public Methods ----------------------------
    @Override
    public void generateEnemies() {
        System.out.println("batata Normal");
    }

    public void reachSector(Player player) {
        super.reachSector(player);
        player.setCanSearch(true);
    }
}
