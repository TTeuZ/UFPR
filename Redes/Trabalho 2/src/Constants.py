# Constants
LOCAL_NAMES = ["N1", "N2", "N3", "N4"]
DELIMITER = "~"
BUFFER_SIZE = 1024
TIMEOUT = 60
NUM_PLAYERS = 4
GAME_MAX_BET = 4
PLAYER_MAX_BET = 3
ROUNDS = 3

# Enum - Types
CONNECTION = -1
LIST = -2
CARDS = -3
BET = -4
SHOW = -5
MOVE = -6
RESULTS = -7
ROUND = -8
ALIVE = -9
END_GAME = -10
DEALER = -11

# Deck
CARDS_BY_HAND = 3
DECK = ['4C', '5C', '6C', '7C', 'QC', 'JC', 'KC', 'AC', '2C', '3C',
        '4E', '5E', '6E', '7E', 'QE', 'JE', 'KE', 'AE', '2E', '3E',
        '4O', '5O', '6O', '7O', 'QO', 'JO', 'KO', 'AO', '2O', '3O',
        '4P', '5P', '6P', '7P', 'QP', 'JP', 'KP', 'AP', '2P', '3P',]

POWER_SCALE = ['4', '5', '6', '7', 'Q', 'J', 'K', 'A', '2', '3']
GOAT_SCALE = ['O', 'E', 'C', 'P']