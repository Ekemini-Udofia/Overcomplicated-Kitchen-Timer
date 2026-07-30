#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_HEIGHT 128
#define SCREEN_WIDTH 64

#define OLED_RESET -1
#define SCREEN_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  delay(500); // Wait for display

  if (!display.begin(SSD1306_SWITCHAPVCC, SCREEN_ADDR)) {
    Serial.println("[OLED] Display not Initialised!\n.");
    for (;;) Serial.print(".");
  }

  Serial.println("[OLED] Display Initialised Successfully!");

  // Show initial display buffer contents on the screen (Adafuit Logo)
  display.display();
  delay(2000);

  // Clear the buffer
  display.ClearDisplay();

  // Set for params for text display
  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 4);
  display.cp437(true);  // Use full 256 char 'Code Page 437' font

  display.write("Test");
}

void loop() {


}
