import java.util.Scanner;
import java.lang.Float;

public class Exercicio7 {
    public static void main (String[] args) {
        int studentCount, gradeCount;
        float biggerGrades[], biggerClassGrade, currentGrade;
        Scanner input;
    
        input = new Scanner (System.in);
        biggerGrades = new float[30];
        biggerClassGrade = 0.0f;
        currentGrade = 0.0f;


        for (studentCount = 0; studentCount < 30; studentCount++) {
            System.out.printf ("Digite as notas para o estudante %d: ", studentCount + 1);
            for (gradeCount = 0; gradeCount < 4; gradeCount++) {
                currentGrade = input.nextFloat ();
                if (Float.compare (currentGrade, biggerGrades[studentCount]) > 0) 
                    biggerGrades[studentCount] = currentGrade;
                if (Float.compare (currentGrade, biggerClassGrade) > 0)
                    biggerClassGrade = currentGrade;
            }
        }

        for (studentCount = 0; studentCount < 30; studentCount++) 
            System.out.printf ("A maior nota do aluno %d é: %f\n", studentCount + 1, biggerGrades[studentCount]);
        System.out.printf ("A maior nota da sala é: %f\n", biggerClassGrade);  

        input.close(); 
    }
}