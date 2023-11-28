package com.marketplace.models;

import java.io.IOException;
import java.io.FileReader;
import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonObject;
import javax.json.JsonReader;

public abstract class Loadable {
    protected void loadData(String path) {
        try (JsonReader reader = Json.createReader(new FileReader(path))) {
            JsonArray jsonArray = reader.readArray();

            for (JsonObject jsonCategory : jsonArray.getValuesAs(JsonObject.class))
                this.handleJson(jsonCategory);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    protected abstract void handleJson(JsonObject jsonCategory);
}