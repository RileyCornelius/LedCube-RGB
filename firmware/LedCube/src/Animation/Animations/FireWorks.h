#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class FireWorks : public Animation
{
public:
    FireWorks()
    {
        name = "Fire Works";
        setDelay(40);
    };

    Timer preMissileTimer;
    const Vector3 gravity = Vector3(0, 0, -1.0);

    uint8_t missileHue = 0;
    uint8_t explosionHue;
    float radius;
    Vector3 temp;
    Vector3 source;
    Vector3 target;
    Vector3 velocity;
    Particle missile;
    float explosionRadius = 0;
    float explosionMaxRadius;

    enum State
    {
        PREPARE_MISSILE,
        LAUNCHING,
        EXPLODING,
        RESET,
    };

    State state = PREPARE_MISSILE;

    void drawFrame() override
    {
        Cube.fadeAll(65);

        switch (state)
        {
        case PREPARE_MISSILE:

            if (preMissileTimer.ready())
            {
                source = Vector3(randomFloat(3, 5), randomFloat(3, 5), 0);
                target = Vector3(randomFloat(3, 6), randomFloat(3, 6), randomFloat(4.5, 6.5));
                float timeToTarget = randomFloat(1.2, 2.0);
                velocity = (target - source) / timeToTarget;
                missileHue = random8(0, 255);
                missile = Particle(source, velocity, missileHue, timeToTarget);
                Cube.setLed(missile.position, CHSV(missileHue, 255, 255));
                state = LAUNCHING;
            }
            break;
        case LAUNCHING:
            temp = missile.position;
            missile.move(getDeltaTime(), gravity);
            Cube.setLed(missile.position, CHSV(missileHue, 255, 255));

            if (temp.z > missile.position.z || missile.position.z > target.z)
            {
                explosionMaxRadius = randomFloat(2.5, 4.5);
                explosionHue = missileHue + random8(5, 15);
                state = EXPLODING;
            }
            break;

        case EXPLODING:
            explosionRadius += 0.5f;
            Cube.shell(missile.position, explosionRadius, CHSV(explosionHue++, 255, 255), randomFloat(0.1, 0.5));

            if (explosionRadius > explosionMaxRadius)
            {
                state = RESET;
            }
            break;

        case RESET:
            explosionRadius = 0;
            preMissileTimer.reset();
            preMissileTimer.setPeriod(random16(300, 800));
            state = PREPARE_MISSILE;
            break;
        }
    }
};