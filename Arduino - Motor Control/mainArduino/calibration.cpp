/*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is th header for the calibration functions
 */

/* ----------------------
 * Included Files
   ---------------------*/ 
#include "header.h"

/* ----------------------
 * Definitions
   ----------------------*/

  
int calibrate(Motor activeMotor){
  // this function drives the motors to the minimum and maximum position of the rail (determined with analog pins)
  // it returns the max number of steps the x and y motors can take before reaching the end
  int numSteps = 0; //number of steps taken between the beginning and the end
  //reverse until the start is hit, at which point this pin will read LOW
  while (digitalRead(activeMotor.min_pin)== HIGH){
    Serial.println("Calibrate first step");
    activateMode('2',activeMotor);//reverse mode 
  }

  //forward until the end is hit
  while (digitalRead(activeMotor.max_pin)== HIGH){
    Serial.println("Calibrate second step");
    activateMode('1',activeMotor);//forward mode
    numSteps +=1;
  }
  return numSteps;
}
