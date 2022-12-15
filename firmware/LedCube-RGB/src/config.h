// Cube Defines
#define CUBE_SIZE 2
#define LED_COUNT (CUBE_SIZE * CUBE_SIZE * CUBE_SIZE)
#define LED_TYPE PL9823
#define LED_COLOR_ORDER RGB

// Branches
#define BRANCHES 2
#define LED_BRANCH_COUNT (LED_COUNT / BRANCHES)

// Led Pins
#define LED_PIN 5
#define LED_1_PIN 17

// Button Pins
#define NEXT_BTN_PIN 18
#define PREV_BTN_PIN 19
#define PAUSE_BTN_PIN 21

// Debug
#define DEBUG
#ifdef DEBUG
#define PRINTLN(x) Serial.println(x)
#define PRINT(x) Serial.print(x)
#else
#define PRINTLN(x)
#define PRINT(x)
#endif