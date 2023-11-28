package com.marketplace.views;

import java.util.ArrayList;
import java.util.Iterator;

import com.marketplace.controllers.ChatController;
import com.marketplace.models.Chat;
import com.marketplace.models.User;
import com.marketplace.models.UserList;
import com.marketplace.utils.InputReader;

public class Chats extends Interface {
    private ChatController chatController;

    public Chats() {
        this.numberOfOptions = 4;

        this.chatController = new ChatController();
    }

    public void showOptions() {
        System.out.println("\nConversas");
        System.out.println("1 - Listar Conversas");
        System.out.println("2 - Criar Conversa");
        System.out.println("3 - Abrir Conversa");
        System.out.println("4 - Voltar\n");
    }

    public void handleOption(int option) {
        switch (option) {
            case 1:
                this.listChats();
                break;
            case 2:
                this.createChat();
                break;
            case 3:
                this.showChat();
                break;
            default:
                break;
        }
    }

    private void listChats() {
        ArrayList<Chat> chatList = this.chatController.getChats();

        System.out.println("\nCONVERSAS:\n");
        Iterator<Chat> iterator = chatList.iterator();
        while (iterator.hasNext())
            System.out.println(iterator.next().toString(1));

        if (chatList.size() == 0) {
            System.out.println("Você não possui nenhuma conversa.");
        }

        this.showOptions();
    }

    private void createChat() {
        InputReader reader = new InputReader(this.keyboard);
        UserList userList = UserList.getInstance();
        User receiver = null;
        Chat chat = null;

        while (receiver == null || chat == null) {
            receiver = userList.findById(reader.readInt("\nID do usuário"));

            if (receiver == null)
                System.out.println("USUÁRIO INVÁLIDO. Escolha novamente.");
            else {
                chat = this.chatController.createChat(receiver.getId());
                if (chat == null)
                    System.out.println("Não é possível criar um chat consigo mesmo");
            }
        }

        System.out.println("Chat criado com sucesso!");
        this.showOptions();
    }

    private void showChat() {
        InputReader reader = new InputReader(this.keyboard);
        Chat chatObj = null;

        while (chatObj == null) {
            chatObj = this.chatController.getChat(reader.readInt("\nID do chat"));

            if (chatObj == null)
                System.out.println("CHAT INVÁLIDO. Escolha novamente.");
        }

        ViewChat viewChatScreen = new ViewChat(chatObj);

        viewChatScreen.showOptions();
        viewChatScreen.listenCommand();

        this.showOptions();
    }
}
