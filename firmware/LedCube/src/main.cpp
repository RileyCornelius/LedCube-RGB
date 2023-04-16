#include <Arduino.h>
#include <Button.h>
#include <Logger.h>
#include "Cube/Cube.h"
#include "Animator/Animator.h"
#include "Animations.h"

Animation *animations[] = {
    new Linear(),
    new Gradient(),
    new Confetti(),
    new Sinelon(),
    new Rainbow(),
    new BPM(),
    new Solid(),
};

Animator animator = Animator(animations, ARRAY_SIZE(animations));
Button nextButton = Button(NEXT_BTN_PIN);
Button pauseButton = Button(PAUSE_BTN_PIN);

inline void setupFastLED()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 0, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, LED_1_PIN, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 1, LED_BRANCH_COUNT);
}

inline void checkInputs()
{
    if (nextButton.debounce())
        animator.next();

    if (pauseButton.debounce())
        animator.pause();
}

void setup()
{
    Serial.begin(115200);
    DisplaySerial.begin(115200);
    setupFastLED();
}

void loop()
{
    checkInputs();
    animator.loop();
}
