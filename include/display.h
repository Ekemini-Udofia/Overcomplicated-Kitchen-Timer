#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <config.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


bool display_init() {
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR)) {
		return false;
  }

  // Show initial display buffer contents on the screen (Adafuit Logo)
  // display.display();
  // delay(2000);

  // Clear the buffer
  // display.clearDisplay();

  // // Set for params for text display
  // display.setTextSize(4);
  // display.setTextColor(SSD1306_WHITE);
  // display.setCursor(2, 4);
  // display.cp437(true);  // Use full 256 char 'Code Page 437' font

  // display.write("Test");

	return true;
}

// void display_home_screen() {
// 	// Set home screen with various options
// 	display.clearDisplay();

// 	display.drawRect(1, 1, 126, 62, 1);

// 	display.setTextColor(1);
// 	display.setTextWrap(false);
// 	display.setCursor(20, 19);
// 	display.print("Overcomplicated");
// 	display.setCursor(26, 37);
// 	display.print("Kitchen Timer");
// 	display.display();
// 	delay(2000);
// }

void display_timer() {
	// Display the options for starting the timer. Remember that the potentiometer is controls the time knob 
}

void start_timer_with_display(timer_t time) {
	char buffer[6];

	buffer[2] = ':';
	buffer[5] = '\0';

	while (time.seconds > 0 || time.minutes > 0) {		
		display.clearDisplay();

		// Draw Static UI Elements
    display.drawRect(1, 1, 126, 62, 1);
    display.setTextSize(1);
    display.setCursor(22, 7);
    display.print("Stop");
    display.setCursor(57, 36);
    display.print("time left");
    display.setCursor(8, 48);
    display.print("Restart");
    display.drawCircle(12, 10, 4, 1);
		
		// The actual time 
		buffer[0] = (time.minutes / 10) + '0';
		buffer[1] = (time.minutes % 10) + '0';

		buffer[3] = (time.seconds / 10) + '0';
		buffer[4] = (time.seconds % 10) + '0';

		display.setTextColor(1);
    display.setTextSize(2);
    display.setTextWrap(false);
    display.setCursor(54, 16);
    display.print(buffer);
    display.display();
		
		delay(1000);

		if (time.seconds == 0 && time.minutes > 0) {
			time.seconds = 60;
			--time.minutes;
		}		

		if (time.seconds == 0 && time.minutes == 0) break;

		--time.seconds;
	}

	display.clearDisplay();
	display.drawRect(1, 1, 126, 62, 1);
	display.setTextSize(1);
	display.setCursor(22, 7);
	display.print("Stop");
	display.setCursor(57, 36);
	display.print("time left");
	display.setCursor(8, 48);
	display.print("Restart");
	display.drawCircle(12, 10, 4, 1);
	
	// Final Hardcoded "00:00"
	display.setTextColor(1);
	display.setTextSize(2);
	display.setTextWrap(false);
	display.setCursor(54, 16);
	display.print("00:00");
	display.display();
}

