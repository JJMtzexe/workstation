#include <Adafruit_NeoPixel.h>

// NeoPixel configuration
#define PIN 3 // Input pin NeoPixel is attached to
#define NUMPIXELS 120 // Number of NeoPixels in the strip
int SENSOR = A0; // Analog sensor input pin

// NeoPixel object
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Maximum luminosity value
const byte MAXLUMINOSITY = 255;

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

// Function to generate a rainbow color
uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return pixels.Color((255 - WheelPos * 3) * MAXLUMINOSITY / 255, 0, (WheelPos * 3) * MAXLUMINOSITY / 255);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return pixels.Color(0, (WheelPos * 3) * MAXLUMINOSITY / 255, (255 - WheelPos * 3) * MAXLUMINOSITY / 255);
    } else {
        WheelPos -= 170;
        return pixels.Color((WheelPos * 3) * MAXLUMINOSITY / 255, (255 - WheelPos * 3) * MAXLUMINOSITY / 255, 0);
    }
}

// Function to set the color of a pixel based on the rainbow
void rainbow(int unsigned delay_val = 10, int unsigned step = 1)
{
    static int pos = 0;

    for (int i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, Wheel((i + pos) & 255));
    }

    pixels.show();

    pos = (pos + step) % 256; // Increment position (0 to 255)
    delay(delay_val); // Adjust the delay to control the speed of the rainbow
}

// Function to fade between two colors on NeoPixel strip
void fade(int r1, int g1, int b1, int r2, int g2, int b2, int step = 1)
{
    pixels.fill(0);

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
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
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
    if (read > calibrated_param + 13) {
        rainbow(0, 15);
    } else {
        // If below the threshold, turn off the NeoPixel strip
        pixels.fill(0);
        pixels.show();
    }

    // Print the sensor value to the Serial monitor
    Serial.println(read);
}
