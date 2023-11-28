package com.marketplace.models;

public class Image {
    private String url;

    public Image(String url) {
        this.url = url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getUrl() {
        return this.url;
    }

    @Override
    public String toString() {
        return this.url;
    }
}