#include <Arduino.h>
#include <Button.h>
#include <Logger.h>
#include "Cube/Cube.h"
#include "Animator/Animator.h"
#include "OTA/ota.h"
#include "Animations.h"

#include "Display/Display.h"

Animation *animations[] = {
    new Gradient(),
    new Solid(),
    new Linear(),
    new BPM(),
    new Confetti(),
    new Sinelon(),
    new Rainbow(),
};

Animator animator = Animator(animations, ARRAY_SIZE(animations));
Button nextButton = Button(PIN_NEXT_BTN);
Button playPauseButton = Button(PIN_PAUSE_BTN);

void setupFastLED()
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

void checkInputs()
{
    if (nextButton.debounce())
        animator.next();

    if (playPauseButton.debounce())
        animator.togglePlay();
}

void setup()
{
    Serial.begin(115200);
    SerialDisplay.begin(115200);
    setupFastLED();
    otaBegin();
}

void loop()
{
    otaHandle();
    readDisplay();
    checkInputs();
    animator.run();
}
