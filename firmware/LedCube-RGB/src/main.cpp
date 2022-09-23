#include <Arduino.h>
#include <Debounce.h>
#include <Potentiometer.h>
#include "Animator/Animator.h"

#define PREV_BTN_PIN A0
#define NEXT_BTN_PIN A5
#define BRIGHTNESS_POT_PIN A4

Button prevButton = Button(PREV_BTN_PIN);
Button nextButton = Button(NEXT_BTN_PIN);
Potentiometer brightnessPot = Potentiometer(BRIGHTNESS_POT_PIN);

Animation *pAnimations[] = {
    new Linear(),
    new Wave(),
    new Sparkles(),
    new Solid(),
};

Animator animator = Animator(pAnimations, ARRAY_LENGTH(pAnimations));

void checkInputs()
{
    if (nextButton.debounce())
        animator.next();

    if (prevButton.debounce())
        animator.previous();

    if (brightnessPot.changed())
        FastLED.setBrightness(brightnessPot.get8());
}

void setup()
{
    FastLED.addLeds<PIXEL_TYPE, PIXEL_PIN, COLOR_ORDER>(Cube.leds, PIXEL_COUNT);
    Serial.begin(9600);

    // animator.rotateBegin(15000);
}

void loop()
{
    checkInputs();

    animator.update();
    FastLED.show();
}
