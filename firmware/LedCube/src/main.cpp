#include <Arduino.h>
#include <SimpleButton.h>
#include <Logger.h>
#include "Cube.h"
#include "Animator.h"
#include "Animations.h"
#include "display.h"
#include "ota.h"

Animation *animations[] = {
    new Shell(),
    new Sphere(),
    new Spiral(),
    new Gradient(),
    new Rainbow(),
    new Ripple(),
    // new Sinelon(),

    // new Sparkles(),
    // new Linear(),
    // new Solid(),
    // new Confetti(),
    // new BPM(),
    // new Rainbow(),
};

Animator animator(animations, ARRAY_SIZE(animations));
Button nextButton(PIN_NEXT_BTN);
Button playPauseButton(PIN_PAUSE_BTN);

void initFastLED()
{
    FastLED.addLeds<LED_TYPE, PIN_LED_0, LED_COLOR_ORDER>(Cube.leds, LED_PER_BRANCH_COUNT * 0, LED_PER_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_1, LED_COLOR_ORDER>(Cube.leds, LED_PER_BRANCH_COUNT * 1, LED_PER_BRANCH_COUNT);
#ifndef TEST_BOARD
    FastLED.addLeds<LED_TYPE, PIN_LED_2, LED_COLOR_ORDER>(Cube.leds, LED_PER_BRANCH_COUNT * 2, LED_PER_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_3, LED_COLOR_ORDER>(Cube.leds, LED_PER_BRANCH_COUNT * 3, LED_PER_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_4, LED_COLOR_ORDER>(Cube.leds, LED_PER_BRANCH_COUNT * 4, LED_PER_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_5, LED_COLOR_ORDER>(Cube.leds, LED_PER_BRANCH_COUNT * 5, LED_PER_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_6, LED_COLOR_ORDER>(Cube.leds, LED_PER_BRANCH_COUNT * 6, LED_PER_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_7, LED_COLOR_ORDER>(Cube.leds, LED_PER_BRANCH_COUNT * 7, LED_PER_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_8, LED_COLOR_ORDER>(Cube.leds, LED_PER_BRANCH_COUNT * 8, LED_PER_BRANCH_COUNT);
#endif
}

void handleInputs()
{
    if (nextButton.pressed())
        animator.next();

    if (playPauseButton.pressed())
        animator.togglePlay();
}

void setup()
{
    SERIAL_BEGIN(115200);
    DISPLAY_BEGIN(115200);
    initFastLED();
    initOta();
}

void loop()
{
    handleOta();
    handleDisplay();
    handleInputs();
    animator.run();
}
