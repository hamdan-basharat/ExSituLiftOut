String InBytes;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()>0){
  InBytes = Serial.readStringUntil('\n');
  if(InBytes){
    Serial.print(InBytes);
  }
  /*if(InBytes == "on"){
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.write("LED on");
  }
  else if(InBytes == "off"){
    digitalWrite(LED_BUILTIN,LOW);
    Serial.write("LED off");
  }
  else{
    Serial.write("Invalid input");
  }*/
}
}
