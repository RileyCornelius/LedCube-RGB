#include <unity.h>
#include <Arduino.h>

/*------------------------------------------------------------------------------
 * TESTS
 *----------------------------------------------------------------------------*/

void test_function_true(void)
{
    TEST_ASSERT_EQUAL(32, 32);
}

void test_function_false(void)
{
    TEST_ASSERT_EQUAL(20, 0);
}

void serpentine_layout(void)
{
#define CUBE_SIZE 3
    uint8_t x = 2, y = 1, z = 1;

    if (x & 0x01 ^ y & 0x01) // x and y are both odd or even
    {
        z = (CUBE_SIZE - 1) - z; // reverse z
    }

    if (y & 0x01) // y is odd
    {
        x = (CUBE_SIZE - 1) - x; // reverse x
    }

    uint16_t result = (y * CUBE_SIZE * CUBE_SIZE) + (x * CUBE_SIZE) + z;

    TEST_ASSERT_EQUAL(10, result);
}

/*------------------------------------------------------------------------------
 * SETUP
 *----------------------------------------------------------------------------*/

// set stuff up here
void setUp(void)
{
}

// clean stuff up here
void tearDown(void)
{
}

// tests here
void tests()
{
    RUN_TEST(serpentine_layout);
}

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    tests();
    UNITY_END();
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}
