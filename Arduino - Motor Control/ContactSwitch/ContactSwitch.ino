void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(13, INPUT);
}

void loop() {
  if(13 == HIGH){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }
}
