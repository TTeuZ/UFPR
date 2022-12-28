package src.sectors;

import java.util.Random;

import src.characters.*;

public class HiddenSector extends Sector {
    // ---------------------------- Constructors ----------------------------
    public HiddenSector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y, isSource, found, sides);
    }

    public HiddenSector(int x, int y) {
        super(x, y, false, false, null);
    }

    // ---------------------------- Public Methods ----------------------------
    @Override
    public void generateEnemies() {
        int enemiesQtd, virusStatus, count;
        Random random;

        random = new Random();
        enemiesQtd = random.nextInt(3) + 1;

        for (count = 0; count < enemiesQtd; ++count) {
            virusStatus = random.nextInt(3) + 1;
            this.enemies.add(new Virus(this.x, this.y, virusStatus, true));
        }
    }

    public boolean reachSector(Player player) {
        boolean reachedSorce;
        reachedSorce = super.reachSector(player);
        player.setCanSearch(true);

        return reachedSorce;
    }
}
