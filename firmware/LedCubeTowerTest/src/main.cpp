#include <Arduino.h>
// #include "Cube/Cube.h"

#include <FastLED.h>

#define CUBE_SIZE 9
#define ROW_SIZE 9
#define COLUMN_SIZE 3
#define LED_COUNT (ROW_SIZE * COLUMN_SIZE)
#define LED_TYPE PL9823
#define LED_COLOR_ORDER RGB
#define LED_PIN 2

CRGB leds[LED_COUNT];

void fadeAll(uint8_t scale)
{
    for (size_t i = 0; i < LED_COUNT; i++)
    {
        leds[i].fadeToBlackBy(scale);
    }
}

void setup()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, LED_COUNT);
    FastLED.addLeds<LED_TYPE, 18, LED_COLOR_ORDER>(leds, LED_COUNT);
}

void loop()
{
    static int index = 0;
    static CRGB colors[] = {CRGB(255, 0, 0), CRGB(0, 255, 0), CRGB(0, 0, 255)}; // red, green, blue

    index++;
    if (index >= 3)
        index = 0;

    for (int i = 0; i < LED_COUNT; i++)
    {
        fadeAll(40);
        leds[i] = colors[index];
        FastLED.show();
        delay(40);
    }
}