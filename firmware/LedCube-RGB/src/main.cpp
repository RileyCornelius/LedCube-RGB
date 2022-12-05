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
};

Animator animator = Animator(animations, ARRAY_LENGTH(animations));
Button nextButton = Button(NEXT_BTN_PIN);

void setup()
{
    animator.setupFastLED();
}

void loop()
{
    if (nextButton.debounce())
        animator.next();

    animator.update();
    FastLED.show();
}
