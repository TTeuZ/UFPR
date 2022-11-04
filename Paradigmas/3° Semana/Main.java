import java.util.Scanner;

import javax.swing.border.EmptyBorder;

// meio bugado essa ideia do exercicio da folha de pagamento ter o funcionario como item
// parece fazer muito mais sentido e até mais facil de codar se o funcionário tivesse um array de folhas de pagamentos
// nem encontrei uma solução legal para isso, vou so meter 3 arrays de folhas de pagamento e é isso.

public class Main {
    public static void main(String[] args) {
        int day, month, year, paymentDay, paymentMonth, line, col, payrollsQtd;
        String name, registry, role;
        double value;
        UfprPayroll[] firstEmployeePayroll, secondEmployeePayroll, thirdEmployeePayroll;
        UfprEmployee employee;
        Date birthDate;
        Scanner input;
        input = new Scanner(System.in);

        for (line = 0; line < 3; line++) {
            System.out.printf("Informações do %d° Funcionário:\n", line + 1);

            System.out.printf("Nome: ");
            name = input.next();

            System.out.printf("Registro: ");
            registry = input.next();

            System.out.printf("Cargo: ");
            role = input.next();

            System.out.printf("Data de nascimento 'dd/mm/yyyy' (apenas os números): ");
            day = input.nextInt();
            month = input.nextInt();
            year = input.nextInt();

            System.out.printf("Quantidade de folhas de pagamento: ");
            payrollsQtd = input.nextInt();

            birthDate = new Date(day, month, year);
            employee = new UfprEmployee(name, registry, role, birthDate);

            System.out.printf("----------------------------------------------------------------\n");
            for (col = 0; col < payrollsQtd; col++) {
                System.out.printf("Informações da %d° Folha de pagamento:\n", col + 1);

                System.out.printf("Dia e mês de pagamento 'dd/mm' (apenas números): ");
                paymentDay = input.nextInt();
                paymentMonth = input.nextInt();

                System.out.printf("Valor: ");
                value = input.nextFloat();
            }
        }

        input.close();
    }
}
