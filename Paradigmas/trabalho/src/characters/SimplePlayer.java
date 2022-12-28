package src.characters;

import java.util.ArrayList;
import java.util.Scanner;

import src.sectors.*;

public class SimplePlayer extends Player {
    // ---------------------------- Constructors ----------------------------
    public SimplePlayer(int center, int attack, int defense) {
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

        return temp;
    }

    public Sector move(Sector[][] board, Scanner input) {
        if (this.canMove) {
            System.out.printf("Movimentação PLAYER 1 (P1)?\n");
            return super.move(board, input);
        } else
            return null;
    }
}
