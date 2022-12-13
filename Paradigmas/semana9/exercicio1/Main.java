package semana9.exercicio1;

import java.util.TreeSet;

public class Main {
    public static void main(String[] args) {
        TreeSet<Monitor> monitors;
        Monitor temp;

        monitors = new TreeSet<Monitor>();

        temp = new Monitor("Batata", 20203030, "CI1062");
        monitors.add(temp);

        // temp.setName("Amandinha");
        // temp.setRegistration(20203031);
        // temp.setClassCode("CI1055");
        temp = new Monitor("Amandinha", 20203031, "CI1055");
        monitors.add(temp);

        // temp.setName("Robervaldo");
        // temp.setRegistration(20203032);
        temp = new Monitor("Robervaldo", 20203032, "CI1055");
        monitors.add(temp);

        for (Monitor monitor : monitors) {
            System.out.printf("Monitor: %s\n", monitor.getName());
        }
    }
}
