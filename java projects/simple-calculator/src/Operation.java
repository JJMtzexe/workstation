import java.util.Scanner;

public class Operation {
float num1, num2;

    public Operation() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Escribe tu primer número: ");
        this.num1 = scanner.nextInt();
        System.out.println("Escribe tu segundo número: ");
        this.num2 = scanner.nextInt();
        calcAll();
    }

    void add(){
        float res = num1 + num2;   
        System.out.println("El resultado de la suma: " + num1 + " + " + num2 + " = " + res);
    }

    void substract(){
        float res = num1 - num2;
        System.out.println("El resultado de la resta: " + num1 + " - " + num2 + " = " + res);
    }

    void multiply(){
        float res = num1 * num2;
        System.out.println("El resultado de la multiplicación: " + num1 + " * " + num2 + " = " + res);
    }

    void divide(){
        float res = num1 / num2;
        System.out.println("El resultado de la división: " + num1 + " / " + num2 + " = " + res);
    }

    void calcAll(){
        add();
        substract();
        multiply();
        divide();
    }
}