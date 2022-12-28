package src.characters;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

import src.sectors.*;

public class SupportPlayer extends Player {
    // ---------------------------- Constructors ----------------------------
    public SupportPlayer(int center, int attack, int defense) {
        super(center, attack, defense);
    }

    // ---------------------------- Public Methods ----------------------------
    @Override
    public ArrayList<String> verifyActions(Sector[][] board) {
        ArrayList<String> temp;
        temp = new ArrayList<String>();

        if (this.sector(board).hasAliveEnemies())
            temp.add("Attack");
        if (this.canSearch)
            temp.add("Search");
        temp.add("Recover");

        return temp;
    }

    public Sector move(Sector[][] board, Scanner input) {
        if (this.canMove) {
            System.out.printf("Movimentação PLAYER 2 (P2)?\n");
            return super.move(board, input);
        } else
            return null;
    }

    public void recover(SimplePlayer playerOne, Scanner input) throws InterruptedException {
        boolean sameSector, recovered;
        String selectedPlayer;

        sameSector = recovered = false;
        if (this.x == playerOne.getX() && this.y == playerOne.getY())
            sameSector = true;

        if (sameSector) {
            System.out.printf("De que deseja recuperar a defesa?\n");
            System.out.printf("P1 - Primeiro Jogador\nP2 - Segundo Jogador\n");
            while (!recovered) {
                selectedPlayer = input.next();
                if (selectedPlayer.equals("P1") || selectedPlayer.equals("P2"))
                    recovered = true;
                if (recovered) {
                    System.out.printf("Recuperando...\n");
                    TimeUnit.SECONDS.sleep(WAIT_TIME);

                    switch (selectedPlayer) {
                        case "P1":
                            playerOne.setDefense(playerOne.getDefense() + 2);
                            break;
                        case "P2":
                            this.setDefense(this.defense + 2);
                            break;
                    }
                } else
                    System.out.printf("Player não existente!\n");
            }
        } else {
            System.out.printf("Recuperando...\n");
            TimeUnit.SECONDS.sleep(WAIT_TIME);
            this.setDefense(this.defense + 2);
        }
    }
}
