package src.functions;

import java.util.ArrayList;

import src.characters.*;
import src.constants.Constants;
import src.sectors.*;

public class Printer implements Constants {
    // ---------------------------- Private Methods ----------------------------
    /**
     * A partir da base de print do mapa, juntamente com a base para os eixos X e Y,
     * verifica se o setor atual, na posição indicada possui uma porta ou uma parede
     */
    private char verifyWall(Sector[][] board, int x, int y, int side) {
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

    /**
     * A partir da base de print do mapa, juntamente com a base para os eixos X e Y,
     * verifica se o setor atual, na posição indicada existem um ou mais jogadores
     * ou se o setor é a fonte
     */
    private String verifyPlayer(Sector[][] board, Player[] players, int x, int y) {
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

    /**
     * A partir do virusCount enviado pela função print, verifica se, de acordo com
     * o contador, no momento, no menu, existe ainda algum virus para ser printado,
     * e se sim, qual dos virus do setor e se temos que printar seu ataque ou sua
     * defesa. Como o contador vai de 0 a 8, utilizamos 0 / 3 para sabermos o index
     * do virus dentro da lista (0 a 2) e o % 3 para sabermos se temos que printar,
     * ataque, '/' ou defesa
     */
    private char verifyVirus(Sector sector, int count) {
        ArrayList<Virus> enemies;
        int atribute, index;
        char temp;

        temp = ' ';
        atribute = count % 3;
        index = (int) Math.floor(count / 3);
        enemies = sector.getEnemies();

        if (!enemies.isEmpty() && index < enemies.size()) {
            switch (atribute) {
                case 0:
                    temp = (char) (enemies.get(index).getAttack() + '0');
                    break;
                case 1:
                    temp = '/';
                    break;
                case 2:
                    temp = (char) (enemies.get(index).getDefense() + '0');
                    break;
            }
        }
        return temp;
    }

    // ---------------------------- Public Methods ----------------------------
    /**
     * Printa o mapa e o menu lateral no terminal.
     * Utiliza Arrays de base para o print, os percurrendo durante os laçoes,
     * e de acordo com as flags posicionadas nessa base, realiza as verificações
     * necessariárias para realizar o print correto da situação do jogo
     */
    public void print(Sector[][] board, Player players[]) {
        int playerCount, attackCount, defenseCount, virusCount;
        boolean sameSector;
        Sector tempSector;
        int x, y, count;

        playerCount = 1;
        attackCount = defenseCount = virusCount = 0;

        if (players[SIMPLE].getX() == players[SUPPORT].getX() && players[SIMPLE].getY() == players[SUPPORT].getY())
            sameSector = true;
        else
            sameSector = false;

        // Limpando a tela antes de printar novamente
        System.out.print("\033[H\033[2J");
        System.out.flush();

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
                        System.out.printf("%d", players[SIMPLE].getX() + 1);
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'y')
                        System.out.printf("%d", players[SIMPLE].getY() + 1);
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'p')
                        System.out.printf("P%d", playerCount++);
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'a')
                        System.out.printf("%d", players[attackCount++].getAttack());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'd')
                        System.out.printf("%d", players[defenseCount++].getDefense());
                    else if (MENU_SAME_SECTOR_BASE[x][y] == 'v')
                        System.out.printf("%c", verifyVirus(tempSector, virusCount++));
                    else
                        System.out.printf("%c", MENU_SAME_SECTOR_BASE[x][y]);
                }
            } else {
                for (count = 0; count < players.length; ++count) {
                    tempSector = board[players[count].getX()][players[count].getY()];
                    for (y = 0; y < MENU_COLS; ++y) {
                        if (MENU_DIFF_SECTOR_BASE[x][y] == 'x')
                            System.out.printf("%d", players[count].getX() + 1);
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'y')
                            System.out.printf("%d", players[count].getY() + 1);
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'p')
                            System.out.printf("P%d", count + 1);
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'a')
                            System.out.printf("%d", players[count].getAttack());
                        else if (MENU_DIFF_SECTOR_BASE[x][y] == 'd')
                            System.out.printf("%d", players[count].getDefense());
                        else if (MENU_SAME_SECTOR_BASE[x][y] == 'v')
                            System.out.printf("%c", verifyVirus(tempSector, virusCount++));
                        else
                            System.out.printf("%c", MENU_DIFF_SECTOR_BASE[x][y]);
                    }
                    virusCount = 0;
                    // Espaçamento
                    System.out.printf("   ");
                }
            }
            System.out.printf("\n");
        }
    }

    public void loseGame() {
        System.out.println("----------------------------");
        System.out.println("|       Voce Perdeu!       |");
        System.out.println("----------------------------");
    }

    public void wonGame(int whoHasWon) {
        System.out.println("----------------------------");
        System.out.printf("|        P%d  Ganhou!       |\n", whoHasWon);
        System.out.println("----------------------------");
    }
}
