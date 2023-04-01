String arr[4];
String x_steps, x_dir, y_steps, y_dir, step_size;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  while (Serial.available() > 0) {
   
    x_steps = Serial.readStringUntil(','); // writes in the string all the inputs till a comma
    Serial.read(); 
    x_dir = Serial.readStringUntil(',');
    Serial.read(); 
    y_steps = Serial.readStringUntil(',');
    Serial.read(); 
    y_dir = Serial.readStringUntil(',');
    Serial.read(); 
    step_size = Serial.readStringUntil('\n'); // writes in the string all the inputs till the end of line character

    Serial.print(x_steps + x_dir + y_steps + y_dir + step_size);
  }
}
