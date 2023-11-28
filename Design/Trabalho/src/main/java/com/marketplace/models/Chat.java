package com.marketplace.models;

import java.util.ArrayList;
import java.util.Iterator;

public class Chat {
    private static int nextId = 1;

    private int id;
    private ArrayList<User> users = new ArrayList<>();
    private MessageList messages;

    public Chat(User userOne, User userTwo) {
        this.id = nextId++;
        this.users.add(userOne);
        this.users.add(userTwo);
        this.messages = new MessageList();
    }

    public int getId() {
        return this.id;
    }

    public ArrayList<User> getUsers() {
        return this.users;
    }

    public MessageList getMessages() {
        return this.messages;
    }

    public boolean userParticipateChat(User user) {
        boolean participate = false;

        Iterator<User> iterator = this.users.iterator();

        while (!participate && iterator.hasNext())
            if (user.getId() == iterator.next().getId())
                participate = true;

        return participate;
    }

    public void sendMessage(String message) {
        Session session = Session.getInstance();

        User sender = session.getCurrentUser();
        User receiver = fetchReceiver();

        Message messageObj = new Message(sender, receiver, message);

        this.messages.add(messageObj);
    }

    private User fetchReceiver() {
        Session session = Session.getInstance();
        User sender = session.getCurrentUser();

        boolean found = false;
        User receiver = null;

        Iterator<User> iterator = this.users.iterator();

        while (!found && iterator.hasNext()) {
            User user = iterator.next();

            if (user.getId() != sender.getId()) {
                receiver = user;
                found = true;
            }
        }

        return receiver;
    }

    @Override
    public String toString() {
        return this.toString(0);
    }

    public String toString(int level) {
        String tabbing = "\n";

        for (int i = 0; i < level; ++i)
            tabbing += "\t";

        String result = tabbing + "Conversa com: " + this.fetchReceiver().getName()
                + " (Id: " + this.id + ")";

        return result;
    }
}