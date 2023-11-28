package com.marketplace.controllers;

import java.util.ArrayList;
import java.util.HashMap;

import com.marketplace.models.Chat;
import com.marketplace.models.Session;
import com.marketplace.models.User;
import com.marketplace.models.UserList;

public class ChatController {
    public Chat createChat(int userId) {
        Session session = Session.getInstance();
        UserList userList = UserList.getInstance();

        User user = userList.findById(userId);
        User currentUser = session.getCurrentUser();

        Chat chat = null;
        if (currentUser.getId() != userId) {
            chat = new Chat(user, currentUser);
            user.addChat(chat);
            currentUser.addChat(chat);
        }

        return chat;
    }

    public HashMap<String, Object> sendMessage(String message, Chat chat) {
        HashMap<String, Object> result = new HashMap<String, Object>();

        if (message.trim().length() > 2000) {
            String errorMessage = "Tamanho máximo permitido é igual a 2000 caracteres";
            result.put("message", errorMessage);
        }
        if (message.trim().length() == 0) {
            String errorMessage = "Mensagem não pode estar em branco!";
            result.put("message", errorMessage);
        }

        if (result.size() > 0)
            return result;

        chat.sendMessage(message);
        result.put("chat", chat);
        return result;
    }

    public Chat getChat(int chatId) {
        Session session = Session.getInstance();
        User currentUser = session.getCurrentUser();

        return currentUser.getChats().findById(chatId);
    }

    public ArrayList<Chat> getChats() {
        Session session = Session.getInstance();
        User currentUser = session.getCurrentUser();

        return currentUser.getChats();
    }
}
