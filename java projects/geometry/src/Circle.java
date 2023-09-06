public class Circle extends Figure {

    float radius, diameter, circumference;

    public Circle() {
        id = "circle";
        radius = Float.parseFloat(requestValues("radius", id));;
        diameter = radius * 2;
        calculateValues(radius);
    }

    void calculateValues(float radius) {
        area = (float) (Math.PI * Math.pow(radius, 2));
        perimeter = (float) (Math.PI * diameter);
        circumference = perimeter;
    }
}