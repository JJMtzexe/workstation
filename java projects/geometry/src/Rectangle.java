public class Rectangle extends Figure{

    float base;

    public Rectangle() {
        id = "rectangle";
        width = Float.parseFloat(requestValues("width", id));
        height = Float.parseFloat(requestValues("height", id));
        base = width;
        calculateValues(width, height);
    }

    void calculateValues(float width, float height) {
        area = (float) (width * height);
        perimeter = (float) (2 * width + 2 * height);
    }
}
