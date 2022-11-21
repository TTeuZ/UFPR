package semana5;

public class ChristimasCard extends WebCard {
    // Constructor
    public ChristimasCard(String destination) {
        super(destination);
    }

    // Methods
    public void returnMessage(String sender) {
        System.out.printf("Querido(a) %s,\n", this.getDestination());
        System.out.printf("Feliz Natal!\n");
        System.out.printf("Espero que hoje seja um dia muito especial!\n");
        System.out.printf("De todo meu coração,\n");
        System.out.printf("%s\n", sender);
    }
}
