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

Joystick getJS(){
  //this function just returns the current state of the joystick
  //input: a joystick object 
  //output: an updated joystick object
  Joystick newJs;
  newJs.X = analogRead(xStick);
  newJs.Y = analogRead(yStick);
  newJs.pressed = digitalRead(js_but);

  //Serial.println("X value: " + String(newJs.X)  + "Y value: " + String(newJs.Y) + "Pushed down " + String(newJs.pressed));
  //delay (10);

  return newJs;
}

void jsMove(Joystick js, Motor motor_x, Motor motor_y, char step_type){
  //this function moves the motors depending on what the joystick's position is
  //input: the joystick data
  //1023 is teh maximum joystick analog value

  //TODO, JOYSTICK MOVE MICRO STEPS too INSTEAD OF WHOLE STEPS
  if (js.X < 250){
    moveMotor(motor_x, 1000, 0, step_type);//make the current motor take one step forwards as a whole step
  } else if (js.X > 750){
    moveMotor(motor_x, 1000, 1, step_type);//make the current motor take one step backwards as a whole step
  }

  if (js.Y < 250){
    moveMotor(motor_y, 1000, 0, step_type);//make the current motor take one step forwards as a whole step
  } else if (js.Y > 750){
    moveMotor(motor_y, 1000, 1, step_type);//make the current motor take one step backwards as a whole step
  }

}

void jsMove(Joystick js, Motor manip,char step_type){
  //this function moves a single motor forward or backward using only the Y coordinate
  //input: joystick and motor object
  
  //Serial.println("moving manip motor");//debugging
  if (js.Y < 250){
    moveMotor(manip, 1, 0, step_type);//make the current motor take one step forwards as a whole step
  } else if (js.Y > 750){
    moveMotor(manip, 1, 1, step_type);//make the current motor take one step backwards as a whole step
  }
}
