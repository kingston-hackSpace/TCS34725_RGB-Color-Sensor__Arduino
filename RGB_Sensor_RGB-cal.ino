#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Sensor configuration
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_154MS,
  TCS34725_GAIN_4X
);

// White reference calibration values
uint16_t whiteR = 1, whiteG = 1, whiteB = 1, whiteC = 1;

void setup() {
  Serial.begin(9600);

  if (!tcs.begin()) {
    Serial.println("TCS34725 not detected. Check wiring.");
    while (1);
  }

  Serial.println("=== Starting Calibration ===");
  Serial.println("Place a matte white card 5–10 mm above the sensor.");
  Serial.println("Then press the Arduino RESET button.");
  delay(1500);

  // Capture white reference
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  whiteR = r;
  whiteG = g;
  whiteB = b;
  whiteC = c;

  Serial.println("Calibration complete!");
  Serial.print("White reference -> R:");
  Serial.print(whiteR);
  Serial.print(" G:");
  Serial.print(whiteG);
  Serial.print(" B:");
  Serial.print(whiteB);
  Serial.print(" C:");
  Serial.println(whiteC);
  Serial.println("===============================");
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // ---- Calibrated channels (0–1) ----
  float R_cal = min((float)r / whiteR, 1.0);
  float G_cal = min((float)g / whiteG, 1.0);
  float B_cal = min((float)b / whiteB, 1.0);
  float C_cal = min((float)c / whiteC, 1.0);

  // ---- Normalised RGB ratios ----
  float sumCal = R_cal + G_cal + B_cal;
  float R_norm = R_cal / sumCal;
  float G_norm = G_cal / sumCal;
  float B_norm = B_cal / sumCal;

  // ---- Print RAW values ----
  Serial.print("RAW RGB    -> R:");
  Serial.print(r);
  Serial.print(" G:");
  Serial.print(g);
  Serial.print(" B:");
  Serial.print(b);
  Serial.print(" C:");
  Serial.println(c);

  // ---- Print normalised RGB ----
  Serial.print("NORM RGB%  -> R:");
  Serial.print(R_norm, 3);
  Serial.print(" G:");
  Serial.print(G_norm, 3);
  Serial.print(" B:");
  Serial.println(B_norm, 3);

    // ---- Print Clear Channel ----
  Serial.print("BRIGHTNESS -> C:"); 
  Serial.println(C_cal, 3);

  Serial.println("------------------------------");
  delay(500);
}
