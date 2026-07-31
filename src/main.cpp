#include <Arduino.h>

#include <display.h>
#include <config.h>

timer_t timer;

void setup() {
  Serial.begin(115200);

	pinMode(BTN_ONE, INPUT_PULLUP);
	pinMode(BTN_TWO, INPUT_PULLUP);
	pinMode(BUZZER_PIN, OUTPUT);
	pinMode(POT_PIN, INPUT);
	pinMode(13, OUTPUT);

	// tone(BUZZER_PIN, 1000);



  delay(500); // Wait for display
	if (!display_init()) {
		Serial.println("[ERROR] Display failed to initialise!");
		digitalWrite(13, HIGH);
		while (true) {
		}
	}

	timer.seconds = 30;
	timer.minutes = 5;
	
	// display_home_screen();
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
}