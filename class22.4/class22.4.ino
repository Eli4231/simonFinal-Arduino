void setup() {
  Serial.begin(9600);            
  randomSeed(analogRead(A1));     
}

void loop() {
  int num = random(1, 101);    
  Serial.println(num);           
  delay(1000);                   
}
