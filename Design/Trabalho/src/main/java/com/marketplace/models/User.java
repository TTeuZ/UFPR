package com.marketplace.models;

import java.util.ArrayList;

import com.marketplace.enums.ReasonType;

public class User {
    private static int nextId = 1;

    private int id;
    private String firstName;
    private String lastName;
    private String email;
    private String photo;
    private boolean admin;
    private ChatList chats;
    private ReportList reports;

    public User(String firstName, String lastName, String email, String photo, boolean admin) {
        this.id = User.nextId++;
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.photo = photo;
        this.admin = admin;
        this.chats = new ChatList();
        this.reports = new ReportList();
    }

    public int getId() {
        return this.id;
    }

    public String getName() {
        return this.firstName + " " + this.lastName;
    }

    public ArrayList<Product> getProducts() {
        ArrayList<Product> products = new ArrayList<Product>();
        ProductList list = ProductList.getInstance();

        for (Product product : list.getProducts()) {
            if (product.getSeller().getId() == this.id)
                products.add(product);
        }

        return products;
    }

    public ChatList getChats() {
        return this.chats;
    }

    public void addChat(Chat chat) {
        this.chats.add(chat);
    }

    public void addReport(ReasonType reason, String description) {
        Report report = new Report(reason, description);
        this.reports.add(report);
    }

    public String toString(int level) {
        String tabbing = "\n";

        for (int i = 0; i < level; ++i)
            tabbing += "\t";

        String result = tabbing + "id: " + this.id +
                tabbing + "name: " + this.firstName + " " + this.lastName +
                tabbing + "email: " + this.email +
                tabbing + "admin: " + this.admin;

        return result;
    }
}