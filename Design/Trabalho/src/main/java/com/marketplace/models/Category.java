package com.marketplace.models;

public class Category {
    private static int nextId = 1;

    private int id;
    private String name;

    public Category(String name) {
        setId(Category.nextId++);
        setName(name);
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return this.id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    @Override
    public String toString() {
        return this.toString(0);
    }

    public String toString(int level) {
        String tabbing = "\n";

        for (int i = 0; i < level; ++i)
            tabbing += "\t";

        String result = tabbing + "id: " + this.id +
                tabbing + "name: " + this.name;

        return result;
    }

}