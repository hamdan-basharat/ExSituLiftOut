/*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is the source file for the calibration functions
 */

/* ----------------------
 * Included Files
   ---------------------*/ 
#include "header.h"

/* ----------------------
 * Definitions
   ----------------------*/
int calibrate(Motor activeMotor, Adafruit_MCP23X17 mcp){
  // this function drives the motors to the minimum and maximum position of the rail (determined with analog pins)
  // mcp is the IO extender object
  // it returns the max number of steps the x and y motors can take before reaching the end
  int numSteps = 0; //number of steps taken between the beginning and the end

  Serial.println("Calibrate first step");
  //reverse until the start is hit, at which point this pin will read LOW
  while (mcp.digitalRead(activeMotor.min_pin)== HIGH){
    moveMotor(activeMotor, 1, 0, 'w');//make the current motor take one step forwards as a whole step
  }

  Serial.println("Calibrate second step");
  //forward until the end is hit
  while (mcp.digitalRead(activeMotor.max_pin)== HIGH){
    moveMotor(activeMotor, 1, 1, 'w');//make the current motor take one step reverse as a whole step
    numSteps +=1;
  }

  Serial.println("Returning to center");
  moveMotor(activeMotor, numSteps, 0, 'w');//make the current motor return to center
  
  return numSteps;
}
