package src.constants;

public interface Constants {
        // Game Constants
        public static final int MAX_CYCLES = 25;
        public static final int MAX_ACTIONS = 2;
        public static final int SIMPLE = 0;
        public static final int SUPPORT = 1;
        public static final int WAIT_TIME = 2;
        public static final int END_GAME = 25;

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

        // Player Constants
        public static final int P1_ATTACK = 2;
        public static final int P1_DEFENSE = 6;
        public static final int P2_ATTACK = 1;
        public static final int P2_DEFENSE = 7;

        // Printer constants
        public static final int BOARD_ROWS = 11;
        public static final int BOARD_COLS = 25;
        public static final int MENU_COLS = 15;
        public static final int Y_BASE[] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4 };
        public static final int X_BASE[] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4 };
        public static final char BOARD_BASE[][] = {
                        { ' ', ' ', ' ', ' ', '|', '-', '-', '-', '|', '-', '-', '-', '|', '-', '-', '-', '|', '-', '-',
                                        '-', '|', '-', '-', '-', '|' },
                        { '1', ' ', ' ', ' ', '|', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r',
                                        'p', '\0', '\0', 'r', 'p', '\0', '\0', '|' },
                        { ' ', ' ', ' ', ' ', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't',
                                        '-', '|', '-', 't', '-', '|' },
                        { '2', ' ', ' ', ' ', '|', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r',
                                        'p', '\0', '\0', 'r', 'p', '\0', '\0', '|' },
                        { ' ', ' ', ' ', ' ', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't',
                                        '-', '|', '-', 't', '-', '|' },
                        { '3', ' ', ' ', ' ', '|', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r',
                                        'p', '\0', '\0', 'r', 'p', '\0', '\0', '|' },
                        { ' ', ' ', ' ', ' ', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't',
                                        '-', '|', '-', 't', '-', '|' },
                        { '4', ' ', ' ', ' ', '|', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r',
                                        'p', '\0', '\0', 'r', 'p', '\0', '\0', '|' },
                        { ' ', ' ', ' ', ' ', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't', '-', '|', '-', 't',
                                        '-', '|', '-', 't', '-', '|' },
                        { '5', ' ', ' ', ' ', '|', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r', 'p', '\0', '\0', 'r',
                                        'p', '\0', '\0', 'r', 'p', '\0', '\0', '|' },
                        { ' ', ' ', ' ', ' ', '|', '-', '-', '-', '|', '-', '-', '-', '|', '-', '-', '-', '|', '-', '-',
                                        '-', '|', '-', '-', '-', '|' },
        };
        public static final char MENU_SAME_SECTOR_BASE[][] = {
                        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                        { ' ', ' ', 'S', 'e', 't', 'o', 'r', ' ', '[', 'x', ',', 'y', ']', ' ', ' ' },
                        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                        { '|', '-', '-', '-', '-', '-', '-', '*', '-', '-', '-', '-', '-', '-', '|' },
                        { '|', ' ', 'v', 'v', 'v', ' ', 'v', 'v', 'v', ' ', 'v', 'v', 'v', ' ', '|' },
                        { '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|' },
                        { '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*' },
                        { '|', ' ', ' ', 'p', '\0', ' ', ' ', ' ', ' ', 'p', '\0', ' ', ' ', ' ', '|' },
                        { '|', ' ', ' ', 'a', '/', 'd', ' ', ' ', ' ', 'a', '/', 'd', ' ', ' ', '|' },
                        { '|', '-', '-', '-', '-', '-', '-', '*', '-', '-', '-', '-', '-', '-', '|' },
                        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        };
        public static final char MENU_DIFF_SECTOR_BASE[][] = {
                        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                        { ' ', ' ', 'S', 'e', 't', 'o', 'r', ' ', '[', 'x', ',', 'y', ']', ' ', ' ' },
                        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
                        { '|', '-', '-', '-', '-', '-', '-', '*', '-', '-', '-', '-', '-', '-', '|' },
                        { '|', ' ', 'v', 'v', 'v', ' ', 'v', 'v', 'v', ' ', 'v', 'v', 'v', ' ', '|' },
                        { '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|' },
                        { '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*' },
                        { '|', ' ', ' ', 'p', '\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|' },
                        { '|', ' ', ' ', 'a', '/', 'd', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|' },
                        { '|', '-', '-', '-', '-', '-', '-', '*', '-', '-', '-', '-', '-', '-', '|' },
                        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        };
}
