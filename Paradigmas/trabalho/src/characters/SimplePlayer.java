package src.characters;

import java.util.Scanner;

import src.sectors.*;

public class SimplePlayer extends Player {
    // Constructors
    public SimplePlayer(int center, int attack, int defense, boolean canSearch, boolean canMove) {
        super(center, attack, defense, canSearch, canMove);
    }

    // ---------------------------- Public Methods ----------------------------
    public Sector move(Sector[][] board) {
        Scanner input;
        input = new Scanner(System.in);

        if (this.canMove) {
            System.out.printf("Where to go PLAYER 1 (P1)?\n");
            return super.move(board, input);
        } else {
            input.close();
            return null;
        }
    }

    @Override
    public void search() {
    }

    @Override
    public void attack() {
    }
}
