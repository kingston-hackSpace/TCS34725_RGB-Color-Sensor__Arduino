# TCS34725 RGB-Color-Sensor___Arduino

The [TCS34725 RGB sensor](https://learn.adafruit.com/adafruit-color-sensors/overview) provides a digital return of red, green, blue (RGB), and clear light sensing values. An RGB Color sensor helps you accurately detect an object’s colour in your Arduino projects.

----
**TCS34725 on-board white LED**

Used to provide constant illumination. 

The LED pin can be pulled low to turn off the LED. This can be done by:

  1. Wiring directly to ground to turn it off completely.
     
  2. Wiring to a spare digital pin and control it with digitalWrite().

----
# TUTORIAL SET-UP for Arduino
----
### HARDWARE

- Arduino UNO
- TCS3472 sensor
----
### WIRING
Reference image [here](https://github.com/kingston-hackSpace/TCS34725_RGB-Color-Sensor/blob/main/WiringDiagram_RGB-Sensor.png)

Arduino UNO|RGB Sensor
-|-
GND | GND
5V | VIN
A4 | SDA
A5 | SCL (I2C Clock signal)

----
## TUTORIAL 1: Visualizing RGB-sensor data in the Arduino Serial Monitor
----
   
- Download the corresponding libraries [Adafruit_TCS34725](https://github.com/CamilaColussi-KSA/Adafruit_TCS34725)

- Install the libraries via "Importing a .zip Library". Instructions [here](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries/)

- Open Arduino IDE and find the sensor examples:
   - File > Examples > Adafruit TCS34725 > tcs34725

- Upload the code to your Arduino board.

- Open Arduino's Serial Monitor to see the incoming data.

- Visit [this link](https://github.com/kingston-hackSpace/TCS34725_RGB-Color-Sensor__Arduino/blob/main/Understanding_the_values.md) for further understanding of your sensor's incoming data.

----

### Useful TIPS

- Place different objects in front of the sensor to perform colour readings. See reference [here](https://www.youtube.com/watch?v=FQnzRW4XukA&t=5s)
  
- The closer and more centred, the more accurate the colour reading.

- If your object is too far or at an angle, readings may be weak or uneven.

- The TCS34725 LED helps reduce ambient light interference. The LED provides constant and stable illumination. 

----
## TUTORIAL 2: Calibrating the sensor for accurate readings

- Upload [this code](https://github.com/kingston-hackSpace/TCS34725_RGB-Color-Sensor/blob/main/RGB_Sensor_RGB-cal.ino) to your Arduino board.

- Open the Arduino Serial Monitor to see the incoming data.
  
- Place a matte-pure-white-card close to the sensor (usually 5–10 mm away).
  
- Make sure the sensor’s illumination LED is on.
  
- With the card still covering the sensor, press the **RESET** button on the Arduino. The Arduino code will reload, allowing us to collect a baseline of white readings.

- Look at the Serial Monitor and wait until the calibration is completed.

- You now will see new values with calibrated data.

- The new sensor values represent:

  - Raw RGB readings + Raw Brightness(C) (0 - 65,535)
    
  - RGB percentages (%) as normalised values (0.0 - 1.0)
    
  - Normalised brightness values (0.0 - 1.0)
  
----
## TUTORIAL 3: Sensing HSV

- Upload [this code](https://github.com/kingston-hackSpace/TCS34725_RGB-Color-Sensor/blob/main/RGB_Sensor_HSV-cal.ino) to your Arduino board

----
## TUTORIAL 4:  Naming HSV colours

- Upload [this code](https://github.com/kingston-hackSpace/TCS34725_RGB-Color-Sensor/blob/main/RGB_sensor_HSV-names.ino) to your Arduino board

----
### MORE TUTORIALS

- [Interfacing a TCS34725 RGB Color Sensor With Arduino – A Complete Guide](https://www.makerguides.com/tcs34725-rgb-color-sensor-with-arduino/)

- [LED lighting based on colour readings](https://learn.adafruit.com/adafruit-color-sensors/arduino-code)
