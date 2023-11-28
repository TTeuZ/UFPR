package com.marketplace.views;

import java.util.ArrayList;
import java.util.Iterator;

import com.marketplace.models.Session;
import com.marketplace.models.User;
import com.marketplace.models.Product;

public class MyStore extends Interface {
    public MyStore() {
        this.numberOfOptions = 3;
    }

    public void showOptions() {
        System.out.println("\nMinha Loja");
        System.out.println("1 - Meus Produtos");
        System.out.println("2 - Adicionar Produtos");
        System.out.println("3 - Voltar\n");
    }

    public void handleOption(int option) {
        switch (option) {
            case 1:
                this.showProducts();
                break;
            case 2:
                this.addProduct();
                break;
            default:
                break;
        }
    }

    private void showProducts() {
        Session session = Session.getInstance();
        User user = session.getCurrentUser();
        ArrayList<Product> products = user.getProducts();

        System.out.println("\nPRODUTOS:\n");
        Iterator<Product> iterator = products.iterator();
        while (iterator.hasNext()) {
            System.out.println(iterator.next());
            System.out.print("\n");
        }

        if (products.size() == 0) {
            System.out.println("Você não possui nenhum produto.");
        }

        this.showOptions();
    }

    private void addProduct() {
        CreateProduct createProductScreen = new CreateProduct();

        createProductScreen.showOptions();
        createProductScreen.listenCommand();

        this.showOptions();
    }
}