package com.marketplace.utils;

import java.util.Scanner;

public class InputReader {
    private Scanner scanner;

    public InputReader(Scanner scanner) {
        this.scanner = scanner;
    }

    public String readString(String label) {
        String input = "";

        System.out.print(label + ": ");
        input += scanner.nextLine();
        return input;
    }

    public int readInt(String label) {
        System.out.print(label + ": ");
        while (!scanner.hasNextInt()) {
            System.out.println("Valor inválido. Por favor, insira um valor válido.");
            System.out.print(label + ": ");
            scanner.next();
        }
        int value = scanner.nextInt();
        scanner.nextLine();
        return value;
    }

    public float readFloat(String label) {
        System.out.print(label + ": ");
        while (!scanner.hasNextFloat()) {
            System.out.println("Valor inválido. Por favor, insira um valor válido.");
            System.out.print(label + ": ");
            scanner.next();
        }
        float value = scanner.nextFloat();
        scanner.nextLine();
        return value;
    }

    public boolean readBoolean(String label) {
        boolean isValid = false;
        String input = "";
        System.out.print(label + " (S/N): ");
        while (!isValid) {
            input = scanner.next();
            scanner.nextLine();

            if (!input.equals("S") && !input.equals("N")) {
                System.out.println("Valor inválido. Por favor, insira um valor válido.");
                System.out.print(label + " (S/N): ");
            } else {
                isValid = true;
            }
        }
        boolean value = input.equals("S") ? true : false;
        return value;
    }

    public <T extends Enum<T>> T readEnum(Class<T> enumType, String label) {
        System.out.print(label + " (" + enumOptions(enumType) + "): ");
        String input = scanner.nextLine().toUpperCase();

        try {
            return Enum.valueOf(enumType, input);
        } catch (IllegalArgumentException e) {
            System.out.println("Valor inválido. Por favor, insira um valor válido.");
            return readEnum(enumType, label);
        }
    }

    private <T extends Enum<T>> String enumOptions(Class<T> enumType) {
        StringBuilder options = new StringBuilder();
        for (Enum<T> value : enumType.getEnumConstants()) {
            options.append(value.name()).append("/");
        }
        return options.substring(0, options.length() - 1);
    }
}
