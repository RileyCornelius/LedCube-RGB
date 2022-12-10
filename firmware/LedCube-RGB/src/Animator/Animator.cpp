#include "Animator.h"
#include <FastLED.h>
#include "Cube/Cube.h"
#include "config.h"

enum State : uint8_t
{
    Stop = 0,
    Idle,
    Starting,
    Running,
    Ending
};

/*--------------------------- PUBLIC FUNCTIONS ---------------------------*/
Animator::Animator(Animation *animations[], uint16_t length)
{
    addAnimationArray(animations, length);
    count = 0;
    head = NULL;
    transition = NULL;
    isRotating = false;
    state = Running;
}

void Animator::setupFastLED(uint8_t scale)
{
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(Cube.leds, LED_COUNT);
    FastLED.setBrightness(scale);
}

void Animator::pause()
{
    if (state != Idle)
        transitionState(NULL);
    else
        transitionState(current);
}

void Animator::first()
{
    transitionState(head);
}

void Animator::next()
{
    transitionState(current->next);
}

void Animator::previous()
{
    transitionState(current->prev);
}

void Animator::rotateBegin(uint32_t time)
{
    isRotating = true;
    rotationTimer.setPeriod(time);
}

void Animator::rotateEnd()
{
    isRotating = false;
}

void Animator::stateMachine()
{
    if (isRotating && rotationTimer.ready())
        next();

    switch (state)
    {
    case Stop:
        FastLED.clear(true);
        FastLED.setBrightness(0);
        if (transitioning())
            state = Starting;
        else
            state = Idle;
        break;

    case Idle:
        break;

    case Starting:
        if (fadeIn())
            state = Running;
        break;

    case Running:
        animate();
        break;

    case Ending:
        if (fadeOut())
            state = Stop;
        break;
    }
}

/*--------------------------- PRIVATE FUNCTIONS --------------------------*/
void Animator::addAnimationArray(Animation *animations[], uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
        addAnimation(animations[i]);
}

void Animator::addAnimation(Animation *animation)
{
    // Circular doubly linked list
    count++;              // increase total animations count
    if (head == NULL)     // will only run once on an empty list
        head = animation; // set first animation as head
    else
    {
        current->next = animation; // change the current next animation to the new animation instead of the head
        head->prev = animation;    // change head to point backwards to the new animation
    }

    animation->next = head;    // is makes the list circular
    animation->prev = current; // is makes the list doubly linked
    current = animation;       // finally make the new animation the new current animation
}

void Animator::transitionState(Animation *nextAnimation)
{
    state = Ending;
    transition = nextAnimation;
}

bool Animator::transitioning()
{
    if (transition != NULL)
    {
        current = transition;
        transition = NULL;
        return true;
    }
    return false;
}

bool Animator::fadeIn()
{
    uint8_t brightness = FastLED.getBrightness();
    if (brightness == 255) // TODO: replace 255 with max brightness var
        return true;

    FastLED.setBrightness(++brightness);
    animate(); // fade in while updating the animation
    return false;
}

bool Animator::fadeOut()
{
    uint8_t brightness = FastLED.getBrightness();
    if (brightness == 0)
        return true;

    FastLED.setBrightness(--brightness);
    FastLED.show(); // fade out the last state of the animation
    return false;
}

void Animator::animate()
{
    if (current->animate())
        FastLED.show();
}