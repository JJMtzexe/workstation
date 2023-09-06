public class Triangle extends Figure {

    float[] sides;

    public Triangle() {
        id = "triangle";
        sides = getSides(3);
        calculateValues(sides);
    }

    void calculateValues(float[] sides) {
        float s = sumSides(sides)/2;
        area = (float)(Math.sqrt(s * (s - sides[0]) * (s - sides[1]) * (s - sides[2])));
        perimeter = sumSides(sides);
    }
}
