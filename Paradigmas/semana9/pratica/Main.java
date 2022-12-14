package semana9.pratica;

import java.util.ArrayList;
import java.util.Random;

public class Main {
    public static void main (String args[]) {
        ArrayList<Shop> list;
        Product product;
        Service service;
        Random random;
        String name;
        double price, size;
        int count, time;

        list = new ArrayList<Shop>();
        random = new Random();

        for (count = 0; count < 4; ++count) {
            name = "Nome" + count;
            price = 1000 * random.nextDouble();
            switch (random.nextInt(2)) {
                case 0:
                    size = 100 * random.nextDouble();
                    product = new Product(name, size, price);
                    list.add(product);
                    break;
                case 1:
                    time = random.nextInt(100);
                    service = new Service(name, time, price);
                    list.add(service);
                    break;
            }
        }

        for (Shop item : list) {
            if (item instanceof Product) {
                product = (Product) item;
                System.out.printf("----------------------------------------------\n");
                System.out.printf("Tipo: Produto\n");
                System.out.printf("Nome: %s\n", product.getName());
                System.out.printf("Tamanho: %s\n", product.getSize());
                System.out.printf("Preço %s\n", product.getPrice());
            } else {
                service = (Service) item;
                System.out.printf("----------------------------------------------\n");
                System.out.printf("Tipo: Serviço\n");
                System.out.printf("Nome: %s\n", service.getName());
                System.out.printf("Tamanho: %s\n", service.getTime());
                System.out.printf("Preço %s\n", service.getPrice());
            } 
        }
    }
}
