package src.characters;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

import src.sectors.*;

public abstract class Player extends Character {
    protected boolean canSearch;
    protected boolean canMove;

    // ---------------------------- Constructors ----------------------------
    public Player(int center, int attack, int defense) {
        super(center, center, attack, defense);
        this.setCanSearch(true);
        this.setCanMove(true);
    }

    // ---------------------------- Setters ----------------------------
    public void setCanSearch(boolean canSearch) {
        this.canSearch = canSearch;
    }

    public void setCanMove(boolean canMove) {
        this.canMove = canMove;
    }

    // ---------------------------- Private Methods ----------------------------
    private void blindAttack(Virus virus) {
        Random random;

        random = new Random();
        if ((random.nextInt(6) + 1) % 2 == 0) {
            virus.reciveDamage(this.attack);
            System.out.printf("Acertou o ataque!\n");
        } else
            System.out.printf("Errou o ataque!\n");
    }

    // ---------------------------- Public Methods ----------------------------
    public abstract ArrayList<String> verifyActions(Sector[][] board);

    public Sector sector(Sector[][] board) {
        return board[this.x][this.y];
    }

    public void attack(Sector[][] board, Scanner input) throws InterruptedException {
        ArrayList<Virus> aliveVirus;
        int count, selectedEnemy;
        boolean attacked;

        attacked = false;
        count = 0;

        aliveVirus = new ArrayList<Virus>();
        for (Virus virus : this.sector(board).getEnemies())
            if (virus.isAlive())
                aliveVirus.add(virus);

        System.out.printf("Qual inimigo deseja atacar?\n");
        for (Virus virus : aliveVirus)
            System.out.printf("%d - %d/%d\n", count++, virus.getAttack(), virus.getDefense());

        while (!attacked) {
            try {
                selectedEnemy = input.nextInt();
                if (selectedEnemy < aliveVirus.size())
                    attacked = true;

                if (attacked) {
                    System.out.printf("Atacando...\n");
                    TimeUnit.SECONDS.sleep(WAIT_TIME);

                    if (aliveVirus.get(selectedEnemy).isCanAvoid())
                        this.blindAttack(aliveVirus.get(selectedEnemy));
                    else {
                        aliveVirus.get(selectedEnemy).reciveDamage(this.attack);
                        System.out.printf("Acertou o ataque!\n");
                    }

                    TimeUnit.SECONDS.sleep(WAIT_TIME);
                } else
                    System.out.printf("Inimigo invalido!\n");
            } catch (InputMismatchException e) {
                System.out.printf("Inimigo invalido!\n");
                input.nextLine();
            }
        }
    }

    public Sector move(Sector[][] board, Scanner input) {
        ArrayList<String> possibleMoves;
        String selectedMove;
        boolean moved, validMove;

        moved = validMove = false;
        possibleMoves = this.sector(board).verifyMoves();

        for (String move : possibleMoves)
            System.out.printf("%s - %s\n", move.substring(0, 1), move);

        while (!moved) {
            selectedMove = input.next();
            for (String move : possibleMoves)
                if (move.startsWith(selectedMove))
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
        return this.sector(board);
    }

    public void search(Sector[][] board) throws InterruptedException {
        Random random;
        random = new Random();

        System.out.printf("Procurando...\n");
        TimeUnit.SECONDS.sleep(WAIT_TIME);

        switch (random.nextInt(6)) {
            case 3:
                System.out.printf("Bust de 1 DEF encontrado\n");
                this.setDefense(this.defense + 1);
                break;
            case 4:
                System.out.printf("Bust de 2 DEF encontrado\n");
                this.setDefense(this.defense + 2);
                break;
            case 5:
                System.out.printf("Dano em area!\n");
                for (Virus virus : this.sector(board).getEnemies())
                    virus.reciveDamage(1);
                break;
            default:
                System.out.printf("Nada encontrado\n");
                break;
        }

        TimeUnit.SECONDS.sleep(WAIT_TIME);
    }
}