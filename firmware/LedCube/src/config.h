#define TEST_BOARD

// Cube Defines
// #define CUBE_SIZE
#define LED_COUNT (CUBE_SIZE * CUBE_SIZE * CUBE_SIZE)
#define LED_TYPE PL9823
#define LED_COLOR_ORDER RGB
#define LED_BRIGHTNESS 255
#define LED_PER_BRANCH_COUNT (LED_COUNT / CUBE_SIZE)

// Led Pins (150 ohm resistor on each pin)
#ifdef TEST_BOARD
#define CUBE_SIZE 2
#define PIN_LED_0 5
#define PIN_LED_1 18
#else
#define CUBE_SIZE 9
#define PIN_LED_0 22
#define PIN_LED_1 19
#define PIN_LED_2 23
#define PIN_LED_3 18
#define PIN_LED_4 32
#define PIN_LED_5 33
#define PIN_LED_6 25
#define PIN_LED_7 26
#define PIN_LED_8 27
#endif

// Button Pins
#define PIN_NEXT_BTN 4
#define PIN_PREV_BTN 35
#define PIN_PAUSE_BTN 21

// Display UART
#define SerialDisplay Serial1