package src.characters;

import java.util.ArrayList;
import java.util.Scanner;

import src.sectors.*;

public abstract class Player extends Character {
    protected boolean canSearch;
    protected boolean canMove;

    // Contructors
    public Player(int center, int attack, int defense, boolean canSearch, boolean canMove) {
        super(center, center, attack, defense);
        this.setCanSearch(canSearch);
        this.setCanMove(canMove);
    }

    // Setters
    public void setCanSearch(boolean canSearch) {
        this.canSearch = canSearch;
    }

    public void setCanMove(boolean canMove) {
        this.canMove = canMove;
    }

    // Getters
    public boolean isCanSearch() {
        return canSearch;
    }

    public boolean isCanMove() {
        return canMove;
    }

    // ---------------------------- Public Methods ----------------------------
    public Sector move(Sector[][] board, Scanner input) {
        ArrayList<String> possibleMoves;
        Sector actualSector;
        String selectedMove;
        boolean moved, validMove;

        moved = validMove = false;
        actualSector = board[this.x][this.y];
        possibleMoves = actualSector.verifyMoves();

        for (String move : possibleMoves)
            System.out.printf("%s - %s\n", move.substring(0, 1), move);

        while (!moved) {
            selectedMove = input.next();
            for (String move : possibleMoves)
                if (move.contains(selectedMove))
                    validMove = true;

            if (validMove) {
                moved = true;
                switch (selectedMove) {
                    case "U":
                        this.setX(this.x - 1);
                        break;
                    case "R":
                        this.setY(this.y + 1);
                        break;
                    case "D":
                        this.setX(x + 1);
                        break;
                    case "L":
                        this.setY(y - 1);
                        break;
                }
            } else
                System.out.printf("Não é possivel ir para ai!\n");
        }
        return board[this.x][this.y];
    }

    public abstract void search();
}