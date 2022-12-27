package src.sectors;

public class PrivateSector extends Sector {
    // Constructors
    public PrivateSector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y, isSource, found, sides);
    }

    // Methods
    @Override
    public void generateEnemies() {
        System.out.println("batata");
    }

    @Override
    public void reachSector() {
        this.setFound(true);

    }
}
