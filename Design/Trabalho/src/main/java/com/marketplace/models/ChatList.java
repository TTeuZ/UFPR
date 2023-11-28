package com.marketplace.models;

import java.util.ArrayList;
import java.util.Iterator;

import com.marketplace.interfaces.Searchable;

public class ChatList extends ArrayList<Chat> implements Searchable<Chat> {
    public Chat findById(int id) {
        boolean found = false;
        Iterator<Chat> iterator = this.iterator();
        Chat chat = null;

        while (!found && iterator.hasNext()) {
            Chat currentChat = iterator.next();

            if (currentChat.getId() == id) {
                chat = currentChat;
                found = true;
            }
        }

        return chat;
    }
}