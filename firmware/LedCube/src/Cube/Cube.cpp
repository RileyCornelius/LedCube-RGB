
#if defined(ESP32)
#if ESP_ARDUINO_VERSION_MAJOR <= 2
// * IMPORTANT: This built on esp-idf 4.x. This existed prior to Arduino Core 3.0.0. you MUST downgrade to Arduino Core < 3.0.0
// Changes data transfer from RMT to I2S which can handle up to 24 parallel branches
#define FASTLED_ESP32_I2S true                      // This must be defined before including FastLED.h
#define FASTLED_ESP32_I2S_NUM_DMA_BUFFERS CUBE_SIZE // Number of DMA buffers equal to cube size
#else
#pragma message "ESP32 Arduino Core version >= 3.0.0 detected. Please use Arduino Core < 3.0.0 for FastLED I2S support."
#endif // ESP_ARDUINO_VERSION_MAJOR <= 2
#endif // defined(ESP32)

#include <FastLED.h>

#include "Cube/Cube.h"
#include "Bitmaps/ibm_vga.h"
#include "Bitmaps/ibm_cga_light.h"

LedCube Cube = LedCube();

// Enables safe voxel guard
#define SAFE_VOXEL_ON 1

#if SAFE_VOXEL_ON
// Checks if invalid index is trying to be accessed and stops the program if so
#define SAFE_VOXEL_GUARD(index)                    \
    if (index >= LED_COUNT)                        \
    {                                              \
        Cube.clear();                              \
        Cube.sphere(Point(4, 4, 4), 3, CRGB::Red); \
        FastLED.show();                            \
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

void LedCube::setLed(const Point &p, const CRGB &col)
{
    setLed(p.x, p.y, p.z, col);
}

void LedCube::setLed(int8_t x, int8_t y, int8_t z, const CRGB &col)
{
    setLed(getIndex(x, y, z), col);
}

void LedCube::setLed(uint16_t index, const CRGB &col)
{
    // SAFE_VOXEL_GUARD(index)
    if (index >= LED_COUNT)
        return;
    leds[index] = col;
}

CRGB LedCube::getLed(const Point &p)
{
    return getLed(p.x, p.y, p.z);
}

CRGB LedCube::getLed(int8_t x, int8_t y, int8_t z)
{
    return getLed(getIndex(x, y, z));
}

CRGB LedCube::getLed(uint16_t index)
{
    SAFE_VOXEL_GUARD(index)
    return leds[index];
}

void LedCube::fadeLed(const Point &p, int8_t scale)
{
    fadeLed(p.x, p.y, p.z, scale);
}

void LedCube::fadeLed(int8_t x, int8_t y, int8_t z, int8_t scale)
{
    fadeLed(getIndex(x, y, z), scale);
}

void LedCube::fadeLed(uint16_t index, int8_t scale)
{
    // SAFE_VOXEL_GUARD(index)
    if (index >= LED_COUNT)
        return;
    leds[index].fadeToBlackBy(scale);
}

void LedCube::fadeAll(int8_t scale) // scale / 256 * color
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        fadeLed(i, scale);
}

void LedCube::fill(const CRGB &col)
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        setLed(i, col);
}

void LedCube::clear()
{
    fill(CRGB::Black);
}

void LedCube::line(int x1, int y1, int z1, int x2, int y2, int z2, const CRGB &col)
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
            setLed(currentPoint, col);

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
            setLed(currentPoint, col);

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
            setLed(currentPoint, col);

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

    setLed(currentPoint, col);
}

void LedCube::line(const Point &p1, const Point &p2, const CRGB &col)
{
    line(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, col);
}

void LedCube::triangle(const Point &p1, const Point &p2, const Point &p3, const CRGB &col)
{
    line(p1, p2, col);
    line(p2, p3, col);
    line(p3, p1, col);
}

void LedCube::square(const Point &p1, const Point &p2, const Point &p3, const Point &p4, const CRGB &col)
{
    line(p1, p2, col);
    line(p2, p3, col);
    line(p3, p4, col);
    line(p4, p1, col);
}

void LedCube::cube(const Point &p1, const Point &p2, const CRGB &col)
{
    for (int8_t x = p1.x; x <= p2.x; x++)
        for (int8_t y = p1.y; y <= p2.y; y++)
            for (int8_t z = p1.z; z <= p2.z; z++)
            {
                setLed(x, y, z, col);
            }
}

void LedCube::box(const Point &p1, const Point &p2, const CRGB &col)
{
    line(p1.x, p1.y, p1.z, p2.x, p1.y, p1.z, col);
    line(p1.x, p1.y, p1.z, p1.x, p2.y, p1.z, col);
    line(p2.x, p1.y, p1.z, p2.x, p2.y, p1.z, col);
    line(p1.x, p2.y, p1.z, p2.x, p2.y, p1.z, col);

    line(p1.x, p1.y, p2.z, p2.x, p1.y, p2.z, col);
    line(p1.x, p1.y, p2.z, p1.x, p2.y, p2.z, col);
    line(p2.x, p1.y, p2.z, p2.x, p2.y, p2.z, col);
    line(p1.x, p2.y, p2.z, p2.x, p2.y, p2.z, col);

    line(p1.x, p1.y, p1.z, p1.x, p1.y, p2.z, col);
    line(p1.x, p2.y, p1.z, p1.x, p2.y, p2.z, col);
    line(p2.x, p1.y, p1.z, p2.x, p1.y, p2.z, col);
    line(p2.x, p2.y, p1.z, p2.x, p2.y, p2.z, col);
}

void LedCube::radiate(int x, int y, int z, float r, const CRGB &col, uint8_t power /* = 3 */)
{
    for (int dx = -r; dx <= r; dx++)
        for (int dy = -r; dy <= r; dy++)
            for (int dz = -r; dz <= r; dz++)
            {
                float mag = sqrtf(dx * dx + dy * dy + dz * dz);
                if (mag <= r)
                {
                    CRGB fadedColor = col.scale8(255 / (1 + pow(mag, power)));
                    setLed(x + dx, y + dy, z + dz, fadedColor);
                }
            }
}

void LedCube::radiate(const Point &p, float r, const CRGB &col, uint8_t power /* = 3 */)
{
    radiate(p.x, p.y, p.z, r, col, power);
}

void LedCube::sphere(int x, int y, int z, int r, const CRGB &col, bool radiate /* = false */)
{
    for (int dx = -r; dx <= r; dx++)
        for (int dy = -r; dy <= r; dy++)
            for (int dz = -r; dz <= r; dz++)
            {
                float mag = sqrtf(dx * dx + dy * dy + dz * dz);
                if (mag <= r)
                {
                    if (radiate)
                        setLed(x + dx, y + dy, z + dz, col.scale8(255 - (mag / r * 255)));
                    else
                        setLed(x + dx, y + dy, z + dz, col);
                }
            }
}

void LedCube::sphere(const Point &p, int r, const CRGB &col, bool radiate /* = false */)
{
    sphere(p.x, p.y, p.z, r, col, radiate);
}

void LedCube::shell(float x, float y, float z, float r, const CRGB &col, float thickness /* = 0.1 */)
{
    for (int i = 0; i < CUBE_SIZE; i++)
        for (int j = 0; j < CUBE_SIZE; j++)
            for (int k = 0; k < CUBE_SIZE; k++)
                if (abs(sqrt(pow(i - x, 2) + pow(j - y, 2) + pow(k - z, 2)) - r) < thickness)
                {
                    setLed(i, j, k, col);
                }
}

void LedCube::shell(const Point &p, float r, const CRGB &col, float thickness /* = 0.1 */)
{
    shell(p.x, p.y, p.z, r, col, thickness);
}

void LedCube::ascii(char ascii, int8_t y, const CRGB &color)
{
    static_assert(CUBE_SIZE > 8, "CUBE_SIZE must be 8 or larger");

    int8_t offset = CUBE_SIZE - 8;
    const char *bitmap = ibm_vga[ascii];
    bool set;

    for (int8_t z = 0; z < 8; z++)
        for (int8_t x = 0; x < 8; x++)
        {
            set = bitmap[z] & 1 << x;
            setLed(8 - x - offset, y, 8 - z - offset, set ? color : CRGB::Black);
        }
}

void LedCube::asciiThin(char ascii, int8_t y, const CRGB &color)
{
    static_assert(CUBE_SIZE > 8, "CUBE_SIZE must be 8 or larger");

    const char *bitmap = ibm_cga_light[ascii];
    bool set;

    for (int8_t z = 1; z < 9; z++)
        for (int8_t x = 1; x < 9; x++)
        {
            set = bitmap[z - 1] & 1 << 8 - x - 1;
            setLed(8 - x, y, 8 - z, set ? color : CRGB::Black);
        }
}

/*--------------------------- PRIVATE FUNCTIONS --------------------------*/

uint16_t LedCube::getIndex(const Point &p)
{
    return getIndex(p.x, p.y, p.z);
}

uint16_t LedCube::getIndex(int8_t x, int8_t y, int8_t z)
{
    if (x < 0 || x >= CUBE_SIZE || y < 0 || y >= CUBE_SIZE || z < 0 || z >= CUBE_SIZE)
        return LED_COUNT + 1; // invalid index

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
    int8_t z = index / (CUBE_SIZE * CUBE_SIZE);              // get layer
    int8_t layerIndex = index - (z * CUBE_SIZE * CUBE_SIZE); // get 2D index of layer
    int8_t x = layerIndex / CUBE_SIZE;                       // get y on layer
    int8_t y = layerIndex % CUBE_SIZE;                       // get x on layer

    return Point(x, y, z);
}
