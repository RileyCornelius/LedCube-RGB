#include <Arduino.h>
#include <Logger.h>
#include "Cube/Cube.h"
#include "Animator/Animator.h"
#include "Animation/Animations/Animations.h"
#include "Communication/Display.h"

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

    Cube.init();
    animator.init();
    animator.setRotationTime(30000);
    animator.setRotating(true);
}

void loop()
{
    handleDisplay();
    animator.loop();
}
