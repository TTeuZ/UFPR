package src.characters;

import java.util.Random;
import java.util.concurrent.TimeUnit;

public class Virus extends Character {
    private boolean canAvoid;

    // ---------------------------- Constructors ----------------------------
    public Virus(int x, int y, int status, boolean canAvoid) {
        super(x, y, status, status);
        this.setCanAvoid(canAvoid);
    }

    // ---------------------------- Setters ----------------------------
    public void setCanAvoid(boolean canAvoid) {
        this.canAvoid = canAvoid;
    }

    // ---------------------------- Getters ----------------------------
    public boolean isCanAvoid() {
        return canAvoid;
    }

    // ---------------------------- Public Methods ----------------------------
    public void attack(Player player) throws InterruptedException {
        Random random;
        int type;

        if (player instanceof SimplePlayer)
            type = 1;
        else
            type = 2;

        System.out.printf("Virus %d/%d atacando o PLAYER %d (P%d)\n", this.attack, this.defense, type, type);
        TimeUnit.SECONDS.sleep(1);

        random = new Random();
        if ((random.nextInt(6) + 1) % 2 == 0) {
            player.reciveDamage(this.attack);
            System.out.printf("Acertou o ataque!\n");
        } else
            System.out.printf("Errou o ataque!\n");
        TimeUnit.SECONDS.sleep(2);
    }
}
