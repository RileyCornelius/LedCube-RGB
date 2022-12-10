#include <Arduino.h>
#include <FastLED.h>
#include <Button.h>
#include "Cube/Cube.h"
#include "Animator/Animator.h"
#include "Animations.h"

Animation *animations[] = {
    new Sparkles(),
    new Wave(),
    new Linear(),
    new Solid(),
};

Animator animator = Animator(animations, ARRAY_LENGTH(animations));
Button nextButton = Button(NEXT_BTN_PIN);
Button prevButton = Button(PREV_BTN_PIN);
Button pauseButton = Button(PAUSE_BTN_PIN);

void setup()
{
    animator.setupFastLED();
}

void loop()
{
    if (nextButton.debounce())
        animator.next();

    if (prevButton.debounce())
        animator.previous();

    if (pauseButton.debounce())
        animator.pause();

    animator.stateMachine();
}
