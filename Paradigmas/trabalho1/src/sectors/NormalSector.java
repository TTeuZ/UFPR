package src.sectors;

public class NormalSector extends Sector {
    // Constructors
    public NormalSector(int x, int y, boolean isSource, boolean found, int[] sides) {
        super(x, y, isSource, found, sides);
    }

    public NormalSector(int center, boolean isSource, boolean found, int[] sides) {
        super(center, center, isSource, found, sides);
    }

    // Methods
    @Override
    public void generateEnemies() {
        System.out.println("batata");
    }

    @Override
    public void reachSector() {
        System.out.println("batata");
    }
}
