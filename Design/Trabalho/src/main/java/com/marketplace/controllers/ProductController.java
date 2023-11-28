package com.marketplace.controllers;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import com.marketplace.models.ProductList;
import com.marketplace.models.Product;
import com.marketplace.models.PaymentMethodList;
import com.marketplace.enums.PaymentMethodType;
import com.marketplace.models.PaymentMethod;
import com.marketplace.enums.StateType;
import com.marketplace.models.CategoriesList;
import com.marketplace.models.Category;
import com.marketplace.models.ImageList;
import com.marketplace.models.Image;
import com.marketplace.models.Location;
import com.marketplace.models.RatingList;
import com.marketplace.models.Session;
import com.marketplace.models.User;

public class ProductController {
    public ArrayList<Product> search() {
        ProductList list = ProductList.getInstance();
        return list.getProducts();
    }

    public ArrayList<Product> filter(String name, int categoryId, float lowerPriceBound, float upperPriceBound) {
        ProductList list = ProductList.getInstance();
        HashMap<String, Object> filters = new HashMap<String, Object>();

        if (name.length() != 0)
            filters.put("name", name);
        if (categoryId != -1)
            filters.put("categoryId", categoryId);
        if (lowerPriceBound != -1)
            filters.put("lowerPriceBound", lowerPriceBound);
        if (upperPriceBound != -1)
            filters.put("upperPriceBound", upperPriceBound);

        return list.filter(filters);
    }

    public Product getProduct(int id) {
        ProductList productList = ProductList.getInstance();
        return productList.findById(id);
    }

    public HashMap<String, Object> registerProduct(String name, String description, float price, int categoryId,
            StateType state, HashMap<String, Object> location, ArrayList<PaymentMethodType> payments, boolean donation,
            ArrayList<String> photos) {
        HashMap<String, Object> result = new HashMap<>();

        if (name.isBlank()) {
            String errorMessage = "Nome não pode estar em branco!";
            result.put("name", errorMessage);
        }
        if (description.isBlank()) {
            String errorMessage = "Descrição não pode estar em branco!";
            result.put("description", errorMessage);
        }
        if (!donation && Float.compare(price, 0) < 0) {
            String errorMessage = "Preço não pode ser negativo!";
            result.put("price", errorMessage);
        }

        CategoriesList categoriesList = CategoriesList.getInstance();
        Category category = categoriesList.findById(categoryId);

        if (category == null) {
            String errorMessage = "Categoria não pode estar em branco!";
            result.put("category", errorMessage);
        }

        HashMap<String, Object> locationValidationResult = validateLocation(location);
        Location locationObj = (Location) locationValidationResult.get("location");
        if (locationObj == null)
            result.putAll(locationValidationResult);

        if (!donation && payments.size() == 0) {
            String errorMessage = "Os métodos de pagamento precisam ser informados!";
            result.put("payments", errorMessage);
        }

        if (photos.size() == 0) {
            String errorMessage = "Ao menos uma foto precisa ser fornecida!";
            result.put("photos", errorMessage);
        }

        if (result.size() > 0)
            return result;

        Session session = Session.getInstance();
        User currentUser = session.getCurrentUser();

        ImageList imageList = new ImageList();
        for (String url : photos)
            imageList.add(new Image(url));

        PaymentMethodList paymentMethods = new PaymentMethodList();
        for (PaymentMethodType type : payments)
            paymentMethods.add(new PaymentMethod(type));

        Product product = new Product(name, description, price, imageList, new RatingList(), paymentMethods, category,
                currentUser, state, locationObj, 0, donation);
        result.put("product", product);
        return result;
    }

    public void confirm(Product product) {
        ProductList productList = ProductList.getInstance();
        productList.addProduct(product);
    }

    public void cancel() {
        return;
    }

    public HashMap<String, Object> rate(float rating, String comment, Product product) {
        HashMap<String, Object> result = new HashMap<String, Object>();

        if (comment.trim().length() > 320) {
            String errorMessage = "Tamanho máximo permitido é igual a 2000 caracteres";
            result.put("message", errorMessage);
        }
        if (comment.trim().length() == 0) {
            String errorMessage = "Mensagem não pode estar em branco!";
            result.put("message", errorMessage);
        }

        if (result.size() > 0)
            return result;

        Session session = Session.getInstance();
        User currentUser = session.getCurrentUser();

        product.addRating(currentUser, rating, comment);
        result.put("product", product);
        return result;
    }

    private HashMap<String, Object> validateLocation(HashMap<String, Object> location) {
        HashMap<String, Object> result = new HashMap<>();

        for (Map.Entry<String, Object> entry : location.entrySet()) {
            if (entry.getValue() instanceof String) {
                String temp = (String) entry.getValue();
                if (temp.isBlank())
                    result.put(entry.getKey(), "Valor precisa ser informado");
            } else {
                if (entry.getValue() == null)
                    result.put(entry.getKey(), "Valor precisa ser informado");
            }
        }
        if (result.size() > 0)
            return result;

        Location locationObj = new Location((String) location.get("street"), (String) location.get("neighborhood"),
                (int) location.get("number"), (String) location.get("city"), (String) location.get("state"));
        result.put("location", locationObj);
        return result;
    }
}