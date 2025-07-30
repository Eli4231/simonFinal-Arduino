const int greenLed = 2;
const int redLed = 3;
const int greenButton = 4;

int Count = 0;
int lastnumber=0;

int counter(int greenLed, boll isOn){
if (digitalRead(greenButton) == LOW) {
    delay(200); 

    Count++;
  return Count;
}

void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop(); {
  counter();
  
}