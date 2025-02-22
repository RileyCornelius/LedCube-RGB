#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Text : public Animation
{
public:
    Text(const char *text)
    {
        name = text;
        ascii = text;
        setDelay(100);
    };

    const char *ascii;
    CRGB color = CRGB::Blue;
    int8_t y = CUBE_SIZE_M1;
    uint8_t index = 0;
    bool thin = false;

    void drawFrame() override
    {
        if (y < 0)
        {
            color = CHSV(random8(), 255, 255);
            y = CUBE_SIZE_M1;
            index++;
            if (ascii[index] == '\0')
            {
                thin = !thin;
                index = 0;
            }
            if (ascii[index] == ' ')
                Cube.fadeAll(200);
        }

        Cube.fadeAll(180);
        thin ? Cube.asciiThin(ascii[index], y, color) : Cube.ascii(ascii[index], y, color);
        y--;
    }
};

class TextRotate : public Animation
{
public:
    TextRotate(const char *text)
    {
        name = text;
        ascii = text;
        setDelay(80);
    };

    const char *ascii;
    CRGB color = CRGB::Blue;
    uint8_t index = 0;
    float angle = 0.0f;
    LedCube tempCube = LedCube();

    void drawFrame() override
    {
        // Motion blur
        Cube.fadeAll(150);

        // Draw text on temp cube
        tempCube.clear();
        tempCube.asciiThin(ascii[index], CUBE_CENTER, color);

        // Rotate text
        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                    if (tempCube.getLed(x, y, z) != CRGB(CRGB::Black))
                    {
                        // Quaternion q = Quaternion(angle, Axis::Z);
                        // Vector3 v = q.rotate(Vector3(x, y, z));
                        // Cube.setLed(v, color);

                        Vector3 v = Vector3(x, y, z).rotate(angle, Axis::Z);
                        Cube.setLed(v, color);

                        // Point p = Point(x, y, z).rotate(Angles(0, 0, angle));
                        // Cube.setLed(p, color);
                    }

        // fade in and out
        if (angle > 300)
            Cube.fadeAll(map(angle, 300, 360, 0, 255));
        else if (angle < 60)
            Cube.fadeAll(map(angle, 60, 0, 0, 255));

        // Increase angle and go to next letter after full rotation
        angle += 10;
        if (angle >= 360)
        {
            angle = 0;
            index++;
            if (ascii[index] == '\0')
            {
                index = 0;
            }
        }
    }
};