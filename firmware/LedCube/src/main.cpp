#include <Arduino.h>
#include <Logger.h>
#include "Cube/Cube.h"
#include "Animator/Animator.h"
#include "Animation/Animations/Animations.h"
#include "Communication/Display.h"
#include "Config/Config.h"
#include "Config/Pins.h"

Animation *animations[] = {
    // new Draw(),
    // new Fire(),
    // new MatrixRain(),
    new Pacman(),
    // new Smile(),
    new Arrow(),
    new FireWorks(),
    new Rain(),
    new TextRotate("RRC"),
    new Sparkles(),
    new Ripple(),
    new Sinelon(),
    new Spiral(),
    // new Text("123456789 "),
    new Bounce(),
    // new Box(),
    new Sphere(),
    // new Gradient(),
    new Rainbow(),
};

Animator animator(animations, ARRAY_SIZE(animations));

void setup()
{
    SERIAL_BEGIN(115200);  // Logging
    DISPLAY_BEGIN(115200); // Display communication

    // Initialize 9 branches of 81 LEDs each, total of 729 LEDs
    FastLED.addLeds<LED_TYPE, PIN_LED_0, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 0, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_1, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 1, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_2, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 2, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_3, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 3, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_4, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 4, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_5, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 5, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_6, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 6, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_7, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 7, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_8, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 8, LED_BRANCH_COUNT);
    FastLED.clear(true); // Turn off all LEDs

    animator.rotate();
}

void loop()
{
    handleDisplay();
    animator.run();
}
