unsigned long timeForLedOn;
unsigned long timeForLedOff;
bool isOn = false;
int rLed = 2;


void setup() {
  // put your setup code here, to run once:
 pinMode(rLed,OUTPUT);
 Serial.begin(9600);
 timeForLedOn=millis();
timeForLedOff=millis();

}

void loop() {
  // put your main code here, to run repeatedly:
 if(!isOn && millis()-timeForLedOn>500){
  digitalWrite(rLed, HIGH);
  isOn = true;
  timeForLedOff=millis();
 }
 if(isOn && millis()-timeForLedOff>1500){
  digitalWrite(rLed, LOW);

  isOn = false;
  timeForLedOn=millis();
 }
}
