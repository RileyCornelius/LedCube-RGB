#include <Arduino.h>
#include <Logger.h>
#include <BlynkSimpleEsp32.h>
#include "Cube.h"
#include "Animator.h"
#include "Animations.h"
#include "display.h"
#include "ota.h"
#include "config.h"
#include "secret.h"

Animation *animations[] = {
    // new Draw(),
    // new Fire(),
    // new MatrixRain(),
    new Pacman(),
    new Smile(),
    new Arrow(),
    new FireWorks(),
    new Rain(),
    new TextRotate("RC"),
    new Sparkles(),
    new Ripple(),
    new Sinelon(),
    new Spiral(),
    new Text("123456789 "),
    new Bounce(),
    new Box(),
    new Sphere(),
    new Gradient(),
    new Rainbow(),
};

Animator animator(animations, ARRAY_SIZE(animations));

BLYNK_WRITE(V1)
{
    String action = param.asStr();

    if (action == "play")
        animator.play();
    if (action == "stop")
        animator.stop();
    if (action == "next")
        animator.next();
    if (action == "prev")
        animator.previous();

    Blynk.virtualWrite(V0, animator.getNextAnimationName());
}

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

    Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS); // Blynk App
    initOta();                                           // Over the Air Update
}

void loop()
{
    handleDisplay();
    handleOta();
    Blynk.run();
    animator.run();
}
