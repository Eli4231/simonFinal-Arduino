#include <DIYables_4Digit7Segment_74HC595.h>

#define data_pin 7
#define latch_pin 6
#define clk_pin 5

DIYables_4Digit7Segment_74HC595 display(clk_pin, latch_pin, data_pin);

unsigned long timer = 0;
int num = 0;

void showNumber() {
  if (millis() - timer > 1000) {
    num++;
    display.printInt(num, false);
    timer = millis();
  }
}

void setup() {
}

void loop() {
  display.loop();
  showNumber();
}