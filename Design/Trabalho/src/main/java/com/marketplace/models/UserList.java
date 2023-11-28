package com.marketplace.models;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

import javax.json.JsonObject;

import com.marketplace.interfaces.Searchable;

public class UserList extends Loadable implements Searchable<User> {
    private static UserList instance;
    private ArrayList<User> users;

    private UserList() {
        this.users = new ArrayList<User>();
        this.loadData("src/main/java/com/marketplace/data/users.json");
    }

    public static synchronized UserList getInstance() {
        if (instance == null)
            instance = new UserList();

        return instance;
    }

    public ArrayList<User> getUsers() {
        return this.users;
    }

    public User findById(int id) {
        boolean found = false;
        Iterator<User> iterator = users.iterator();
        User user = null;

        while (!found && iterator.hasNext()) {
            User currentUser = iterator.next();

            if (currentUser.getId() == id) {
                user = currentUser;
                found = true;
            }
        }

        return user;
    }

    public User getRandomUser() {
        Random random = new Random();

        int randomIndex = random.nextInt(this.users.size());

        return this.users.get(randomIndex);
    }

    protected void handleJson(JsonObject jsonUser) {
        String firstName = jsonUser.getString("firstName");
        String lastName = jsonUser.getString("lastName");
        String email = jsonUser.getString("email");
        String photo = jsonUser.getString("photo");
        boolean admin = jsonUser.getBoolean("admin");

        User user = new User(firstName, lastName, email, photo, admin);

        this.users.add(user);
    }
}