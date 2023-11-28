package com.marketplace.models;

public class Session {
    private static Session instance;
    private User currentUser;

    private Session() {
        UserList users = UserList.getInstance();
        this.currentUser = users.getRandomUser();
    };

    public static synchronized Session getInstance() {
        if (instance == null)
            instance = new Session();
        return instance;
    }

    public User getCurrentUser() {
        return this.currentUser;
    }
}