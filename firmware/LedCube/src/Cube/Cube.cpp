#include "Cube.h"

// Global cube helper object for Animation sub classes
RGBLedCube Cube = RGBLedCube();

// Enables safe voxel guard
#define SAFE_VOXEL_ON 1

#if SAFE_VOXEL_ON
// Checks if invalid index is trying to be accessed and stops the program if so
#define SAFE_VOXEL_GUARD(index) \
    if (index >= LED_COUNT)     \
        while (1)               \
            ;
#else
#define SAFE_VOXEL_GUARD(index)
#endif

// Set 'SERPENTINE_LAYOUT' to true if leds are like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//                         |
//     9 <  8 <  7 <  6 <  5
//     |
//     |
//    10 > 11 > 12 > 13 > 14
//
// Set 'SERPENTINE_LAYOUT' to false if leds are like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//     .----<----<----<----'
//     |
//     5 >  6 >  7 >  8 >  9
//                         |
//     .----<----<----<----'
//     |
//    10 > 11 > 12 > 13 > 14
//
/**
 Wired like this:
   +----<---+
  /        /|
 /        / |
+--->----+  ^
|        |  |
|        |  +
^        v /
|        |/
+--------+
 */
#define SERPENTINE_LAYOUT true

/*---------------------------------------------------------------------------------------
 * CUBE CLASS - 3D RGB LED Cube
 *-------------------------------------------------------------------------------------*/

RGBLedCube::RGBLedCube()
{
}

void RGBLedCube::setVoxel(Point p, CRGB col)
{
    setVoxel(p.x, p.y, p.z, col);
}

void RGBLedCube::setVoxel(uint8_t x, uint8_t y, uint8_t z, CRGB col)
{
    // SAFE_VOXEL_GUARD(x, y, z);
    // index = getIndex(x, y, z);
    // leds[index] = col;
    setVoxel(getIndex(x, y, z), col);
}

void RGBLedCube::setVoxel(uint16_t index, CRGB col)
{
    SAFE_VOXEL_GUARD(index)
    // index = getIndex(getPoint(index));
    leds[index] = col;
}

CRGB RGBLedCube::getVoxel(Point p)
{
    return getVoxel(p.x, p.y, p.z);
}

CRGB RGBLedCube::getVoxel(uint8_t x, uint8_t y, uint8_t z)
{
    return getVoxel(getIndex(x, y, z));
}

CRGB RGBLedCube::getVoxel(uint16_t index)
{
    SAFE_VOXEL_GUARD(index)
    return CRGB(leds[index].r, leds[index].g, leds[index].b);
}

void RGBLedCube::fadeVoxel(Point p, uint8_t scale)
{
    fadeVoxel(p.x, p.y, p.z, scale);
}

void RGBLedCube::fadeVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t scale)
{
    fadeVoxel(getIndex(x, y, z), scale);
}

void RGBLedCube::fadeVoxel(uint16_t index, uint8_t scale)
{
    SAFE_VOXEL_GUARD(index)
    leds[index].nscale8(255 - scale);
}

void RGBLedCube::fadeAll(uint8_t scale) // scale / 256 * color
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        fadeVoxel(i, scale);
}

void RGBLedCube::fill(CRGB col)
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        setVoxel(i, col);
}

void RGBLedCube::clear()
{
    fill(CRGB::Black);
}

void RGBLedCube::line(int x1, int y1, int z1, int x2, int y2, int z2, CRGB col)
{
    Point currentPoint = Point(x1, y1, z1);

    int dx = x2 - x1;
    int dy = y2 - y1;
    int dz = z2 - z1;
    int x_inc = (dx < 0) ? -1 : 1;
    int l = abs(dx);
    int y_inc = (dy < 0) ? -1 : 1;
    int m = abs(dy);
    int z_inc = (dz < 0) ? -1 : 1;
    int n = abs(dz);
    int dx2 = l << 1;
    int dy2 = m << 1;
    int dz2 = n << 1;

    if ((l >= m) && (l >= n))
    {
        int err_1 = dy2 - l;
        int err_2 = dz2 - l;

        for (int i = 0; i < l; i++)
        {
            setVoxel(currentPoint, col);

            if (err_1 > 0)
            {
                currentPoint.y += y_inc;
                err_1 -= dx2;
            }

            if (err_2 > 0)
            {
                currentPoint.z += z_inc;
                err_2 -= dx2;
            }

            err_1 += dy2;
            err_2 += dz2;
            currentPoint.x += x_inc;
        }
    }
    else if ((m >= l) && (m >= n))
    {
        int err_1 = dx2 - m;
        int err_2 = dz2 - m;

        for (int i = 0; i < m; i++)
        {
            setVoxel(currentPoint, col);

            if (err_1 > 0)
            {
                currentPoint.x += x_inc;
                err_1 -= dy2;
            }

            if (err_2 > 0)
            {
                currentPoint.z += z_inc;
                err_2 -= dy2;
            }

            err_1 += dx2;
            err_2 += dz2;
            currentPoint.y += y_inc;
        }
    }
    else
    {
        int err_1 = dy2 - n;
        int err_2 = dx2 - n;

        for (int i = 0; i < n; i++)
        {
            setVoxel(currentPoint, col);

            if (err_1 > 0)
            {
                currentPoint.y += y_inc;
                err_1 -= dz2;
            }

            if (err_2 > 0)
            {
                currentPoint.x += x_inc;
                err_2 -= dz2;
            }

            err_1 += dy2;
            err_2 += dx2;
            currentPoint.z += z_inc;
        }
    }

    setVoxel(currentPoint, col);
}

void RGBLedCube::line(Point p1, Point p2, CRGB col)
{
    line(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, col);
}

void RGBLedCube::sphere(int x, int y, int z, int r, CRGB col)
{
    for (int dx = -r; dx <= r; dx++)
    {
        for (int dy = -r; dy <= r; dy++)
        {
            for (int dz = -r; dz <= r; dz++)
            {
                if (sqrt(dx * dx + dy * dy + dz * dz) <= r)
                {
                    setVoxel(x + dx, y + dy, z + dz, col);
                }
            }
        }
    }
}

void RGBLedCube::sphere(Point p, int r, CRGB col)
{
    sphere(p.x, p.y, p.z, r, col);
}

void RGBLedCube::shell(float x, float y, float z, float r, CRGB col)
{
    float thickness = 0.1;
    for (int i = 0; i < CUBE_SIZE; i++)
        for (int j = 0; j < CUBE_SIZE; j++)
            for (int k = 0; k < CUBE_SIZE; k++)
                if (abs(sqrt((i - x, 2) + pow(j - y, 2) + pow(k - z, 2)) - r) < thickness)
                    setVoxel(i, j, k, col);
}

void RGBLedCube::shell(Point p, float r, CRGB col)
{
    shell(p.x, p.y, p.z, r, col);
}

void RGBLedCube::shell(float x, float y, float z, float r, float thickness, CRGB col)
{
    for (int i = 0; i < CUBE_SIZE; i++)
        for (int j = 0; j < CUBE_SIZE; j++)
            for (int k = 0; k < CUBE_SIZE; k++)
                if (abs(sqrt(pow(i - x, 2) + pow(j - y, 2) + pow(k - z, 2)) - r) < thickness)
                    setVoxel(i, j, k, col);
}

void RGBLedCube::shell(Point p, float r, float thickness, CRGB col)
{
    shell(p.x, p.y, p.z, r, thickness, col);
}

/*--------------------------- PRIVATE FUNCTIONS --------------------------*/
uint16_t RGBLedCube::getIndex(Point p)
{
    return getIndex(p.x, p.y, p.z);
}

// uint16_t getIndex(uint8_t x, uint8_t y, uint8_t z)
// {
// Only works for 9x9x9 cubes
//     uint16_t index = 0;
//     uint8_t zone = (((x / 3) * 3) + (y / 3));
//     uint8_t branchX = x % 3;
//     uint8_t branchY = y % 3;

//     if ((branchX + branchY) % 2) // x + y is an odd number - flip z
//     {
//         if (branchX % 2) // x is an odd number - flip front y column to back and vice versa and also flip z
//         {
//             index = (branchX * 27) + ((3 - branchY - 1) * 9) + (9 - z - 1);
//         }
//         else // x is an even number - just flip z
//         {
//             index = (branchX * 27) + (branchY * 9) + (9 - z - 1);
//         }
//     }
//     else // x + y is an even number - don't flip z
//     {
//         index = (branchX * 27) + (branchY * 9) + z;
//     }

//     return (index += (zone * 81));
// }

uint16_t RGBLedCube::getIndex(uint8_t x, uint8_t y, uint8_t z)
{
#if SERPENTINE_LAYOUT
    if (x & 0x01 && y & 0x01) // if x and y are both odd or even then run z backwards
    {
        z = (CUBE_SIZE - 1) - z; // reverse z
    }

    if (y & 0x01) // if y is odd then run x backwards
    {
        x = (CUBE_SIZE - 1) - x; // reverse x
    }
#endif

    return (y * CUBE_SIZE * CUBE_SIZE) + (x * CUBE_SIZE) + z;
}

Point RGBLedCube::getPoint(uint16_t index)
{
    uint8_t z = index / (CUBE_SIZE * CUBE_SIZE);              // get layer
    uint8_t layerIndex = index - (z * CUBE_SIZE * CUBE_SIZE); // get 2D index of layer
    uint8_t x = layerIndex / CUBE_SIZE;                       // get y on layer
    uint8_t y = layerIndex % CUBE_SIZE;                       // get x on layer

    return Point(x, y, z);
}
