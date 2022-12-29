import java.util.Scanner;

import src.characters.*;
import src.constants.*;
import src.functions.*;
import src.sectors.*;

//  Autor: Paulo Mateus Luza Alves GRR20203945

public class Main implements Constants {
    public static void main(String[] args) throws InterruptedException {
        // ---------------------------- Classes Funcionais ----------------------------
        BoardGenerator boardGenerator;
        Printer printer;
        PlayerActionsHandler playerActionsHandler;
        Scanner input;

        // ---------------------------- Atributos do jogo ----------------------------
        Sector[][] board;
        Player[] players;
        int actualCycle, deadQtd;
        boolean winner;

        // ---------------------------- temporarias ----------------------------
        Sector tempSector;
        int count;

        // ---------------------------- Inic. dos Func. ----------------------------
        boardGenerator = new BoardGenerator();
        printer = new Printer();
        playerActionsHandler = new PlayerActionsHandler();
        input = new Scanner(System.in);

        // ---------------------------- Inic. dos Atrib. ----------------------------
        board = new Sector[BOARD_SIZE][BOARD_SIZE];
        players = new Player[2];
        players[SIMPLE] = new SimplePlayer(BOARD_CENTER, P1_ATTACK, P1_DEFENSE);
        players[SUPPORT] = new SupportPlayer(BOARD_CENTER, P2_ATTACK, P2_DEFENSE);
        actualCycle = deadQtd = 0;
        winner = false;

        // ---------------------------- Gerando mesa ----------------------------
        boardGenerator.generate(board);
        printer.print(board, players);

        // ---------------------------- Loop Principal ----------------------------
        while (actualCycle < MAX_CYCLES && !winner) {
            // ---------------------------- Movimentação ----------------------------
            for (count = 0; count < players.length; ++count) {
                if (players[count].isAlive()) {
                    tempSector = players[count].move(board, input);
                    if (tempSector != null) {
                        winner = tempSector.reachSector(players[count]);
                        printer.print(board, players);
                        if (winner) {
                            actualCycle = END_GAME;
                            break;
                        }
                    }
                }
            }

            if (winner)
                break;

            // ---------------------------- Ações dos jogadores ---------------------------
            for (count = 0; count < MAX_ACTIONS; ++count) {
                playerActionsHandler.handle(board, players, SIMPLE, input);
                printer.print(board, players);
            }
            for (count = 0; count < MAX_ACTIONS; ++count) {
                playerActionsHandler.handle(board, players, SUPPORT, input);
                printer.print(board, players);
            }

            // ---------------------------- Ataque dos virus ---------------------------
            for (count = 0; count < players.length; ++count) {
                tempSector = players[count].sector(board);
                for (Virus virus : tempSector.getEnemies()) {
                    if (virus.isAlive()) {
                        virus.attack(players[count]);
                        printer.print(board, players);
                    }
                }
            }

            // ---------------------------- Att. de Status ---------------------------
            deadQtd = 0;
            for (count = 0; count < players.length; ++count) {
                if (players[count].isAlive()) {
                    tempSector = players[count].sector(board);
                    players[count].setCanMove(!tempSector.hasAliveEnemies());
                } else
                    deadQtd++;
            }

            if (deadQtd == 2)
                actualCycle = END_GAME;
            else
                actualCycle++;
        }

        if (winner)
            printer.wonGame();
        else
            printer.loseGame();
        input.close();
    }
}
