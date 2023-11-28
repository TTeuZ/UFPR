package com.marketplace.views;

import java.util.Scanner;

import com.marketplace.utils.InputReader;

public abstract class Interface {
    protected int numberOfOptions;
    protected Scanner keyboard;

    private boolean checkOption(int option) {
        boolean isValid = option >= 1 && option <= this.numberOfOptions;

        if (!isValid)
            System.out.println("OPÇÃO INVÁLIDA: Selecione novamente.\n");

        return isValid;
    }

    private boolean isExit(int option) {
        return option == this.numberOfOptions;
    }

    public void listenCommand() {
        boolean isValid;
        int option = -1;
        this.keyboard = new Scanner(System.in);
        InputReader reader = new InputReader(this.keyboard);

        option = reader.readInt("Opção");

        while (!this.isExit(option)) {
            isValid = this.checkOption(option);

            if (isValid)
                this.handleOption(option);

            option = reader.readInt("Opção");
        }
    }

    public abstract void showOptions();

    public abstract void handleOption(int option);
}
