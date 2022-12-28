package src.characters;

import java.util.ArrayList;
import java.util.Scanner;

import src.sectors.*;

public class SimplePlayer extends Player {
    // Constructors
    public SimplePlayer(int center, int attack, int defense, boolean canSearch, boolean canMove) {
        super(center, attack, defense, canSearch, canMove);
    }

    // ---------------------------- Public Methods ----------------------------
    @Override
    public ArrayList<String> verifyActions() {
        ArrayList<String> temp;
        temp = new ArrayList<String>();

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

    @Override
    public void attack() {
    }
}
