# UNDERSTANDING THE VALUES

----
**Color Temperature (measured in Kelvin)**

  Typical range:

      1,500–3,000 K → warm / yellow

      3,000–5,000 K → neutral white

      5,000–7,000 K → cool daylight

      7,000–10,000+ K → very blue-ish light

----
**Lux (Lumens per Square Meter)**

*The TCS34725 can read up to about 40k–50k lux before saturating*, depending on settings.

    Typical range:

      0–10 lux → very dark

      10–100 lux → dim indoor light

      100–1,000 lux → normal indoor light

      1,000–10,000 lux → outdoors shade

      10,000–100,000 lux → bright sunlight

----
**Clear Light (unfiltered) value**

The TCS34725 measures light using a 16-bit ADC (analogue-to-digital converter).

A 16-bit number can count from:

    - 0 (no light detected)

    - to 65,535 (maximum)

  Typical range:

    0–2,000 → dim or dark

    2,000–10,000 → normal indoor lighting

    10,000–40,000 → bright room or daylight

    40,000+ → very bright / outdoor sun

    65,535 → too bright (saturation)

----
**R, G and B values**

The TCS34725 sensor doesn’t output human-readable colour names. Instead, it provides raw digital values via a 16-bit ADC (analogue-to-digital converter), representing the intensity of red, green, and blue light detected.

These raw values give a reference of colour predominance — for example, if the red channel is much higher than green or blue, the object is likely red. However, for consistent comparisons, it is recommended to normalise these values (e.g., scale according to total light intensity or to a standard 0–255 range).

The 16-bit RGB raw values can range from:

    0 to 65,535

