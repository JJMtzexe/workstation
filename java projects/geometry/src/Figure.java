import java.util.Scanner;

public class Figure {
    float area, perimeter, width, height;
    String id;

    String requestValues(String value, String tag) {
        Scanner value_scanner = new Scanner(System.in);
        System.out.printf("Enter the %s of the %s:", value, tag);
        System.out.println("");
        String output = value_scanner.nextLine();
        return output;
    }

    void printValues() {
        System.out.println("");
        System.out.printf("The perimeter of the %s is: %.2fu \nThe area of the %s is: %.2fu2 \n", id, Math.round(perimeter * 100.0) / 100.0, id, Math.round(area * 100.0) / 100.0);
        System.out.println("");
    }

    float[] getSides(int side_num) {
        float[] sides = new float[side_num];
        for (int i = 0; i < side_num; i++) {
            sides[i] = Float.parseFloat(requestValues("side " + (i + 1), id));
        }
        return sides;
    }

    float sumSides(float[] sides) {
        float output = 0;
        for (int i = 0; i < sides.length; i++) {
            output += sides[i] ;
        }
        return output;
    }
}
