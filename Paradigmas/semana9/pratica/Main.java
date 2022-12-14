package semana9.pratica;

import java.util.ArrayList;
import java.util.Random;

public class Main {
    public static void main (String args[]) {
        ArrayList<Shop> list;
        Television television;
        Cellphone cellphone;
        Service service;
        Random random;
        String name;
        double price, size;
        int count, time;

        list = new ArrayList<Shop>();
        random = new Random();

        for (count = 0; count < 8; ++count) {
            name = "Nome" + count;
            price = 1000 * random.nextDouble();
            switch (random.nextInt(3)) {
                case 0:
                    size = 100 * random.nextDouble();
                    television = new Television(name, size, price);
                    list.add(television);
                    break;
                case 1:
                    size = 100 * random.nextDouble();
                    cellphone = new Cellphone(name, size, price);
                    list.add(cellphone);
                    break;
                case 2:
                    time = random.nextInt(100);
                    service = new Service(name, time, price);
                    list.add(service);
                    break;
            }
        }

        for (Shop item : list) {
            if (item instanceof Service) {
                service = (Service) item;
                System.out.printf("----------------------------------------------\n");
                System.out.printf("Tipo: Serviço\n");
                System.out.printf("Nome: %s\n", service.getName());
                System.out.printf("Tamanho: %s\n", service.getTime());
                System.out.printf("Preço %s\n", service.getPrice());
            } else if (item instanceof Television) {
                television = (Television) item;
                System.out.printf("----------------------------------------------\n");
                System.out.printf("Tipo: Televisão\n");
                System.out.printf("Nome: %s\n", television.getName());
                System.out.printf("Tamanho: %s\n", television.getSize());
                System.out.printf("Preço %s\n", television.getPrice());
            } else {
                cellphone = (Cellphone) item;
                System.out.printf("----------------------------------------------\n");
                System.out.printf("Tipo: Telefone\n");
                System.out.printf("Nome: %s\n", cellphone.getName());
                System.out.printf("Tamanho: %s\n", cellphone.getSize());
                System.out.printf("Preço %s\n", cellphone.getPrice());
            }
        }
    }
}
