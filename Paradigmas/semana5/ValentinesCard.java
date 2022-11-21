package semana5;

public class ValentinesCard extends WebCard {
    // Constructor
    public ValentinesCard(String destination) {
        super(destination);
    }

    // Methods
    public void returnMessage(String sender) {
        System.out.printf("Querido(a) %s,\n", this.getDestination());
        System.out.printf("Feliz Dia dos Namorados!\n");
        System.out.printf("Espero que esse tenha sido o único cartão do dia dos namorados que tenha\n");
        System.out.printf("ganhado nessa data!\n");
        System.out.printf("De todo meu coração,\n");
        System.out.printf("%s\n", sender);
    }
}
