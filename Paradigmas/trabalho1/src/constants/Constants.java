package src.constants;

public interface Constants {
    // Board Constants
    public static final int BOARD_SIZE = 5;
    public static final int BOARD_CENTER = 2;

    // Sector Types
    public static final int NORMAL = 0;
    public static final int HIDDEN = 1;
    public static final int PRIVATE = 2;

    // Sector Constants
    public static final int SIDES_QTD = 4;
    public static final int TOP = 0;
    public static final int RIGHT = 1;
    public static final int BOTTOM = 2;
    public static final int LEFT = 3;
    public static final int DOOR = 1;
    public static final int WALL = 0;

    // Printer constants
    public static final int Y_BASE[] = { 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4 };
    public static final int X_BASE[] = { 0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4 };
    public static final int BOARD_BASE[][] = {
            { ' ', ' ', ' ', ' ', '|', '-', '-', '-', '|', '-', '-', '-', '|', '-', '-', '-', '|', '-', '-', '-',
                    '|', '-', '-', '-', '|' },
            { '1', ' ', ' ', ' ', '|', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ',
                    'r', 'p', '\0', ' ', '|' },
            { ' ', ' ', ' ', ' ', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-',
                    '|', '-', 't', '-', '|' },
            { '2', ' ', ' ', ' ', '|', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ',
                    'r', 'p', '\0', ' ', '|' },
            { ' ', ' ', ' ', ' ', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-',
                    '|', '-', 't', '-', '|' },
            { '3', ' ', ' ', ' ', '|', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ',
                    'r', 'p', '\0', ' ', '|' },
            { ' ', ' ', ' ', ' ', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-',
                    '|', '-', 't', '-', '|' },
            { '4', ' ', ' ', ' ', '|', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ',
                    'r', 'p', '\0', ' ', '|' },
            { ' ', ' ', ' ', ' ', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-',
                    '|', '-', 't', '-', '|' },
            { '5', ' ', ' ', ' ', '|', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ', 'r', 'p', '\0', ' ',
                    'r', 'p', '\0', ' ', '|' },
            { ' ', ' ', ' ', ' ', '|', '-', '-', '-', '|', '-', '-', '-', '|', '-', '-', '-', '|', '-', '-', '-',
                    '|', '-', '-', '-', '|' },
    };
}
