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
    moveMotor(motor_x, 30, 0, step_type);//make the current motor take one step forwards as a whole step
  } else if (js.X > 750){
    moveMotor(motor_x, 30, 1, step_type);//make the current motor take one step backwards as a whole step
  }

  if (js.Y < 250){
    moveMotor(motor_y, 30, 0, step_type);//make the current motor take one step forwards as a whole step
  } else if (js.Y > 750){
    moveMotor(motor_y, 30, 1, step_type);//make the current motor take one step backwards as a whole step
  }

}

void jsMove(Joystick js, Motor manip,char step_type){
  //this function moves a single motor forward or backward using only the Y coordinate
  //input: joystick and motor object
  
  //Serial.println("moving manip motor");//debugging
  if (js.Y < 250){
    moveMotor(manip, 100, 0, step_type);//make the current motor take one step forwards as a whole step
  } else if (js.Y > 750){
    moveMotor(manip, 100, 1, step_type);//make the current motor take one step backwards as a whole step
  }
}

int changeMode(Joystick js, Joystick prevJS){
  //this function is repeated and returns a mode depending on what is activated
  int mode=-1;//initialize to -1 for now, this is repeatedly called to avoid blocking
  if (js.X < 250){ //up
    mode =1;
    Serial.println(mode); 
  } else if (js.X > 750){ //down
    mode=3;
    Serial.println(mode); 
  }

  if (js.Y > 750){ //left
    mode=4;
    Serial.println(mode); 
  } else if (js.Y < 250){ //right
    mode=2;
    Serial.println(mode); 
  }

  if ((prevJS.pressed==0) && (js.pressed==1)){mode=5;}
  return mode;
  
}
