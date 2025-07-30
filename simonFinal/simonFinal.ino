//אלימלך לאנג
// ת.ז:308132448

#include <DIYables_4Digit7Segment_74HC595.h>

#define IDLE 0
#define SHOW 1
#define PLAY 2
#define RESET 3

const int rLed = 2, yLed = 3, gLed = 4, bLed = 12;
const int rBtn = 8, yBtn = 9, gBtn = 10, bBtn = 11;
const int ledPins[4] = { rLed, yLed, gLed, bLed };
const int buttonPins[4] = { rBtn, yBtn, gBtn, bBtn };

int clk = 5, ltc = 6, dta = 7;
DIYables_4Digit7Segment_74HC595 display(clk, ltc, dta);

int gameState = IDLE;
int sequence[20];
int level = 1;
int userIndex = 0;
unsigned long showDelay = 700;
const unsigned long minDelay = 200;

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
  display.loop();
  display.printInt(level - 1, false);

  switch (gameState) {
    case IDLE:
      IdleState();
      break;
    case SHOW:
      ShowSequence();
      break;
    case PLAY:
      PlaySequence();
      break;
    case RESET:
      ResetState();
      break;
  }
}

void IdleState() {
  idleAnimation();
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      resetGameState();
      gameState = SHOW;
      break;
    }
  }
}

void resetGameState() {
  level = 1;
  userIndex = 0;
  showDelay = 700;
  for (int i = 0; i < 20; i++) {
    sequence[i] = random(4);
  }
  display.clear();
}

void ShowSequence() {
  for (int i = 0; i < 4; i++) digitalWrite(ledPins[i], LOW);
  delay(200);
  for (int i = 0; i < level; i++) {
    int led = sequence[i];
    digitalWrite(ledPins[led], HIGH);
    delay(showDelay);
    digitalWrite(ledPins[led], LOW);
    delay(showDelay / 2);
  }
  userIndex = 0;
  gameState = PLAY;
}

void PlaySequence() {
  int input = getUserInput();
  if (input != -1) {
    if (input == sequence[userIndex]) {
      flashLed(input);
      userIndex++;
      if (userIndex == level) {
        delay(500);
        level++;
        if (level > 20) level = 20;
        if (showDelay > minDelay && level % 5 == 0) {
          showDelay -= 100;
        }
        gameState = SHOW;
      }
    } else {
      gameState = RESET;
    }
  }
}

void ResetState() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  display.printInt(0, false);
  delay(1000);
  gameState = IDLE;
}

void idleAnimation() {
  static unsigned long last = 0;
  static int currentLed = -1;
  if (millis() - last > 300) {
    if (currentLed != -1) {
      digitalWrite(ledPins[currentLed], LOW);
    }
    currentLed = random(4);
    digitalWrite(ledPins[currentLed], HIGH);
    last = millis();
  }
}

int getUserInput() {
  static bool released = true;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW && released) {
      released = false;
      delay(150);
      return i;
    }
  }
  bool allReleased = true;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      allReleased = false;
    }
  }
  if (allReleased) released = true;
  return -1;
}

void flashLed(int index) {
  for (int i = 0; i < 4; i++) digitalWrite(ledPins[i], LOW);
  digitalWrite(ledPins[index], HIGH);
  delay(200);
  digitalWrite(ledPins[index], LOW);
}
