package src.functions;

import src.characters.*;
import src.constants.Constants;
import src.sectors.*;

public class Printer implements Constants {
    // ---------------------------- Private Methods ----------------------------
    public char verifyWall(Sector[][] board, int x, int y, int side) {
        int realX, realY;
        boolean isFound, isDoor;
        char temp;

        realX = X_BASE[x];
        realY = Y_BASE[y];
        isDoor = board[realX][realY].getSides()[side] == 1;
        isFound = board[realX][realY].isFound();

        temp = side == TOP ? '-' : '|';
        if (isFound && isDoor)
            temp = '*';

        return temp;
    }

    public String verifyPlayer(Sector[][] board, SimplePlayer playerOne, SupportPlayer playerTwo, int x, int y) {
        int realX, realY;
        String temp;

        realX = X_BASE[x];
        realY = Y_BASE[y];

        temp = "   ";
        if (board[realX][realY].isSource())
            temp = " X ";
        else if (playerOne.getX() == realX && playerOne.getY() == realY && playerTwo.getX() == realX
                && playerTwo.getY() == realY)
            temp = "P12";
        else if (playerOne.getX() == realX && playerOne.getY() == realY)
            temp = "P1 ";
        else if (playerTwo.getX() == realX && playerTwo.getY() == realY)
            temp = "P2 ";

        return temp;
    }

    // ---------------------------- Public Methods ----------------------------
    public void print(Sector[][] board, SimplePlayer playerOne, SupportPlayer playerTwo) {
        int x, y, count;
        Player tempArray[];
        boolean sameSector;

        tempArray = new Player[2];
        tempArray[0] = playerOne;
        tempArray[1] = playerTwo;
        count = 0;

        if (playerOne.getX() == playerTwo.getX() && playerOne.getY() == playerTwo.getY())
            sameSector = true;
        else
            sameSector = false;


        // verificar se o P1 e o P2 estão no mesmo setor
        // armazenar os inimigos do setor, ou dos setores para o print

        System.out.println("----------------------------");
        System.out.println("|   Antivìrus por um dia   |");
        System.out.println("----------------------------");
        System.out.println("      1   2   3   4   5");
        for (x = 0; x < BOARD_ROWS; ++x) {
            for (y = 0; y < BOARD_COLS; ++y) {
                if (BOARD_BASE[x][y] == 't')
                    System.out.printf("%c", verifyWall(board, x, y - 5, TOP));
                else if (BOARD_BASE[x][y] == 'r')
                    System.out.printf("%c", verifyWall(board, x, y - 5, RIGHT));
                else if (BOARD_BASE[x][y] == 'p')
                    System.out.printf("%s", verifyPlayer(board, playerOne, playerTwo, x, y - 5));
                else
                    System.out.printf("%c", BOARD_BASE[x][y]);
            }

            if (sameSector) {
                for (y = 0; y < MENU_SAME_SECTOR_COLS; ++y) {
                    if (MENU_SAME_SECTOR_BASE[x][y] == 'x')
                        System.out.printf("%d", playerOne.getX());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'y')
                        System.out.printf("%d", playerOne.getY());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'p') {
                        System.out.printf("P%d", count + 1);
                        if (count == 1) count = 0;
                        count++;
                    } else if (MENU_SAME_SECTOR_BASE[x][y] == 'a') {
                        System.out.printf("%d", tempArray[count].getAttack());
                    } else if (MENU_SAME_SECTOR_BASE[x][y] == 'd') {
                        System.out.printf("%d", tempArray[count].getDefense());
                        if (count == 1) count = 0;
                        count++;
                    }
                    else 
                        System.out.printf("%c", MENU_SAME_SECTOR_BASE[x][y]);
                }
            } else {

            }

            System.out.printf("\n");
        }
    }
}
