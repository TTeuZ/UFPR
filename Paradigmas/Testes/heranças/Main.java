package Testes.heranças;

public class Main {
    public static void main(String[] args) {
        Filho f;
        f = new Filho(12, 10);

        System.out.printf("Teste: %d - Teste2: %d\n", f.getTeste(), f.getTeste2());
    }
}
