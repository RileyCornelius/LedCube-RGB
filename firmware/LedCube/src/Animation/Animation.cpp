#include "Animation.h"
#include "Cube.h"

Animation::Animation()
{
    setDelay(5);
}

uint16_t Animation::getFps(bool actual)
{
    if (actual)
        return FastLED.getFPS(); // hardware update rate
    else
        return 1000 / updateTimer.getPeriod(); // software update rate
}

/**
 * Set the fps between frames
 * @param fps in frames per second
 */
void Animation::setFps(uint16_t fps)
{
    setDelay(1000 / fps);
}

/**
 * Set the delay between frames
 * @param delay in milliseconds
 */
void Animation::setDelay(uint32_t delay)
{
    updateTimer.setPeriod(delay);
}

/**
 * Clears the cube
 */
void Animation::clear()
{
    FastLED.clear(true);
}

/**
 * Virtual function to be overridden by child classes
 * Default implementation fades in the new animation
 * @return True if the fade is finished, false otherwise
 */
bool Animation::beginning()
{
    uint8_t brightness = FastLED.getBrightness();
    if (brightness < LED_BRIGHTNESS)
    {
        if (transitionTimer.ready())
        {
            FastLED.setBrightness(++brightness);
            animate();
        }
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * Virtual function to be overridden by child classes
 * Default implementation fades out the last state of the animation
 * @return True if the fade is finished, false otherwise
 */
bool Animation::ending()
{
    uint8_t brightness = FastLED.getBrightness();
    if (brightness > 35)
    {
        if (transitionTimer.ready())
        {
            FastLED.setBrightness(--brightness);
            FastLED.show(); // fade out the last state of the animation
        }
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * Draw the current frame of the animation and show it on the cube when the timer is ready
 */
void Animation::animate()
{
    deltaTime = updateTimer.getElapsed() / 1000.0f;
    if (updateTimer.ready())
    {
        drawFrame();
        FastLED.show();
    }
}