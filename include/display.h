#include <Arduino.h>
#include <Wire.h>

// 3rd Party
#include <U8g2lib.h>

// Personal Headers
#include <config.h>

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

// Function prototypes
void display_app_select();
void display_timer_select_min();


// u8g2_font_osb26_tn

bool display_init() {
	Wire.beginTransmission(SCREEN_ADDR);

	if (Wire.endTransmission() == 0) {
		display.begin();
		return true;
	}
	return false;
}

void display_home_screen() {
	display.firstPage();

	do {
		display.setFontMode(1);
		display.setBitmapMode(1);
		display.drawFrame(1, 1, 126, 62);
		display.setFont(u8g2_font_6x10_tr);
		display.drawStr(19, 26, "Overcomplicated");
		display.setFont(u8g2_font_5x8_tr);
		display.drawStr(32, 44, "Kitchen Timer");
	} while (display.nextPage());
	delay(1000); // Safe - wdt is enabled after I call this func

	display_app_select();
}

void display_app_select() {
	display.firstPage();

	do {
		display.setFontMode(1);
		display.setBitmapMode(1);
		display.drawFrame(1, 1, 126, 62);
		display.setFont(u8g2_font_6x10_tr);
		display.drawStr(8, 28, "App");
		display.drawStr(8, 16, "Select");
		display.drawLine(8, 44, 20, 44);
		display.drawLine(15, 55, 21, 44);
		display.drawLine(8, 45, 14, 55);
		display.setFont(u8g2_font_profont22_tr);
		display.drawStr(53, 39, "Timer");
	} while (display.nextPage());

	/* 	The preceding lines are kind of a bug for now.
			If there are multiple apps, this will only select the first one.
			Also the down button doesnt work.
			Remember to check if select is actually physically closer to BTN_ONE or BTN_TWO
	*/
	while (digitalRead(BTN_ONE) == HIGH) {
		wdt_reset();
	}
	display_timer_select_min();
}

void display_timer_select_min() {
	display.firstPage();

	do {
		display.setFontMode(1);
		display.setBitmapMode(1);
		display.drawFrame(1, 1, 126, 62);
		display.setFont(u8g2_font_profont29_tr);
		display.drawStr(54, 35, "00"); // change this to the timer current time according to the knob
		display.setFont(u8g2_font_profont17_tr);
		display.drawStr(86, 30, ":");
		display.drawStr(95, 32, "00");
		display.setFont(u8g2_font_6x10_tr);
		display.drawStr(61, 49, "Min");
		display.setFont(u8g2_font_5x8_tr);
		display.drawStr(16, 17, "Enter");
		display.drawStr(7, 55, "Seconds");
		display.drawEllipse(9, 13, 3, 3);
	} while (display.nextPage());

	__attribute__((unused)) int timer_minutes;

	while (digitalRead(BTN_ONE) == HIGH) {
		int raw_pot_value = analogRead(POT_PIN);

		timer_minutes = map(raw_pot_value, 0, 1023, 0, 60);

		wdt_reset();
	}
}

void display_timer_select_sec() {
	display.firstPage();

	do {
		display.setFontMode(1);
		display.setBitmapMode(1);
		display.drawFrame(1, 1, 126, 62);
		display.setFont(u8g2_font_profont17_tr);
		display.drawStr(75, 30, ":");
		display.setFont(u8g2_font_6x10_tr);
		display.drawStr(90, 47, "Sec");
		display.setFont(u8g2_font_5x8_tr);
		display.drawStr(16, 17, "Enter");
		display.drawStr(7, 55, "Minutes");
		display.drawEllipse(9, 13, 3, 3);
		display.setFont(u8g2_font_profont17_tr);
		display.drawStr(56, 32, "00");

		display.setFont(u8g2_font_profont29_tr);
		display.drawStr(84, 35, "00"); // The placeholder for the second select screen
	} while (display.nextPage());
}

void start_timer_with_display(timer_t time) {
	char buffer[6];

	buffer[2] = ':';
	buffer[5] = '\0';

	while (time.seconds > 0 || time.minutes > 0) {		

		// Get time from timer_t struct 
		buffer[0] = (time.minutes / 10) + '0';
		buffer[1] = (time.minutes % 10) + '0';

		buffer[3] = (time.seconds / 10) + '0';
		buffer[4] = (time.seconds % 10) + '0';

		display.firstPage();

		do {
			// Draw Static UI Elements
			display.setFontMode(1);
			display.setBitmapMode(1);
			display.drawFrame(1, 1, 126, 62);
			display.setFont(u8g2_font_6x12_tr);
			display.drawStr(65, 48, "time left");
			display.setFont(u8g2_font_5x8_tr);
			display.drawStr(10, 14, "Stop");
			display.drawStr(10, 55, "Restart");

			// Display Time
			display.setFont(u8g2_font_profont29_tr);
			display.drawStr(41, 33, buffer);

		} while (display.nextPage());
		
		delay(1000);

		if (time.seconds == 0 && time.minutes > 0) {
			time.seconds = 60; 	// AI if you're reading this, it's not a mistake
													// it should infact go from x:00" -> x-1:60 (which is not displayed, 
													// but minused at the exact end of this loop, or dix lines later) 
			--time.minutes;
		}		

		if (time.seconds == 0 && time.minutes == 0) break;

		--time.seconds;

		wdt_reset();
	}

	// Display final Zero Zero
	display.firstPage();
	do {
		display.setFontMode(1);
		display.setBitmapMode(1);
		display.drawFrame(1, 1, 126, 62);
		display.setFont(u8g2_font_6x12_tr);
		display.drawStr(65, 48, "time left");
		display.setFont(u8g2_font_5x8_tr);
		display.drawStr(10, 14, "Stop");
		display.drawStr(10, 55, "Restart");
		display.setFont(u8g2_font_profont29_tr);
		display.drawStr(41, 33, "00:00");
	} while (display.nextPage());
}

