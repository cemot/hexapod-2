
int pinPIRLeft = A13;
int pinPIRMid = A14;
int pinPIRRight = A15;
void setup() {
  Serial.begin(9600);
  
  pinMode(pinPIRLeft, INPUT);
  pinMode(pinPIRMid, INPUT);
  pinMode(pinPIRRight, INPUT);
  
}

void loop() {
   float outLeft = analogRead(pinPIRLeft); 
   float outMid = analogRead(pinPIRMid); 
   float outRight = analogRead(pinPIRRight);
   
   int human = map(outMid, 0, )
//   Serial.print("Left: "); Serial.println(outLeft);
   Serial.print("Mid: "); Serial.println(outMid);
//   Serial.print("Right: "); Serial.println(outRight);
   Serial.println("=============");
   delay(500);
}
