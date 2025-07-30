#include <DIYables_4Digit7Segment_74HC595.h>
#define   START_GAME 100
#define   GAME 101
#define   END_GAME 102
int stateGame;
int rLed = 2, yLed = 3, gLed = 4, bLed = 12;
int rBtn = 8, yBtn = 9, gBtn = 10, bBtn = 11;
int sum = 0;
const int ledPins[4] = { rLed, yLed, gLed, bLed };
const int buttonPins[4] = { rBtn, yBtn, gBtn, bBtn };
const int buzPin = 10;
int clk = 5, ltc = 6, dta = 7;
DIYables_4Digit7Segment_74HC595 display(clk, ltc, dta);
int currentColor = -1;
unsigned long lastChangeTime = 0;
unsigned long interval = 1000;
const unsigned long minInterval = 500;
bool gameOver = false;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  display.clear();
  Serial.begin(9600);
  randomSeed(analogRead(A1));
}

void loop() {

switch(stateGame){
  case START_GAME:
  
for(int i = 0; i < 4; i++){
  digitalWrite(ledPins[i], == HIGH );
  digitalWrite(ledPins[i], == LOW);
  if(buttonPins[i] == LOW){
    stateGame=101;
  }
  break;

  case GAME:
 display.loop();
  display.printInt(sum, false);
  if (gameOver) return;

  unsigned long currentTime = millis();

  if (currentTime - lastChangeTime >= interval) {
    if (currentColor != -1) {
      digitalWrite(ledPins[currentColor], LOW);
    }

    currentColor = random(4);
    digitalWrite(ledPins[currentColor], HIGH);
    lastChangeTime = currentTime;
  }

  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      if (i == currentColor) {
        sum += 1;

        Serial.print("YES +1 point  Total: ");
        Serial.println(sum);

        if (interval > minInterval) {
          interval -= 50;
        }
      } else {
        if (sum > 0) {
          sum -= 1;
        }


        Serial.print("WRONG -1 point  Total: ");
        Serial.println(sum);
      }


      delay(300);
    }
  }
  break

  case END_GAME:
 for(int i =0 ;i<4;i++){
  digitalWrite(ledPins[i] == LOW);

 }
  break;

  
}

 
}
