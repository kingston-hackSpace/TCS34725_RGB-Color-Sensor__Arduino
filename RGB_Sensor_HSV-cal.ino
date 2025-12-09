#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Sensor settings
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_154MS,
  TCS34725_GAIN_4X
);

// White reference calibration
uint16_t whiteR = 1, whiteG = 1, whiteB = 1, whiteC = 1;

void setup() {
  Serial.begin(9600);

  if (!tcs.begin()) {
    Serial.println("TCS34725 not detected.");
    while (1);
  }

  Serial.println("=== WHITE CALIBRATION ===");
  Serial.println("Place a matte white card 5–10 mm above the sensor.");
  Serial.println("Then press RESET.");
  delay(1500);

  // Read white reference
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  whiteR = r;
  whiteG = g;
  whiteB = b;
  whiteC = c;

  Serial.println("Calibration complete:");
  Serial.print("White R:");
  Serial.print(whiteR);
  Serial.print(" G:");
  Serial.print(whiteG);
  Serial.print(" B:");
  Serial.print(whiteB);
  Serial.print(" C:");
  Serial.println(whiteC);
  Serial.println("=========================");
}

//
// ---- Convert calibrated RGB to HSV ----
// HSV output:
// H = 0–360 degrees
// S = 0–1
// V = 0–1
//
void RGB_to_HSV(float r, float g, float b, float &h, float &s, float &v) {
  float maxVal = max(r, max(g, b));
  float minVal = min(r, min(g, b));
  float delta = maxVal - minVal;

  // Value
  v = maxVal;

  // Saturation
  if (maxVal == 0) s = 0;
  else s = delta / maxVal;

  // Hue
  if (delta == 0) {
    h = 0; // grey
  } else {
    if (maxVal == r)
      h = 60 * fmod(((g - b) / delta), 6);
    else if (maxVal == g)
      h = 60 * (((b - r) / delta) + 2);
    else
      h = 60 * (((r - g) / delta) + 4);

    if (h < 0) h += 360;
  }
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // ---- Calibrated RGB (0–1) ----
  float R_cal = min((float)r / whiteR, 1.0);
  float G_cal = min((float)g / whiteG, 1.0);
  float B_cal = min((float)b / whiteB, 1.0);

  // ---- Convert calibrated RGB to HSV ----
  float H, S, V;
  RGB_to_HSV(R_cal, G_cal, B_cal, H, S, V);

  // ---- Print ----
  Serial.print("HSV -> H:");
  Serial.print(H, 1);
  Serial.print("°  S:");
  Serial.print(S, 3);
  Serial.print("  V:");
  Serial.println(V, 3);

  Serial.println("----------------------");
  delay(400);
}

