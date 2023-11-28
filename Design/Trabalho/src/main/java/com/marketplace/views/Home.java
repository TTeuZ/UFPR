package com.marketplace.views;

public class Home extends Interface {
    public Home() {
        this.numberOfOptions = 4;
    }

    public void showOptions() {
        System.out.println("\nBem-vindo ao Marketplace");
        System.out.println("1 - Explorar");
        System.out.println("2 - Minha Loja");
        System.out.println("3 - Conversas");
        System.out.println("4 - Sair\n");
    }

    public void handleOption(int option) {
        switch (option) {
            case 1:
                this.goToExplore();
                break;
            case 2:
                this.goToMyStore();
                break;
            case 3:
                this.goToChats();
                break;
            default:
                System.exit(0);
        }
    }

    private void goToExplore() {
        Explore exploreScreen = new Explore();

        exploreScreen.showOptions();
        exploreScreen.listenCommand();

        this.showOptions();
    }

    private void goToMyStore() {
        MyStore myStoreScreen = new MyStore();

        myStoreScreen.showOptions();
        myStoreScreen.listenCommand();

        this.showOptions();
    }

    private void goToChats() {
        Chats chatsScreen = new Chats();

        chatsScreen.showOptions();
        chatsScreen.listenCommand();

        this.showOptions();
    }
}