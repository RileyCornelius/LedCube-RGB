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
    RUN_TEST(test_function_true);
    RUN_TEST(test_function_false);
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
