package com.marketplace.models;

public class Message {
    private User sender;
    private User receiver;
    private String message;

    public Message(User sender, User receiver, String message) {
        this.sender = sender;
        this.receiver = receiver;
        this.message = message;
    }

    public String getMessage() {
        return this.message;
    }

    public User getSender() {
        return this.sender;
    }

    public User getReceiver() {
        return this.receiver;
    }

    @Override
    public String toString() {
        return this.toString(0);
    }

    public String toString(int level) {
        String tabbing = "\n";

        for (int i = 0; i < level; ++i)
            tabbing += "\t";

        String result = "De: " + this.sender.getName()
                + " Para: " + this.receiver.getName() +
                tabbing + this.message + "\n";

        return result;
    }
}