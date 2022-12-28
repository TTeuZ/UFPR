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
        isDoor = board[realX][realY].getSides()[side] == DOOR;
        if (side == TOP)
            isFound = board[realX][realY].isFound() || board[realX - 1][realY].isFound();
        else
            isFound = board[realX][realY].isFound() || board[realX][realY + 1].isFound();

        temp = side == TOP ? '-' : '|';
        if (isFound && isDoor)
            temp = '*';

        return temp;
    }

    public String verifyPlayer(Sector[][] board, Player[] players, int x, int y) {
        int realX, realY;
        String temp;

        realX = X_BASE[x];
        realY = Y_BASE[y];

        temp = "   ";
        if (board[realX][realY].isSource())
            temp = " X ";
        else if (players[SIMPLE].getX() == realX && players[SIMPLE].getY() == realY && players[SUPPORT].getX() == realX
                && players[SUPPORT].getY() == realY)
            temp = "P12";
        else if (players[SIMPLE].getX() == realX && players[SIMPLE].getY() == realY)
            temp = "P1 ";
        else if (players[SUPPORT].getX() == realX && players[SUPPORT].getY() == realY)
            temp = "P2 ";

        return temp;
    }

    // ---------------------------- Public Methods ----------------------------
    public void print(Sector[][] board, Player players[]) {
        int playerCount, attackCount, defenseCount;
        boolean sameSector;
        Sector tempSector;
        int x, y, count;

        playerCount = 1;
        attackCount = defenseCount = 0;

        if (players[SIMPLE].getX() == players[SUPPORT].getX() && players[SIMPLE].getY() == players[SUPPORT].getY())
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
                    System.out.printf("%s", verifyPlayer(board, players, x, y - 5));
                else
                    System.out.printf("%c", BOARD_BASE[x][y]);
            }

            // Espaçamento
            System.out.printf("     ");

            // Print do menu de cada jogador
            if (sameSector) {
                tempSector = board[players[SIMPLE].getX()][players[SIMPLE].getY()];
                for (y = 0; y < MENU_COLS; ++y) {
                    if (MENU_SAME_SECTOR_BASE[x][y] == 'x')
                        System.out.printf("%d", players[SIMPLE].getX());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'y')
                        System.out.printf("%d", players[SIMPLE].getY());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'p')
                        System.out.printf("P%d", playerCount++);
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'a')
                        System.out.printf("%d", players[attackCount++].getAttack());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'd')
                        System.out.printf("%d", players[defenseCount++].getDefense());
                    else
                        System.out.printf("%c", MENU_SAME_SECTOR_BASE[x][y]);
                }
            } else {
                for (count = 0; count < players.length; ++count) {
                    for (y = 0; y < MENU_COLS; ++y) {
                        tempSector = board[players[count].getX()][players[count].getY()];
                        if (MENU_DIFF_SECTOR_BASE[x][y] == 'x')
                            System.out.printf("%d", players[count].getX());
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'y')
                            System.out.printf("%d", players[count].getY());
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'p')
                            System.out.printf("P%d", count + 1);
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'a')
                            System.out.printf("%d", players[count].getAttack());
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'd')
                            System.out.printf("%d", players[count].getDefense());
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
