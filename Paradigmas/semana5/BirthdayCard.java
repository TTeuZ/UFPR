package semana5;

public class BirthdayCard extends WebCard {
    // Constructor
    public BirthdayCard(String destination) {
        super(destination);
    }

    // Methods
    public void returnMessage(String sender) {
        System.out.printf("Querido(a) %s,\n", this.getDestination());
        System.out.printf("Feliz Aniversário!\n");
        System.out.printf("Muitos anos de vida e aproveite seu dia!\n");
        System.out.printf("De todo meu coração,\n");
        System.out.printf("%s\n", sender);
    }
}
