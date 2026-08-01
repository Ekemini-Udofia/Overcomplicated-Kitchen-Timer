#include <Arduino.h>
#include <avr/wdt.h>

#include <display.h>
#include <config.h>

timer_t timer;

void setup() {
  Serial.begin(115200);
	Wire.begin();

	pinMode(BTN_ONE, INPUT_PULLUP);
	pinMode(BTN_TWO, INPUT_PULLUP);
	pinMode(BUZZER_PIN, OUTPUT);
	pinMode(POT_PIN, INPUT);

	Serial.println("[SYS] Initialization started");

  delay(500); // Wait for display
	if (!display_init()) {
		Serial.println("[ERROR] Display failed to initialise!");
		while (true) {
		}
	}

	Serial.println("[SYS] Display initialised successfully");

	timer.seconds = 30;
	timer.minutes = 5;
	
	display_home_screen();
	wdt_enable(WDTO_2S);
}

void loop() {
	start_timer_with_display(timer);
	// delay(1000);
	if (!digitalRead(BTN_ONE)) {
		noTone(BUZZER_PIN);
	}

	if (!digitalRead(BTN_TWO)) {
		tone(BUZZER_PIN, 5000);
	}
	wdt_reset();
}