 /*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is the source file for manual remote control mode
 */
/* ----------------------
 * Included Files
   ---------------------*/ 
#include "header.h"

/* ----------------------
 * Definitions
   ----------------------*/

Joystick getJS(Joystick js){
  //this function just returns the current state of the joystick
  //input: a joystick object 
  //output: an updated joystick object
  Joystick newJs;
  newJs.X = analogRead(xStick);
  newJs.Y = analogRead(yStick);
  newJs.pressed = digitalRead(js_but);

  Serial.println("X value: " + String(js.X)  + "Y value: " + String(js.Y) + "Pushed down " + String(js.pressed));
  delay (10);

  return js;
}
