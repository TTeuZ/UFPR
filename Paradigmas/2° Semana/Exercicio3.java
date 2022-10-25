import java.util.Scanner;
import java.util.Arrays;

public class Exercicio3 {
    public static void main (String[] args) {
        Scanner input;
        String word;
        char replacement, vowels[] = {'a', 'e', 'i', 'o', 'u'};
        int count, wordVowels;

        input = new Scanner (System.in);
        wordVowels = 0;

        System.out.println ("Digite a palavra");
        word = input.next ();

        for (count = 0; count < word.length (); count++)
            if (Arrays.binarySearch (vowels,  word.charAt (count)) != -5) 
                wordVowels++;
        
        System.out.println ("Digite a consoante");
        replacement = input.next().charAt(0);

        for (count = 0; count < 4; count++)
            word = word.replace (vowels[count], replacement);
        
        System.out.printf ("%s\n", word);

        input.close();
    }
}