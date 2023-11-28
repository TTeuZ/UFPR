package com.marketplace.models;

import java.util.ArrayList;

import javax.json.JsonArray;
import javax.json.JsonObject;

public class ImageList extends ArrayList<Image> {
    public static ImageList jsonToList(JsonArray jsonArray) {
        ImageList imageList = new ImageList();

        for (JsonObject jsonImage : jsonArray.getValuesAs(JsonObject.class)) {
            String url = jsonImage.getString("url");

            Image image = new Image(url);
            imageList.add(image);
        }

        return imageList;
    }
}
