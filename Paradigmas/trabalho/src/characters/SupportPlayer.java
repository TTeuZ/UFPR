package src.characters;

import java.util.Scanner;

import src.sectors.*;

public class SupportPlayer extends Player {
    // Constructors
    public SupportPlayer(int center, int attack, int defense, boolean canSearch, boolean canMove) {
        super(center, attack, defense, canSearch, canMove);
    }

    // ---------------------------- Public Methods ----------------------------
    public Sector move(Sector[][] board) {
        Scanner input;
        input = new Scanner(System.in);

        System.out.printf("Where to go PLAYER 2 (P2)?\n");
        return super.move(board, input);
    }

    @Override
    public void search() {
    }

    @Override
    public void attack() {
    }

    public void recover() {
    }
}
