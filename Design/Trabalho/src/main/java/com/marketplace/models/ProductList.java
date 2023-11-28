package com.marketplace.models;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

import javax.json.JsonArray;
import javax.json.JsonObject;

import com.marketplace.enums.StateType;
import com.marketplace.interfaces.Searchable;

public class ProductList extends Loadable implements Searchable<Product> {
    private static ProductList instance;
    private ArrayList<Product> products;

    private ProductList() {
        this.products = new ArrayList<Product>();
        this.loadData("src/main/java/com/marketplace/data/products.json");
    };

    public static synchronized ProductList getInstance() {
        if (instance == null)
            instance = new ProductList();

        return instance;
    }

    public ArrayList<Product> getProducts() {
        return this.products;
    }

    public Product findById(int id) {
        boolean found = false;
        Iterator<Product> iterator = this.products.iterator();
        Product product = null;

        while (!found && iterator.hasNext()) {
            Product currentProduct = iterator.next();

            if (currentProduct.getId() == id) {
                product = currentProduct;
                found = true;
            }
        }

        return product;
    }

    public ArrayList<Product> filter(HashMap<String, Object> filter) {
        ArrayList<Product> filteredList = new ArrayList<Product>();

        String name = (String) filter.get("name");
        Integer categoryId = (Integer) filter.get("categoryId");
        Float lowerPriceBound = (Float) filter.get("lowerPriceBound");
        Float upperPriceBound = (Float) filter.get("upperPriceBound");

        Iterator<Product> iterator = this.products.iterator();

        while (iterator.hasNext()) {
            Product currentProduct = iterator.next();

            if (name != null && !currentProduct.getName().toLowerCase().contains(name.toLowerCase()))
                continue;
            if (categoryId != null && categoryId != currentProduct.getCategory().getId())
                continue;
            if (lowerPriceBound != null && (currentProduct.getPrice() < lowerPriceBound))
                continue;
            if (upperPriceBound != null && (currentProduct.getPrice() > upperPriceBound))
                continue;

            filteredList.add(currentProduct);
        }

        return filteredList;
    }

    public void addProduct(Product product) {
        this.products.add(product);
    }

    protected void handleJson(JsonObject jsonProduct) {
        String name = jsonProduct.getString("name");
        String description = jsonProduct.getString("description");
        float price = jsonProduct.getJsonNumber("price").numberValue().floatValue();
        JsonArray jsonImage = jsonProduct.getJsonArray("images");
        JsonArray jsonRating = jsonProduct.getJsonArray("ratings");
        JsonArray JsonPaymentMethods = jsonProduct.getJsonArray("paymentMethods");
        int categoryId = jsonProduct.getInt("categoryId");
        int userId = jsonProduct.getInt("userId");
        String stateType = jsonProduct.getString("state");
        JsonObject jsonLocation = jsonProduct.getJsonObject("location");
        float generalRating = jsonProduct.getJsonNumber("generalRating").numberValue().floatValue();
        boolean donation = jsonProduct.getBoolean("donation");

        StateType state = StateType.valueOf(stateType);

        ImageList images = ImageList.jsonToList(jsonImage);
        RatingList ratings = RatingList.jsonToList(jsonRating);
        PaymentMethodList paymentMethods = PaymentMethodList.jsonToList(JsonPaymentMethods);

        CategoriesList categories = CategoriesList.getInstance();
        Category category = categories.findById(categoryId);

        UserList users = UserList.getInstance();
        User user = users.findById(userId);

        Location location = Location.jsonToObject(jsonLocation);

        Product product = new Product(name, description, price, images, ratings, paymentMethods, category, user, state,
                location, generalRating, donation);
        products.add(product);
    }
}