#include <Arduino.h>
#include <Button.h>
#include "Cube/Cube.h"
#include "Animator/Animator.h"
#include "Animations.h"

Animation *animations[] = {
    new Solid(),
    new Sparkles(),
    new Wave(),
    new Linear(),
    new Fire(),
};

Animator animator = Animator(animations, ARRAY_SIZE(animations));
Button nextButton = Button(NEXT_BTN_PIN);
Button prevButton = Button(PREV_BTN_PIN);

void setupFastLED()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 0, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, LED_1_PIN, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 1, LED_BRANCH_COUNT);
    // FastLED.setBrightness(200);
    // FastLED.setMaxPowerInVoltsAndMilliamps(5, 5000);
}
#define NOP() __asm__("nop"); // no operation

void checkInputs()
{
    if (nextButton.debounce())
        animator.next();

    if (prevButton.debounce())
        animator.previous();
}

void setup()
{
    Serial.begin(115200);
    setupFastLED();
}

void loop()
{
    checkInputs();
    NOP();
    animator.animate();
}
