import java.util.Scanner;

import src.characters.*;
import src.constants.*;
import src.functions.*;
import src.sectors.*;

//  Autor: Paulo Mateus Luza Alves GRR20203945

public class Main implements Constants {
    public static void main(String[] args) throws InterruptedException {
        // Classes funcionais
        BoardGenerator boardGenerator;
        Printer printer;
        PlayerActionsHandler playerActionsHandler;
        Scanner input;

        // Atributos do jogo
        Sector[][] board;
        Player[] players;
        int actualCycle;

        // Variaveis temporarias
        Sector tempSector;
        int count;

        // Inicialização dos funcionais
        boardGenerator = new BoardGenerator();
        printer = new Printer();
        playerActionsHandler = new PlayerActionsHandler();
        input = new Scanner(System.in);

        // Inicialização dos atributos
        board = new Sector[BOARD_SIZE][BOARD_SIZE];
        players = new Player[2];
        players[SIMPLE] = new SimplePlayer(BOARD_CENTER, P1_ATTACK, P1_DEFENSE, true, true);
        players[SUPPORT] = new SupportPlayer(BOARD_CENTER, P2_ATTACK, P2_DEFENSE, true, true);
        actualCycle = 0;

        // Gerando o mesa do jogo
        boardGenerator.generate(board);
        printer.print(board, players);

        // Loop principal
        while (actualCycle <= MAX_CYCLES) {
            // ---------------------------- Movimentação ----------------------------
            tempSector = players[SIMPLE].move(board, input);
            if (tempSector != null) {
                tempSector.reachSector(players[SIMPLE]);
                printer.print(board, players);
            }
            tempSector = players[SUPPORT].move(board, input);
            if (tempSector != null) {
                tempSector.reachSector(players[SUPPORT]);
                printer.print(board, players);
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

            actualCycle++;
        }
        input.close();
    }
}
