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
        int actualCycle;

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
        actualCycle = 0;

        // ---------------------------- Gerando mesa ----------------------------
        boardGenerator.generate(board);
        printer.print(board, players);

        // ---------------------------- Loop Principal ----------------------------
        while (actualCycle <= MAX_CYCLES) {
            // ---------------------------- Movimentação ----------------------------
            for (count = 0; count < players.length; ++count) {
                if (players[count].isAlive()) {
                    tempSector = players[count].move(board, input);
                    if (tempSector != null) {
                        tempSector.reachSector(players[count]);
                        printer.print(board, players);
                    }
                }
            }

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

            actualCycle++;
        }
        input.close();
    }
}
