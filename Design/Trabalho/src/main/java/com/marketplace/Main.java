package com.marketplace;

import com.marketplace.views.Home;

public class Main {
    public static void main(String[] args) {
        Home homeScreen = new Home();
        homeScreen.showOptions();
        homeScreen.listenCommand();
    }
}