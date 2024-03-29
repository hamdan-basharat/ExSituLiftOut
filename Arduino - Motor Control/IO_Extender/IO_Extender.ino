// Blinks an LED attached to a MCP23XXX pin.

// ok to include only the one needed
// both included here to make things simple for example
#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>

#define LED_PIN 7     // MCP23XXX pin LED is attached to, GPA7
#define INPUT_PIN 8     // MCP23XXX pin LED is attached to, GPB0

// only used for SPI
#define CS_PIN 6

// uncomment appropriate line
//Adafruit_MCP23X08 mcp;
Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("MCP23xxx Blink Test!");

  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C()) {
  //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1);
  }

  // configure pin for output
  mcp.pinMode(LED_PIN, OUTPUT);
  mcp.pinMode(INPUT_PIN, INPUT_PULLUP);

  Serial.println("Looping...");
}

void loop() {
  

  if (mcp.digitalRead(INPUT_PIN)) { //if the pin is high, hold the LED high
     mcp.digitalWrite(LED_PIN,HIGH);
  } else { // otherwise blink the LED
     mcp.digitalWrite(LED_PIN, HIGH);
    delay(500);
    mcp.digitalWrite(LED_PIN, LOW);
    delay(500);
  }
}
