#define blue 9
#define btn 4
bool ispass= false;
bool isledon= false;


void setup() {
  // put your setup code here, to run once:
pinMode(blue, OUTPUT);
pinMode(btn, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

if(digitalRead(btn)==LOW ){
  if(isledon){

digitalWrite(blue, LOW);

isledon=false;
  }
  else{
    digitalWrite(blue,HIGH);
    isledon=true;
  }
while(digitalRead(btn)==LOW ){
  delay(50);
}
}
}