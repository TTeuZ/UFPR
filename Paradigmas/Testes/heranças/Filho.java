package Testes.heranças;

public class Filho extends Classe {
    private int teste2;

    public Filho(int teste, int teste2) {
        super(teste);
        this.teste2 = teste2;
    }

    public int getTeste2() {
        return teste2;
    }

    public void setTeste2(int teste2) {
        this.teste2 = teste2;
    }

    public void metodoTeste(int number) {
        this.teste = number;
        // isso que queria testar, ele herda par não tem visibilidaed para esse tipo de
        // operação
        this.getTeste();
        // mas o quet teste funciona, dai teria que fazer get e set.
    }
}
