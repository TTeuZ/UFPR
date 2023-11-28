package com.marketplace.models;

import java.util.Iterator;

import com.marketplace.enums.StateType;

public class Product {
    private static int nextId = 1;

    private int id;
    private String name;
    private String description;
    private float price;
    private StateType state;
    private float generalRating;
    private ImageList images;
    private RatingList ratings;
    private PaymentMethodList paymentMethods;
    private Category category;
    private Location location;
    private User user;
    private boolean donation;

    public Product(String name, String description, float price, ImageList images, RatingList ratings,
            PaymentMethodList paymentMethods, Category category, User user, StateType state, Location location,
            float generalRating, boolean donation) {
        this.id = Product.nextId++;
        this.name = name;
        this.description = description;
        this.price = price;
        this.images = images;
        this.ratings = ratings;
        this.paymentMethods = paymentMethods;
        this.category = category;
        this.user = user;
        this.state = state;
        this.location = location;
        this.generalRating = generalRating;
        this.donation = donation;
    }

    public int getId() {
        return this.id;
    }

    public String getName() {
        return this.name;
    }

    public float getPrice() {
        return this.price;
    }

    public Category getCategory() {
        return this.category;
    }

    public User getSeller() {
        return this.user;
    }

    public void addRating(User user, float rating, String comment) {
        Rating ratingObj = new Rating(user, rating, comment);
        float totalRating = this.generalRating * this.ratings.size();
        float newRating;

        this.ratings.add(ratingObj);

        newRating = (totalRating + rating) / this.ratings.size();

        this.generalRating = newRating;
    }

    public void showDetails() {
        String result = "id: " + this.id +
                "\nNome: " + this.name +
                "\nDescrição: " + this.description +
                "\nPreço: " + this.price +
                "\nCategoria: " + this.category.toString(1) +
                "\nUsuario: " + this.user.toString(1) +
                "\nEstado: " + Product.parseState(this.state) +
                "\nLocalização: " + this.location.toString(1) +
                "\nAvaliaçao geral: " + this.generalRating +
                "\nDoação: " + this.donation;

        System.out.println(result);

        System.out.println("Meios de Pagamento:");
        Iterator<PaymentMethod> paymentMethodsIterator = this.paymentMethods.iterator();
        while (paymentMethodsIterator.hasNext()) {
            System.out.println(paymentMethodsIterator.next().toString(1));
        }

        System.out.println("Avaliações:");
        Iterator<Rating> ratingsIterator = this.ratings.iterator();
        while (ratingsIterator.hasNext()) {
            System.out.println(ratingsIterator.next().toString(1));
        }
    }

    public static String parseState(StateType state) {
        switch (state) {
            case NEW:
                return "Novo";
            case USED:
                return "Usado";
            default:
                return "";
        }
    }

    @Override
    public String toString() {
        String result = "id: " + this.id +
                "\nNome: " + this.name +
                "\nPreço: " + this.price +
                "\nCategoria: " + this.category.toString(1) +
                "\nAvaliação Geral: " + this.generalRating +
                "\nFoto: " + this.images.get(0);

        return result;
    }
}
