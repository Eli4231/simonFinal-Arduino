const int ledsPins[4] = { 2, 3, 4, 12 };
const int ledsBtn[4] = { 5, 7, 8, 6 };
int numLeds = 4;
unsigned long pMillis = 0;
const unsigned long inter = 1500;
bool isPress = true;
bool isOn = true;

int currentLed = -1;
int lastLed = -1;
void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledsPins[i], OUTPUT);
    pinMode(ledsBtn[i], INPUT_PULLUP);
    digitalWrite(ledsPins[i], LOW);
  }
  randomSeed(analogRead(A1));
  Serial.begin(9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - pMillis >= inter) {
    pMillis = currentMillis;
    
  }

  for (int i = 0; i < numLeds; i++) {
  digitalWrite(ledsPins[i], LOW);
 
  }
    int r = random(0, numLeds - 1);
    if (r >= lastLed) {
      currentLed = r + 1;
    } else {
      currentLed = r;
    }

    digitalWrite(ledsPins[currentLed], HIGH);
    lastLed = currentLed;
    
    for (int i = 0; i < numLeds; i++) {
     if (digitalRead(ledsBtn[i]) == LOW  && digitalRead(ledsPins[currentLed] == HIGH)) {
    Serial.println("yes");
     }
    }

  }
  
