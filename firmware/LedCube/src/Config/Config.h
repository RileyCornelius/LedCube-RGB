#pragma once

// Cube size
#define CUBE_SIZE 9
#define CUBE_SIZE_M1 (CUBE_SIZE - 1)
#define CUBE_CENTER (CUBE_SIZE_M1 / 2)

// Led type
#define LED_COUNT (CUBE_SIZE * CUBE_SIZE * CUBE_SIZE)
#define LED_TYPE PL9823
#define LED_COLOR_ORDER RGB
#define LED_BRIGHTNESS 255
#define LED_BRANCH_COUNT (LED_COUNT / CUBE_SIZE)

// Display UART
#define DISPLAY_ENABLE 1
#define SerialDisplay Serial1