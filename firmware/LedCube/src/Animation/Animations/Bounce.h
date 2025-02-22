#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Bounce : public Animation
{
public:
    Bounce()
    {
        name = __FUNCTION__;
        setDelay(75);

        updateBall(ball1, v1init);
        updateBall(ball2, v2init);
        updateBall(ball3, v3init);
    };
    static const uint8_t ballSize = 8;

    CRGB color = CRGB::Blue;

    int8_t v1init[3] = {2, 3, 0};
    int8_t v1[3] = {1, 1, 1};
    Point ball1[ballSize] = {Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0), Point(1, 1, 0),
                             Point(0, 0, 1), Point(1, 0, 1), Point(0, 1, 1), Point(1, 1, 1)};

    int8_t v2init[3] = {5, 6, 0};
    int8_t v2[3] = {-1, 1, 1};
    Point ball2[ballSize] = {Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0), Point(1, 1, 0),
                             Point(0, 0, 1), Point(1, 0, 1), Point(0, 1, 1), Point(1, 1, 1)};

    int8_t v3init[3] = {1, 2, 3};
    int8_t v3[3] = {-1, -1, 1};
    Point ball3[ballSize] = {Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0), Point(1, 1, 0),
                             Point(0, 0, 1), Point(1, 0, 1), Point(0, 1, 1), Point(1, 1, 1)};

    void setBallVoxel(Point *ball, CRGB color)
    {
        for (size_t i = 0; i < ballSize; i++)
        {
            Cube.setLed(ball[i], color);
        }
    }

    void updateBall(Point *ball, int8_t *v)
    {
        for (size_t i = 0; i < ballSize; i++)
        {
            ball[i].x += v[0];
            ball[i].y += v[1];
            ball[i].z += v[2];
        }

        for (size_t i = 0; i < ballSize; i++)
        {
            if (ball[i].x == CUBE_SIZE_M1 || ball[i].x == 0)
            {
                v[0] = -v[0];
                break;
            }
        }
        for (size_t i = 0; i < ballSize; i++)
        {
            if (ball[i].y == CUBE_SIZE_M1 || ball[i].y == 0)
            {
                v[1] = -v[1];
                break;
            }
        }
        for (size_t i = 0; i < ballSize; i++)
        {
            if (ball[i].z == CUBE_SIZE_M1 || ball[i].z == 0)
            {
                v[2] = -v[2];
                break;
            }
        }
    }

    // void moveBall(Point &ball, int8_t v[3])
    // {
    //     ball.x += v[0];
    //     ball.y += v[1];
    //     ball.z += v[2];

    //     if (ball.x == CUBE_SIZE_M1 || ball.x == 0)
    //         v[0] = -v[0];

    //     if (ball.y == CUBE_SIZE_M1 || ball.y == 0)
    //         v[1] = -v[1];

    //     if (ball.z == CUBE_SIZE_M1 || ball.z == 0)
    //         v[2] = -v[2];
    // }

    void drawFrame() override
    {
        Cube.fadeAll(170);

        setBallVoxel(ball1, CRGB::Blue);
        updateBall(ball1, v1);

        setBallVoxel(ball2, CRGB::Green);
        updateBall(ball2, v2);

        setBallVoxel(ball3, CRGB::Red);
        updateBall(ball3, v3);
    }
};