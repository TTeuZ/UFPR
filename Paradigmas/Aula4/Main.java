import java.util.concurrent.ThreadLocalRandom;

public class Main {
    public static void main(String[] args) {
        MonthlyEmployer[] mEmployer;
        HourlyEmployer[] hEmployer;
        String mEmployerName, hEmployerName;
        int count;

        mEmployer = new MonthlyEmployer[100];
        hEmployer = new HourlyEmployer[100];

        for (count = 0; count < 100; count++) {
            mEmployerName = "FuncionárioM - " + count;
            mEmployer[count] = new MonthlyEmployer(mEmployerName, ThreadLocalRandom.current().nextInt(),
                    ThreadLocalRandom.current().nextBoolean(), ThreadLocalRandom.current().nextDouble());

            hEmployerName = "FuncionarioH - " + count;
            hEmployer[count] = new HourlyEmployer(hEmployerName,
                    ThreadLocalRandom.current().nextInt(),
                    ThreadLocalRandom.current().nextBoolean(),
                    ThreadLocalRandom.current().nextDouble(),
                    ThreadLocalRandom.current().nextDouble());

            mEmployerName = "";
            hEmployerName = "";
        }

        for (count = 0; count < 100; count++) {
            System.out.println("----------------------------");
            mEmployer[count].print();
            mEmployer[count].calcSalary();
            System.out.println("----------------------------");
            hEmployer[count].print();
            hEmployer[count].calcSalary();
        }
    }
}
