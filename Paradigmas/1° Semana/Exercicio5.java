import java.util.Scanner;
import java.lang.Float;

public class Exercicio5 {
    public static float lessFiveFx (float x) {
        return x;
    }

    public static float upperFiveLessTenFx (float x) {
        return (2 * x) + 1;
    }

    public static float upperTenFx (float x) {
        return x - 3;
    }

    public static void main (String[] args) {
        float x, res;
        Scanner input = new Scanner (System.in);

        System.out.print ("Informe o número: ");
        x = (float) input.nextFloat();

        if (Float.compare (x, 5) < 0)
            res = lessFiveFx (x);
        else if (Float.compare (x, 10) < 0)
            res = upperFiveLessTenFx (x);
        else
            res = upperTenFx (x);
        
        System.out.println ("O resultado é: " + res);
    }
}