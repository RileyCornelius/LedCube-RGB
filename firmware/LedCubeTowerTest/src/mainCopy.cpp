// #include <Arduino.h>
// #include <FastLED.h>

// #define ROW_SIZE 9
// #define TOWER_COUNT (ROW_SIZE * 3)

// #define LED_COUNT ROW_SIZE
// #define LED_TYPE PL9823
// #define LED_COLOR_ORDER RGB
// #define LED_PIN 2

// CRGB leds[LED_COUNT];

// void setup()
// {
//   FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, LED_COUNT);
// }

// void loop()
// {
//   static int index = 0;
//   if (index >= 4)
//     index = 0;

//   // CRGB color = CRGBPalette16(CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::White)[index++];
//   CRGB color = CRGBPalette16(CRGB(255, 0, 0), CRGB(0, 255, 0), CRGB(0, 0, 255), CRGB::White)[index++];

//   for (int i = 0; i < LED_COUNT; i++)
//   {
//     leds[i] = color;
//     FastLED.show();
//     delay(100);
//   }
//   for (size_t i = 0; i < LED_COUNT; i++)
//   {
//     leds[i] = CRGB::Black;
//   }
// }