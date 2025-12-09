#include <Wire.h>
#include "Adafruit_TCS34725.h"
#define LED_PIN 6

// Sensor configuration
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_154MS,
  TCS34725_GAIN_4X
);

// White reference calibration values
uint16_t whiteR = 1, whiteG = 1, whiteB = 1, whiteC = 1;

// --- RGB to HSV conversion ---
void RGB_to_HSV(float r, float g, float b, float &h, float &s, float &v) {
  float maxVal = max(r, max(g, b));
  float minVal = min(r, min(g, b));
  float delta = maxVal - minVal;

  v = maxVal;
  if (maxVal == 0) s = 0;
  else s = delta / maxVal;

  if (delta == 0) h = 0;
  else {
    if (maxVal == r) h = 60 * fmod(((g - b) / delta), 6);
    else if (maxVal == g) h = 60 * (((b - r) / delta) + 2);
    else h = 60 * (((r - g) / delta) + 4);
    if (h < 0) h += 360;
  }
}

// --- Classify colour based on HSV ---
String detectColour(float H, float S, float V) {
  if (V < 0.05) return "Black";
  if (S < 0.1 && V > 0.9) return "White";
  if (S < 0.1) return "Grey";

  if ((H >= 0 && H < 15) || (H >= 345 && H <= 360)) return "Red";
  if (H >= 16 && H < 45) return "Orange";
  if (H >= 46 && H < 75) return "Yellow";
  if (H >= 76 && H < 165) return "Green";
  if (H >= 166 && H < 195) return "Cyan";
  if (H >= 196 && H < 255) return "Blue";
  if (H >= 256 && H < 320) return "Purple";
  if (H >= 321 && H < 344) return "Pink";
  return "Unknown";
}



void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 30);  // 0-255 PWM

  if (!tcs.begin()) {
    Serial.println("TCS34725 not detected. Check wiring.");
    while (1);
  }

  Serial.println("=== WHITE CALIBRATION ===");
  Serial.println("Place a matte white card 5–10 mm above the sensor.");
  Serial.println("Then press RESET.");
  delay(1500);

  // Capture white reference
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  whiteR = r; whiteG = g; whiteB = b; whiteC = c;

  Serial.println("Calibration complete!");
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // --- Calibrated RGB (0–1)
  float R_cal = min((float)r / whiteR, 1.0);
  float G_cal = min((float)g / whiteG, 1.0);
  float B_cal = min((float)b / whiteB, 1.0);

  // --- Convert to HSV
  float H, S, V;
  RGB_to_HSV(R_cal, G_cal, B_cal, H, S, V);

  // --- Detect colour name
  String colourName = detectColour(H, S, V);

  // --- Print results
  Serial.print("Detected colour: ");
  Serial.println(colourName);

  delay(500);
}
