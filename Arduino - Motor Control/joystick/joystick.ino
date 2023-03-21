#define xStick A0
#define yStick A1
#define pushButton 13


void setup() {
  pinMode(pushButton, INPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int X = analogRead(xStick);
  int Y = analogRead(yStick);
  int pushed = digitalRead(pushButton);
  Serial.println("X value: " + String(X)  + "Y value: " + String(Y) + "Pushed down " + String(pushed));
  delay (10);
  
}
