#pragma once

/**--------------------------------------------------------------------------------------
 * Config
 *-------------------------------------------------------------------------------------*/

#define CUBE_SIZE 9
#define CUBE_LENGTH (CUBE_SIZE - 1)
#define LED_COUNT (CUBE_SIZE * CUBE_SIZE * CUBE_SIZE)
#define LED_TYPE PL9823
#define LED_COLOR_ORDER RGB
#define LED_BRIGHTNESS 255
#define LED_BRANCH_COUNT (LED_COUNT / CUBE_SIZE)

// Display UART
#define DISPLAY_ENABLE 1
#define SerialDisplay Serial1

// Over the Air Update
#define OTA_ENABLE 1

/**--------------------------------------------------------------------------------------
 * Pins
 *-------------------------------------------------------------------------------------*/

// Led Pins (390 ohm resistor on each pin)
#define PIN_LED_0 22
#define PIN_LED_1 19
#define PIN_LED_2 23
#define PIN_LED_3 18
#define PIN_LED_4 32
#define PIN_LED_5 33
#define PIN_LED_6 25
#define PIN_LED_7 26
#define PIN_LED_8 27