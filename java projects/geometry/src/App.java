import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class App {
    public static void main(String[] args) throws Exception {

        boolean end_program = false;
        Scanner sc = new Scanner(System.in);

        System.out.println("<-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+->");
        System.out.println("Welcome to the geometry calculator");

        outerloop:
        while(end_program == false) {
            System.out.println("");
            System.out.println("Choose the figure that you want to calculate (type the corresponding number):");
            System.out.println("(1): Square");
            System.out.println("(2): Rectangle");
            System.out.println("(3): Circle");
            System.out.println("(4): Triangle");
            System.out.println("");
            System.out.println("(0): Exit Program");
            
            int choice = sc.nextInt();
            switch (choice) {
                case 0: {
                    break outerloop;
                }

                case 1: {
                    Square square = new Square();
                    square.printValues();
                    break;
                }
                
                case 2: {
                    Rectangle rectangle = new Rectangle();
                    rectangle.printValues();
                    break;
                }

                case 3: {
                    Circle circle = new Circle();
                    circle.printValues();
                    break;
                }

                case 4: {
                    Triangle triangle = new Triangle();
                    triangle.printValues();
                    break;
                }

                default: {
                    System.out.println("The value you chose is invalid, please try again.");
                    continue;
                }
            }

            System.out.println("");
            System.out.println("Calculate another figure? (y/n): ");
            System.out.println("(1): yes");
            System.out.println("(0): no");
            int end = sc.nextInt();

            if (end == 0) {
                end_program = true;
            }
        }
        System.out.println("");
        System.out.println("End of the program, thank you for using it.");
    }
}
