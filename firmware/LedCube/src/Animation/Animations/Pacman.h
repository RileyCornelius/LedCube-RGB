#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"
#include "Cube/Bitmaps/pacman.h"
#include "Cube/Bitmaps/pacman_ghost.h"

class Pacman : public Animation
{
public:
    Pacman()
    {
        name = __FUNCTION__;
        setDelay(130);

        uint8_t y = 1;

        updateBitmap();
    };

    enum Sprite
    {
        PACMAN,
        GHOST,
    };

    float angle = 0;
    CRGB tempCube[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE] = {0};
    uint8_t hue = 0;
    const uint16_t pacmanRereshRate = 200;
    const uint16_t ghostRereshRate = 500;
    uint8_t pacmanFrame = 0;
    uint8_t ghostFrame = 0;
    uint8_t spriteToDraw = 0;

    int8_t moveX = 0;
    int8_t posY = 0;

    int8_t dir = 1;

    void clearTempCube()
    {
        for (int8_t x = 0; x < CUBE_SIZE; x++)
            for (int8_t y = 0; y < CUBE_SIZE; y++)
                for (int8_t z = 0; z < CUBE_SIZE; z++)
                {
                    tempCube[x][y][z] = CRGB::Black;
                }
    }

    void updateBitmap()
    {
        clearTempCube();
        for (int8_t z = 0; z < CUBE_SIZE; z++)
            for (int8_t x = 0; x < CUBE_SIZE; x++)
            {
                // pacman on the front
                uint32_t frame = pacman_data[pacmanFrame][z * CUBE_SIZE + x];
                CRGB col = CRGB::Black;
                if (frame >> 24 & 0xFF) // if not transparent
                {
                    col = CRGB((frame & 0xff), (frame >> 8) & 0xff, (frame >> 16 & 0xff)); // get rgb from data
                }
                tempCube[CUBE_SIZE_M1 - x][1][CUBE_SIZE_M1 - z] = col;

                // ghost on the back
                frame = ghost_data[ghostFrame][z * CUBE_SIZE + x];
                col = CRGB::Black;
                if (frame >> 24 & 0xFF) // if not transparent
                {
                    col = CRGB((frame & 0xff), (frame >> 8) & 0xff, (frame >> 16 & 0xff)); // get rgb from data
                }
                tempCube[CUBE_SIZE_M1 - x][CUBE_SIZE_M1 - 1][CUBE_SIZE_M1 - z] = col;
            }
    }

    bool updateSpriteFrame()
    {
        bool changed = false;
        EVERY_N_MILLIS(50)
        {
            pacmanFrame++;
            if (pacmanFrame >= PACMAN_FRAME_COUNT)
                pacmanFrame = 0;

            changed = true;
        }
        EVERY_N_MILLIS(250)
        {
            ghostFrame++;
            if (ghostFrame >= GHOST_FRAME_COUNT)
                ghostFrame = 0;

            changed = true;
        }

        return changed;
    }

    void movePacmanGhost(uint8_t y)
    {
        Cube.clear();
        for (int8_t z = 0; z < CUBE_SIZE; z++)
            for (int8_t x = 0; x < CUBE_SIZE; x++)
            {
                if (spriteToDraw == PACMAN)
                {
                    uint32_t frame = pacman_data[pacmanFrame][z * CUBE_SIZE + x];
                    if (frame >> 24 & 0xFF) // if not transparent
                    {
                        CRGB col = CRGB((frame & 0xff), (frame >> 8) & 0xff, (frame >> 16 & 0xff)); // get rgb from data
                        Vector3 v = Vector3(CUBE_SIZE_M1 - x, y, CUBE_SIZE_M1 - z);
                        if (dir == 1)
                            v = v.rotate(180, Axis::Z);
                        v += Vector3(moveX, 0, 0);
                        Cube.setLed(v, col);
                    }
                }
                else if (spriteToDraw == GHOST)
                {
                    uint32_t frame = ghost_data[ghostFrame][z * CUBE_SIZE + x];
                    if (frame >> 24 & 0xFF) // if not transparent
                    {
                        CRGB col = CRGB((frame & 0xff), (frame >> 8) & 0xff, (frame >> 16 & 0xff)); // get rgb from data
                        Vector3 v = Vector3(CUBE_SIZE_M1 - x, y, CUBE_SIZE_M1 - z);
                        if (dir == 1)
                            v = v.rotate(180, Axis::Z);
                        v += Vector3(moveX, 0, 0);
                        Cube.setLed(v, col);
                    }
                }
            }

        moveX = dir ? moveX + 1 : moveX - 1;
        if (moveX < -CUBE_SIZE || moveX > CUBE_SIZE)
        {
            spriteToDraw = !spriteToDraw;
            if (spriteToDraw == PACMAN)
            {
                dir = !dir;
                posY = random8(0, CUBE_SIZE_M1);
                updateTimer.setPeriod(random8(80, 150));
            }
            moveX = dir ? -CUBE_SIZE : CUBE_SIZE;
        }
    }

    // void rotatePacman()
    // {
    //     Cube.clear();
    //     for (int x = 0; x < CUBE_SIZE; x++)
    //         for (int y = 0; y < CUBE_SIZE; y++)
    //             for (int z = 0; z < CUBE_SIZE; z++)
    //             {
    //                 CRGB color = tempCube[x][y][z];
    //                 if (color != CRGB(0, 0, 0))
    //                 {
    //                     Vector3 v = Vector3(x, y, z).rotate(angle, Axis::Z);
    //                     Cube.setLed(v, color);
    //                 }
    //             }

    //     // Increase angle
    //     angle += 10;
    //     if (angle >= 360)
    //     {
    //         angle = 0;
    //     }
    // }

    // void movePacman()
    // {
    //     Cube.clear();
    //     for (int x = 0; x < CUBE_SIZE; x++)
    //         for (int y = 0; y < CUBE_SIZE; y++)
    //             for (int z = 0; z < CUBE_SIZE; z++)
    //             {

    //                 CRGB color = tempCube[x][y][z];
    //                 if (color != CRGB(0, 0, 0))
    //                 {
    //                     Vector3 v = Vector3(x, y, z);
    //                     // v = v.rotate(180.0, Axis::X);
    //                     v += Vector3(moveX, 0, 0);
    //                     Cube.setLed(v, color);
    //                 }
    //             }

    //     // // Move through the cube forward
    //     // moveX++;
    //     // if (moveX > CUBE_SIZE)
    //     //     moveX = -CUBE_SIZE;

    //     // Move through the cube backwards
    //     moveX--;
    //     if (moveX < -CUBE_SIZE)
    //         moveX = CUBE_SIZE;
    // }

    void drawFrame() override
    {
        updateSpriteFrame();
        movePacmanGhost(posY);
    }
};