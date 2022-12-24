import src.constants.Constants;
import src.functions.*;
import src.sectors.*;

//  Autor: Paulo Mateus Luza Alves GRR20203945

public class Main implements Constants {
    public static void main(String[] args) {
        BoardGenerator boardGenerator;
        Printer printer;
        Sector[][] board = new Sector[BOARD_SIZE][BOARD_SIZE];

        boardGenerator = new BoardGenerator();
        printer = new Printer();

        boardGenerator.generate(board);
        printer.print(board);
    }
}
