package src.functions;

import java.util.Random;

import src.constants.Constants;
import src.sectors.*;

public class BoardGenerator implements Constants {
    // ---------------------------- Private Methods ----------------------------
    /**
     * Instancia um novo Sector de maneira randomica
     */
    private Sector generateRandomSector(int x, int y) {
        Random random;
        int sectorType;
        Sector temp;

        random = new Random();
        sectorType = random.nextInt(3);
        switch (sectorType) {
            case NORMAL:
                temp = new NormalSector(x, y);
                break;
            case HIDDEN:
                temp = new HiddenSector(x, y);
                break;
            case PRIVATE:
                temp = new PrivateSector(x, y);
                break;
            default:
                temp = new NormalSector(x, y);
                break;
        }
        return temp;
    }

    /**
     * Instancia um novo array de lados fazendo com que todos assumam o mesmo valor
     * (DOOR ou WALL)
     */
    private int[] generateSides(int type) {
        int[] temp;

        temp = new int[SIDES_QTD];
        temp[TOP] = temp[RIGHT] = temp[BOTTOM] = temp[LEFT] = type;

        return temp;
    }

    /**
     * Instancia um novo array de lados, com cada lado podendo ter um tipo diferente
     */
    private int[] generateSides(int top, int right, int bottom, int left) {
        int[] temp;

        temp = new int[SIDES_QTD];
        temp[TOP] = top;
        temp[RIGHT] = right;
        temp[BOTTOM] = bottom;
        temp[LEFT] = left;
        return temp;
    }

    // ---------------------------- Public Methods ----------------------------
    /**
     * Responsável por gerar o mapa do jogo atual de maneira totalmente randomica.
     * Garante que a fonte de infecção não seja no centre e nem nas mesma
     * linha/coluna que o centro
     * Garante que o centro tera as 4 portas
     * Garante que todas as laterias serão paredes.
     * Gera de forma sequencial cada setor do mapa 5 x 5, verificando os setores ja
     * instanciados nas redondezas, para garantir que lados comparitlhados tenham o
     * mesmo tipo.
     * A verificação em sua maioria ocorre para a parede de cima e a para a parede
     * da esquerda.
     * Isso ocorre devido ao funcionamento do loop de costrução, onde sempre teremos
     * os elementos
     * acima e da esquerda instanciados antes, salvo exceções que são tradadas
     * durante o loop.
     */
    public void generate(Sector[][] board) {
        Random random;
        int x, y, sourceX, sourceY;
        int top, right, bottom, left;

        random = new Random();

        // gerando a fonte de infecção
        sourceX = sourceY = BOARD_CENTER;
        while (sourceX == BOARD_CENTER || sourceY == BOARD_CENTER) {
            sourceX = random.nextInt(BOARD_SIZE);
            sourceY = random.nextInt(BOARD_SIZE);
        }

        // gerando os setores
        for (x = 0; x < BOARD_SIZE; ++x)
            for (y = 0; y < BOARD_SIZE; ++y) {
                if (sourceX == x && sourceY == y)
                    board[x][y] = new NormalSector(x, y, true, false, null);
                else if (x == BOARD_CENTER && y == BOARD_CENTER)
                    board[x][y] = new NormalSector(x, y, false, true, generateSides(DOOR));
                else {
                    board[x][y] = generateRandomSector(x, y);
                }
            }

        // Gerando os lados das bordas do mapa
        board[0][0].setSides(generateSides(WALL, random.nextInt(2), random.nextInt(2), WALL));
        board[0][BOARD_SIZE - 1].setSides(generateSides(WALL, WALL, random.nextInt(2), random.nextInt(2)));
        board[BOARD_SIZE - 1][0].setSides(generateSides(random.nextInt(2), random.nextInt(2), WALL, WALL));
        board[BOARD_SIZE - 1][BOARD_SIZE - 1].setSides(generateSides(random.nextInt(2), WALL, WALL, random.nextInt(2)));

        // Gerando os lados de cada setor
        for (x = 0; x < BOARD_SIZE; ++x)
            for (y = 0; y < BOARD_SIZE; ++y) {
                if (board[x][y].getSides() == null) {
                    if (x == 0) {
                        top = WALL;
                        right = board[x][y + 1].getSides() != null ? board[x][y + 1].getSides()[LEFT]
                                : random.nextInt(2);
                        bottom = random.nextInt(2);
                        left = board[x][y - 1].getSides()[RIGHT];
                    } else if (x == BOARD_SIZE - 1) {
                        top = board[x - 1][y].getSides()[BOTTOM];
                        right = board[x][y + 1].getSides() != null ? board[x][y + 1].getSides()[LEFT]
                                : random.nextInt(2);
                        bottom = WALL;
                        left = board[x][y - 1].getSides()[RIGHT];
                    } else if (y == 0) {
                        top = board[x - 1][y].getSides()[BOTTOM];
                        right = random.nextInt(2);
                        bottom = board[x + 1][y].getSides() != null ? board[x + 1][y].getSides()[TOP]
                                : random.nextInt(2);
                        left = WALL;
                    } else if (y == BOARD_SIZE - 1) {
                        top = board[x - 1][y].getSides()[BOTTOM];
                        right = WALL;
                        bottom = board[x + 1][y].getSides() != null ? board[x + 1][y].getSides()[TOP]
                                : random.nextInt(2);
                        left = board[x][y - 1].getSides()[RIGHT];
                    } else {
                        top = board[x - 1][y].getSides() != null ? board[x - 1][y].getSides()[BOTTOM]
                                : random.nextInt(2);
                        right = board[x][y + 1].getSides() != null ? board[x][y + 1].getSides()[LEFT]
                                : random.nextInt(2);
                        bottom = board[x + 1][y].getSides() != null ? board[x + 1][y].getSides()[TOP]
                                : random.nextInt(2);
                        left = board[x][y - 1].getSides() != null ? board[x][y - 1].getSides()[RIGHT]
                                : random.nextInt(2);
                    }
                    board[x][y].setSides(generateSides(top, right, bottom, left));
                }
            }
    }
}