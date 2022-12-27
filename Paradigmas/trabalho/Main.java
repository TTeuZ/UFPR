import src.characters.*;
import src.constants.*;
import src.functions.*;
import src.sectors.*;

//  Autor: Paulo Mateus Luza Alves GRR20203945

public class Main implements Constants {
    public static void main(String[] args) {
        // Classes funcionais
        BoardGenerator boardGenerator;
        Printer printer;

        // Atributos do jogo
        Sector[][] board;
        SimplePlayer playerOne;
        SupportPlayer playerTwo;
        int actualCycle;

        // Inicialização dos funcionais
        boardGenerator = new BoardGenerator();
        printer = new Printer();
        // input = new Scanner(System.in);

        // Inicialização dos atributos
        board = new Sector[BOARD_SIZE][BOARD_SIZE];
        playerOne = new SimplePlayer(BOARD_CENTER, P1_ATTACK, P1_DEFENSE, true, true);
        playerTwo = new SupportPlayer(BOARD_CENTER, P2_ATTACK, P2_DEFENSE, true, true);
        actualCycle = 0;

        // Gerando o mesa do jogo
        boardGenerator.generate(board);
        printer.print(board, playerOne, playerTwo);

        // Loop principal
        while (actualCycle <= MAX_CYCLES) {
            playerOne.move(board).reachSector();
            printer.print(board, playerOne, playerTwo);

            playerTwo.move(board).reachSector();
            printer.print(board, playerOne, playerTwo);

            actualCycle++;
        }
    }
}
