package com.marketplace.models;

public class Rating {
    private User user;
    private float rating;
    private String comment;

    public Rating(User user, float rating, String comment) {
        this.user = user;
        this.rating = rating;
        this.comment = comment;
    }

    @Override
    public String toString() {
        return this.toString(0);
    }

    public String toString(int level) {
        String tabbing = "\n";

        for (int i = 0; i < level; ++i)
            tabbing += "\t";

        String result = tabbing + "Usuário: " + this.user.getName() +
                tabbing + "Nota: " + this.rating +
                tabbing + "Comentário: " + this.comment;

        return result;
    }
}
