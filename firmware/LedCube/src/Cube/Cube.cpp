#include "Cube.h"
#include "ota.h"
#include "Font8x8/ibm_vga.h"
#include "Font8x8/ibm_cga_light.h"

// Global cube helper object for Animation sub classes
LedCube Cube = LedCube();

// Enables safe voxel guard
#define SAFE_VOXEL_ON 1

#if SAFE_VOXEL_ON
// Checks if invalid index is trying to be accessed and stops the program if so
#define SAFE_VOXEL_GUARD(index) \
    if (index >= LED_COUNT)     \
    {                           \
        Cube.fill(CRGB::Red);   \
        FastLED.show();         \
        while (1)               \
        {                       \
            handleOta();        \
        }                       \
    }

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
#define SERPENTINE_LAYOUT true

/*---------------------------------------------------------------------------------------
 * CUBE CLASS - 3D RGB LED Cube
 *-------------------------------------------------------------------------------------*/

LedCube::LedCube()
{
}

void LedCube::setVoxel(Vector3 p, CRGB col)
{
    setVoxel(round(p.x), round(p.y), round(p.z), col);
}

void LedCube::setVoxel(Point p, CRGB col)
{
    setVoxel(p.x, p.y, p.z, col);
}

void LedCube::setVoxel(uint8_t x, uint8_t y, uint8_t z, CRGB col)
{
    setVoxel(getIndex(x, y, z), col);
}

void LedCube::setVoxel(uint16_t index, CRGB col)
{
    SAFE_VOXEL_GUARD(index)
    leds[index] = col;
}

CRGB LedCube::getVoxel(Point p)
{
    return getVoxel(p.x, p.y, p.z);
}

CRGB LedCube::getVoxel(uint8_t x, uint8_t y, uint8_t z)
{
    return getVoxel(getIndex(x, y, z));
}

CRGB LedCube::getVoxel(uint16_t index)
{
    SAFE_VOXEL_GUARD(index)
    return CRGB(leds[index].r, leds[index].g, leds[index].b);
}

void LedCube::fadeVoxel(Point p, uint8_t scale)
{
    fadeVoxel(p.x, p.y, p.z, scale);
}

void LedCube::fadeVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t scale)
{
    fadeVoxel(getIndex(x, y, z), scale);
}

void LedCube::fadeVoxel(uint16_t index, uint8_t scale)
{
    SAFE_VOXEL_GUARD(index)
    leds[index].nscale8(255 - scale);
}

void LedCube::fadeXLayer(uint8_t x, uint8_t scale)
{
    for (uint8_t y = 0; y < CUBE_SIZE; y++)
    {
        for (uint8_t z = 0; z < CUBE_SIZE; z++)
        {
            fadeVoxel(x, y, z, scale);
        }
    }
}

void LedCube::fadeYLayer(uint8_t y, uint8_t scale)
{
    for (uint8_t x = 0; x < CUBE_SIZE; x++)
    {
        for (uint8_t z = 0; z < CUBE_SIZE; z++)
        {
            fadeVoxel(x, y, z, scale);
        }
    }
}

void LedCube::fadeZLayer(uint8_t z, uint8_t scale)
{
    for (uint8_t x = 0; x < CUBE_SIZE; x++)
    {
        for (uint8_t y = 0; y < CUBE_SIZE; y++)
        {
            fadeVoxel(x, y, z, scale);
        }
    }
}

void LedCube::fadeAll(uint8_t scale) // scale / 256 * color
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        fadeVoxel(i, scale);
}

void LedCube::fill(CRGB col)
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        setVoxel(i, col);
}

void LedCube::clear()
{
    fill(CRGB::Black);
}

void LedCube::line(int x1, int y1, int z1, int x2, int y2, int z2, CRGB col)
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

void LedCube::line(Point p1, Point p2, CRGB col)
{
    line(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, col);
}

void LedCube::triangle(Point p1, Point p2, Point p3, CRGB col)
{
    line(p1, p2, col);
    line(p2, p3, col);
    line(p3, p1, col);
}

void LedCube::square(Point p1, Point p2, Point p3, Point p4, CRGB col)
{
    line(p1, p2, col);
    line(p2, p3, col);
    line(p3, p4, col);
    line(p4, p1, col);
}

void LedCube::sphere(int x, int y, int z, int r, CRGB col)
{
    for (int dx = -r; dx <= r; dx++)
    {
        for (int dy = -r; dy <= r; dy++)
        {
            for (int dz = -r; dz <= r; dz++)
            {
                if (sqrt(dx * dx + dy * dy + dz * dz) <= r)
                {
                    // if x, y, or z is out of bounds then skip
                    if (x + dx < 0 || x + dx >= CUBE_SIZE || y + dy < 0 || y + dy >= CUBE_SIZE || z + dz < 0 || z + dz >= CUBE_SIZE)
                        continue;
                    setVoxel(x + dx, y + dy, z + dz, col);
                }
            }
        }
    }
}

void LedCube::sphere(Point p, int r, CRGB col)
{
    sphere(p.x, p.y, p.z, r, col);
}

void LedCube::shell(float x, float y, float z, float r, CRGB col, float thickness /* = 0.1 */)
{
    for (int i = 0; i < CUBE_SIZE; i++)
        for (int j = 0; j < CUBE_SIZE; j++)
            for (int k = 0; k < CUBE_SIZE; k++)
                if (abs(sqrt(pow(i - x, 2) + pow(j - y, 2) + pow(k - z, 2)) - r) < thickness)
                    setVoxel(i, j, k, col);
}

void LedCube::shell(Point p, float r, CRGB col, float thickness /* = 0.1 */)
{
    shell(p.x, p.y, p.z, r, col, thickness);
}

void LedCube::ascii(char ascii, uint8_t y, CRGB color)
{
    static_assert(CUBE_SIZE > 8, "CUBE_SIZE must be 8 or larger");

    uint8_t offset = CUBE_SIZE - 8;
    const char *bitmap = ibm_vga[ascii];
    bool set;

    for (uint8_t z = 0; z < 8; z++)
    {
        for (uint8_t x = 0; x < 8; x++)
        {
            set = bitmap[z] & 1 << x;
            setVoxel(8 - x - offset, y, 8 - z - offset, set ? color : CRGB::Black);
        }
    }
}

void LedCube::asciiThin(char ascii, uint8_t y, CRGB color)
{
    static_assert(CUBE_SIZE > 8, "CUBE_SIZE must be 8 or larger");

    const char *bitmap = ibm_cga_light[ascii];
    bool set;

    for (uint8_t z = 1; z < 9; z++)
    {
        for (uint8_t x = 1; x < 9; x++)
        {
            set = bitmap[z - 1] & 1 << 8 - x - 1;
            setVoxel(8 - x, y, 8 - z, set ? color : CRGB::Black);
        }
    }
}

/*--------------------------- PRIVATE FUNCTIONS --------------------------*/

uint16_t LedCube::getIndex(Point p)
{
    return getIndex(p.x, p.y, p.z);
}

uint16_t LedCube::getIndex(uint8_t x, uint8_t y, uint8_t z)
{
#if SERPENTINE_LAYOUT
    if (x & 0x01) // if x is odd then run z backwards
    {
        z = (CUBE_SIZE - 1) - z; // reverse z
    }
#endif

    return (y * CUBE_SIZE * CUBE_SIZE) + (x * CUBE_SIZE) + z;
}

uint16_t LedCube::getIndex(uint16_t index)
{
#if SERPENTINE_LAYOUT
    if ((index / CUBE_SIZE) & 0x01) // if index is odd then run backwards
    {
        index += (CUBE_SIZE - 1) - (index % CUBE_SIZE) * 2;
    }
#endif

    return index;
}

Point LedCube::getPoint(uint16_t index)
{
    uint8_t z = index / (CUBE_SIZE * CUBE_SIZE);              // get layer
    uint8_t layerIndex = index - (z * CUBE_SIZE * CUBE_SIZE); // get 2D index of layer
    uint8_t x = layerIndex / CUBE_SIZE;                       // get y on layer
    uint8_t y = layerIndex % CUBE_SIZE;                       // get x on layer

    return Point(x, y, z);
}
