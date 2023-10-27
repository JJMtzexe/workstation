#include <Adafruit_NeoPixel.h>

// NeoPixel configuration
#define PIN 3 // Input pin NeoPixel is attached to
#define NUMPIXELS 120 // Number of NeoPixels in the strip
int SENSOR = A0; // Analog sensor input pin

// NeoPixel object
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Maximum luminosity value
const byte MAXLUMINOSITY = 50;

// Function to convert RGB values to a 32-bit hexadecimal color
uint32_t RGBtoHex(uint8_t r, uint8_t g, uint8_t b) { return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b; }

// Calibration parameter for the analog sensor
int calibrated_param;

// Function to calibrate the analog sensor
void calibrateSensor()
{
    Serial.println("Calibrating sensor...");

    // Read the SENSOR value for five seconds to calculate the average
    int numReadings = 0;
    long totalReadings = 0;
    unsigned long startTime = millis();

    while (millis() - startTime < 5000) {
        totalReadings += analogRead(SENSOR);
        numReadings++;
        delay(100);
    }

    // Calculate the average and assign it to calibrated_param
    calibrated_param = totalReadings / numReadings;

    Serial.println("Calibration complete. Calibrated Parameter: ");
    Serial.println(calibrated_param);

    // Visual indication of calibration with NeoPixel
    pixels.fill(pixels.Color(MAXLUMINOSITY, MAXLUMINOSITY / 2, 0));
    pixels.show();
    delay(500);

    pixels.fill(0);
    pixels.show();
    delay(500);

    pixels.fill(pixels.Color(MAXLUMINOSITY, MAXLUMINOSITY / 2, 0));
    pixels.show();
    delay(500);

    pixels.fill(0);
    pixels.show();
    delay(500);
}

// Function to convert rainbow color based on a static position
uint32_t rainbowColor()
{
    static int pos = 0; // Static variable to keep track of position
    pos = (pos + 1) % 256; // Increment position (0 to 255)

    // Calculate RGB values based on the rainbow position
    int r = map(pos, 0, 255, MAXLUMINOSITY, 0);
    int g = map(pos, 0, 255, 0, MAXLUMINOSITY);
    int b = map(pos, 0, 255, MAXLUMINOSITY, 0);

    // Pack the RGB values into a 32-bit color value
    uint32_t color = ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;

    return color;
}

// Function to fade between two colors on NeoPixel strip
void fade(int r1, int g1, int b1, int r2, int g2, int b2, int step = 1)
{
    pixels.fill(0x000000);

    for (int i = 0; i <= MAXLUMINOSITY; i++) {
        int r = (r1 * (MAXLUMINOSITY - i) + r2 * i) / MAXLUMINOSITY;
        int g = (g1 * (MAXLUMINOSITY - i) + g2 * i) / MAXLUMINOSITY;
        int b = (b1 * (MAXLUMINOSITY - i) + b2 * i) / MAXLUMINOSITY;

        for (int i = 0; i < NUMPIXELS; ++i) {
            pixels.setPixelColor(i, r, g, b);
        }

        pixels.show();
    }
}

// Function to fill NeoPixel strip with a specified color or random colors
void fillArray(int r, int g, int b, int delay_val = 10, bool random_node = false)
{
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.fill(0x000000);

        if (random_node == true) {
            pixels.setPixelColor(i, random(MAXLUMINOSITY), random(MAXLUMINOSITY), random(MAXLUMINOSITY));
            pixels.show();
        } else {
            pixels.setPixelColor(i, r, g, b);
            pixels.show();
        }
        delay(delay_val);
    }
}

// Setup function
void setup()
{
    pinMode(SENSOR, INPUT);
    pinMode(12, OUTPUT);
    digitalWrite(12, HIGH);
    pixels.begin();
    pixels.fill(0);
    pixels.show();

    Serial.begin(115200);

    calibrateSensor();
}

// Loop function
void loop()
{
    // Read the sensor value
    int read = analogRead(SENSOR);

    // If the sensor value is above the calibrated threshold, execute
    if (read > calibrated_param + 7) {
        pixels.fill(RGBtoHex(MAXLUMINOSITY, 0, 0));
        pixels.show();
    } else {
        // If below the threshold, turn off the NeoPixel strip
        pixels.fill(0);
        pixels.show();
    }

    // Print the sensor value to the Serial monitor
    Serial.println(read);
}
