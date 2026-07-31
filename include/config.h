#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino.h>

// Display definitions
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128

#define OLED_RESET -1
#define SCREEN_ADDR 0x3C

// Other Components
#define POT_PIN A6
#define BUZZER_PIN 2
#define BTN_ONE A0
#define BTN_TWO A1

typedef struct {
	uint8_t minutes;
	uint8_t seconds;
} timer_t;

typedef enum {
	timer_on,
	timer_off,
} state_t;

#endif // _CONFIG_H_

