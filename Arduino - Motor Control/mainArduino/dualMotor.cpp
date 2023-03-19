/*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is the header for the motor control functions
 */

#include "header.h"

/* --------------------------------------------
 * Functions go here
  --------------------------------------------*/ 
void moveMotor(Motor activeMotor, int numSteps, int dir, char step_type){
  //inputs: activeMotor is the motor object we want to move
  //        numstep is the number of steps to take
  //        dir is the direction to move, 0 is LOW/forward, and 1 is HIGH/reverse
  //        steptype is a char describing if we're doing a whole step, or a micro step of 1/16th
  Serial.println("Moving " + String(activeMotor.id) + " " + String(numSteps) + "steps in the " + String(dir) + " direction using "+ String(step_type) + " steps");
  digitalWrite(activeMotor.dir_pin, dir); //Pull direction pin low to move "forward" or high to "reverse"

  if (step_type == 'm'){ //m for micro steps
    digitalWrite(MS1, HIGH); //Pull MS1,MS2, and MS3 high to set logic to 1/16th microstep resolution
    digitalWrite(MS2, HIGH);
    digitalWrite(MS3, HIGH);
  } else { //anything else for whole steps,but it'll usually be 'w' leave this open for future changes of different steps
    digitalWrite(MS1, LOW); //Pull MS1,MS2, and MS3 LOW to set logic to whole step resolution
    digitalWrite(MS2, LOW);
    digitalWrite(MS3, LOW);
  }
  
  for (int x = 0; x < numSteps; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(activeMotor.stp_pin, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(activeMotor.stp_pin, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

//Reset Easy Driver pins to default states
void resetBEDPins()
{
  digitalWrite(stp_x, LOW);
  digitalWrite(dir_x, LOW);
  digitalWrite(stp_y, LOW);
  digitalWrite(dir_y, LOW);

  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);

  digitalWrite(EN_x, HIGH);
  digitalWrite(EN_y, HIGH);
}

// ----------------------------------------------------------------------  //
// ---------- BELOW IS OUTDATED CODE, USED IN PREVIOUS TESTING ----------  //
// ----------------------------------------------------------------------  //

Motor chooseMotor (char choice, Motor motor_x, Motor motor_y){
  //input: some character which is a user defined letter
  //output: x or y depending on what was chosen
  //this function just dummy-proofs the choice to ensure the code doesn't proceed and break because of an invalid selection
    while(1){//always ask 
      switch (toLower(choice)) {
        case ('\n'):
          break;
    
        case ('x'):
          //Serial.println("got x.");
          return motor_x;
          break;
    
        case ('y'):
          //Serial.println("Got y.");
          return motor_y;
          break;
    
        default:
          Serial.println("Invalid option entered. Choose x or y for motor selection. ");
          while (Serial.available()== 0) {};//blocking statement, basically just wait until something is available to read from serial
          choice = Serial.read(); //Read user input and trigger appropriate function
          break;
      }
  }//end while true loop
}

int printModes(){
  //All print statements to choose what mode for the motor
  Serial.println();
  Serial.println("Enter number for control option:");
  Serial.println("1. Turn at default microstep mode.");
  Serial.println("2. Reverse direction at default microstep mode.");
  Serial.println("3. Turn at 1/16th microstep mode forward.");
  Serial.println("4. Turn at 1/16th microstep mode reverse.");
  Serial.println("5. Step forward and reverse directions.");
  Serial.println();
}

//TODO add parameter to include number of steps
void activateMode(int choice, Motor activeMotor){
  //input:  a choice as an integer 
  //        a Motor to move
  //        the number of steps to move        
  //output: no return value, but moves the motor based on the choice
  //1: move forward
  //2: move reverse
  //3: micro step forward
  //4: micro step backward
  //5: forwadr and then backward mode
  while(1){
    if (choice =='1')
    { 
       Serial.println("Going forward.");
       StepForwardDefault(activeMotor.stp_pin,activeMotor.dir_pin);
       return;
    }
    else if(choice =='2')
    { 
      Serial.println("Going reverse.");
      ReverseStepDefault(activeMotor.stp_pin,activeMotor.dir_pin);
      return;
    }
    else if(choice =='3')
    {
      Serial.println("Small steps Forward.");
      SmallStepMode(activeMotor.stp_pin,activeMotor.dir_pin);
      return;
    }
    else if(choice =='4')
    {
      Serial.println("Small steps backward.");
      SmallStepModeRev(activeMotor.stp_pin,activeMotor.dir_pin);
      return;
    }
    else
    {
      Serial.println("Invalid mode selected.");
      printModes();
      while (Serial.available()== 0) {};//blocking statement, basically just wait until something is available to read from serial
      choice = Serial.read(); //Read user input and trigger appropriate function
    }
  }
}
//Default microstep mode function
void StepForwardDefault(int stp_pin, int dir_pin)
{
  //Serial.println("Moving forward at default step mode.");
  digitalWrite(dir_pin, LOW); //Pull direction pin low to move "forward"
  for (int x = 0; x < 1000; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_pin, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_pin, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
//  Serial.println("Enter new option");
//  Serial.println();
}

//Reverse default microstep mode function
void ReverseStepDefault(int stp_pin, int dir_pin)
{
  //Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir_pin, HIGH); //Pull direction pin high to move in "reverse"
  for (int x = 0; x < 1000; x++) //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp_pin, HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp_pin, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
//  Serial.println("Enter new option");
//  Serial.println();
}

// 1/16th microstep foward mode function
void SmallStepMode(int stp_pin, int dir_pin)
{
  //Serial.println("Stepping at 1/16th microstep mode.");
  digitalWrite(dir_pin, LOW); //Pull direction pin low to move "forward"
  digitalWrite(MS1, HIGH); //Pull MS1,MS2, and MS3 high to set logic to 1/16th microstep resolution
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
  for (int x = 0; x < 1000; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_pin, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_pin, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
//  Serial.println("Enter new option");
//  Serial.println();
}

// 1/16th microstep backward mode function - we added this one
void SmallStepModeRev(int stp_pin, int dir_pin)
{
  //Serial.println("Stepping at 1/16th microstep mode backwards.");
  digitalWrite(dir_pin, HIGH); //Pull direction pin high to move "reverse"
  digitalWrite(MS1, HIGH); //Pull MS1,MS2, and MS3 high to set logic to 1/16th microstep resolution
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
  for (int x = 0; x < 1000; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_pin, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_pin, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
//  Serial.println("Enter new option");
//  Serial.println();
}
