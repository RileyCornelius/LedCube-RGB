#include <Arduino.h>
#include <FastLED.h>

#define ROW_SIZE 9
#define COLUMN_SIZE 9
#define LED_COUNT (ROW_SIZE * COLUMN_SIZE)
#define LED_TYPE PL9823
#define LED_COLOR_ORDER RGB
#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4

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
    FastLED.addLeds<LED_TYPE, LED_PIN_1, LED_COLOR_ORDER>(leds, LED_COUNT);
    FastLED.addLeds<LED_TYPE, LED_PIN_2, LED_COLOR_ORDER>(leds, LED_COUNT);
    FastLED.addLeds<LED_TYPE, LED_PIN_3, LED_COLOR_ORDER>(leds, LED_COUNT);
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
        fadeAll(20);
        leds[i] = colors[index];
        FastLED.show();
        delay(40);
    }
}