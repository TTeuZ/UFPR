package com.marketplace.models;

import java.util.ArrayList;

import javax.json.JsonArray;
import javax.json.JsonObject;

public class RatingList extends ArrayList<Rating> {
    public static RatingList jsonToList(JsonArray jsonArray) {
        RatingList ratingList = new RatingList();
        UserList userList = UserList.getInstance();

        for (JsonObject jsonRating : jsonArray.getValuesAs(JsonObject.class)) {
            int userId = jsonRating.getInt("userId");
            float ratingValue = jsonRating.getJsonNumber("rating").numberValue().floatValue();
            String comment = jsonRating.getString("comment");

            User user = userList.findById(userId);
            Rating rating = new Rating(user, ratingValue, comment);
            ratingList.add(rating);
        }

        return ratingList;
    }
}