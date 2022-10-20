public class Exercicio4 {
    public static void main (String[] args) {
        int count, sum;

        sum = 0;
        for (count = 1; count <= 10; count++) 
            sum += count * 3;
        
        System.out.println ("A soma dos 10 primeiro multiplos de 3 é: " + sum);
    }
}