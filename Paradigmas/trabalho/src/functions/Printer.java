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
        int playerCount, attackCount, defenseCount;
        boolean sameSector;
        Player tempArray[];
        Sector tempSector;
        int x, y, count;

        tempArray = new Player[2];
        tempArray[0] = playerOne;
        tempArray[1] = playerTwo;

        playerCount = 1;
        attackCount = defenseCount = 0;

        if (playerOne.getX() == playerTwo.getX() && playerOne.getY() == playerTwo.getY())
            sameSector = true;
        else
            sameSector = false;

        System.out.println("----------------------------");
        System.out.println("|   Antivìrus por um dia   |");
        System.out.println("----------------------------");
        System.out.println("      1   2   3   4   5");
        for (x = 0; x < BOARD_ROWS; ++x) {
            // Print da mesa do jogo
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

            // Espaçamento
            System.out.printf("     ");

            // Print do menu de cada jogador
            if (sameSector) {
                tempSector = board[playerOne.getX()][playerOne.getY()];
                for (y = 0; y < MENU_COLS; ++y) {
                    if (MENU_SAME_SECTOR_BASE[x][y] == 'x')
                        System.out.printf("%d", playerOne.getX());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'y')
                        System.out.printf("%d", playerOne.getY());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'p')
                        System.out.printf("P%d", playerCount++);
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'a')
                        System.out.printf("%d", tempArray[attackCount++].getAttack());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'd')
                        System.out.printf("%d", tempArray[defenseCount++].getDefense());
                    else
                        System.out.printf("%c", MENU_SAME_SECTOR_BASE[x][y]);
                }
            } else {
                for (count = 0; count < tempArray.length; ++count) {
                    for (y = 0; y < MENU_COLS; ++y) {
                        tempSector = board[tempArray[count].getX()][tempArray[count].getY()];
                        if (MENU_DIFF_SECTOR_BASE[x][y] == 'x')
                            System.out.printf("%d", tempArray[count].getX());
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'y')
                            System.out.printf("%d", tempArray[count].getY());
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'p')
                            System.out.printf("P1");
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'a')
                            System.out.printf("%d", tempArray[count].getAttack());
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'd')
                            System.out.printf("%d", tempArray[count].getDefense());
                        else
                            System.out.printf("%c", MENU_DIFF_SECTOR_BASE[x][y]);
                    }
                    // Espaçamento
                    System.out.printf("   ");
                }
            }
            System.out.printf("\n");
        }
    }
}
