package src.functions;

import java.util.ArrayList;
import java.util.Scanner;

import src.characters.*;
import src.constants.Constants;
import src.sectors.*;

public class PlayerActionsHandler implements Constants {
    // ---------------------------- Public Methods ----------------------------
    public void handle(Sector[][] board, Player[] players, int type, Scanner input) throws InterruptedException {
        ArrayList<String> possibleActions;
        SupportPlayer tempPlayer;
        String selectedAction;
        boolean performed;

        performed = false;
        possibleActions = players[type].verifyActions(board);

        System.out.printf("Selecione uma ação PLAYER %d (P%d)\n", type + 1, type + 1);
        for (String action : possibleActions)
            System.out.printf("%s - %s\n", action.substring(0, 1), action);

        while (!performed) {
            selectedAction = input.next();
            for (String action : possibleActions)
                if (action.startsWith(selectedAction))
                    performed = true;

            if (performed) {
                switch (selectedAction) {
                    case "A":
                        players[type].attack(board, input);
                        break;
                    case "S":
                        players[type].search(board);
                        break;
                    case "R":
                        if (players[type] instanceof SupportPlayer) {
                            tempPlayer = (SupportPlayer) players[type];
                            tempPlayer.recover((SimplePlayer) players[SIMPLE], input);
                        }
                        break;
                }
            } else {
                System.out.printf("Ação invalida\n");
            }
        }

    }
}
