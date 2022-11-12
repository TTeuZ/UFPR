package semana4.Exercicio2;

import java.util.concurrent.ThreadLocalRandom;

public class Main {
    public static void main(String[] args) {
        NormalTicket normalTicket;
        VipTicket vipTicket;
        CabinTicket cabinTicket;

        normalTicket = new NormalTicket(ThreadLocalRandom.current().nextDouble() * 20);
        vipTicket = new VipTicket(ThreadLocalRandom.current().nextDouble() * 20,
                ThreadLocalRandom.current().nextDouble() * 20);
        cabinTicket = new CabinTicket(ThreadLocalRandom.current().nextDouble() * 20,
                ThreadLocalRandom.current().nextDouble() * 20, ThreadLocalRandom.current().nextDouble() * 20);

        System.out.println("----------------------------------------------------");
        System.out.println("Ingresso normal: ");
        normalTicket.printValue();
        System.out.println("----------------------------------------------------");
        System.out.println("Ingresso vip: ");
        vipTicket.printValue();
        System.out.println("----------------------------------------------------");
        System.out.println("Ingresso camarote: ");
        cabinTicket.printValue();
    }
}
