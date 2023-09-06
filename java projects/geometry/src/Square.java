public class Square extends Figure {

    float side;

    public Square() {
        id = "square";
        side = Float.parseFloat(requestValues("side", id));
        height = side;
        width = side;
        calculateValues(side);
    }
    
    void calculateValues(float side) {
        perimeter = side * 4;
        area = (float) (Math.pow(side, 2));
    }
}
