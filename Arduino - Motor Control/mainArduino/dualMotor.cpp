/*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is the header for the motor control
 */

#include "header.h"

/* --------------------------------------------
 * Functions go here
  --------------------------------------------*/ 
//TODO new read function that doesnt take a single char, and separates based on some delimiter

//my helper functions
char toLower(char c) {
  //input: c is any char
  //output: the same character converted to a lowercase letter
  if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
  return c;
}

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
       StepForwardDefault(activeMotor.stp,activeMotor.dir);
       return;
    }
    else if(choice =='2')
    { 
      Serial.println("Going reverse.");
      ReverseStepDefault(activeMotor.stp,activeMotor.dir);
      return;
    }
    else if(choice =='3')
    {
      Serial.println("Small steps Forward.");
      SmallStepMode(activeMotor.stp,activeMotor.dir);
      return;
    }
    else if(choice =='4')
    {
      Serial.println("Small steps backward.");
      SmallStepModeRev(activeMotor.stp,activeMotor.dir);
      return;
    }
    else if(choice =='5')
    {
      Serial.println("Forward then backward.");
      ForwardBackwardStep(activeMotor.stp,activeMotor.dir);
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
void StepForwardDefault(int stp, int dir)
{
  //Serial.println("Moving forward at default step mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for (int x = 0; x < 1000; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
//  Serial.println("Enter new option");
//  Serial.println();
}

//Reverse default microstep mode function
void ReverseStepDefault(int stp, int dir)
{
  //Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  for (int x = 0; x < 1000; x++) //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp, HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
//  Serial.println("Enter new option");
//  Serial.println();
}

// 1/16th microstep foward mode function
void SmallStepMode(int stp, int dir)
{
  //Serial.println("Stepping at 1/16th microstep mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  digitalWrite(MS1, HIGH); //Pull MS1,MS2, and MS3 high to set logic to 1/16th microstep resolution
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
  for (int x = 0; x < 1000; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
//  Serial.println("Enter new option");
//  Serial.println();
}

// 1/16th microstep backward mode function - we added this one
void SmallStepModeRev(int stp, int dir)
{
  //Serial.println("Stepping at 1/16th microstep mode backwards.");
  digitalWrite(dir, HIGH); //Pull direction pin high to move "reverse"
  digitalWrite(MS1, HIGH); //Pull MS1,MS2, and MS3 high to set logic to 1/16th microstep resolution
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
  for (int x = 0; x < 1000; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
//  Serial.println("Enter new option");
//  Serial.println();
}

//Forward/reverse stepping function
void ForwardBackwardStep(int stp, int dir)
{
  //Serial.println("Alternate between stepping forward and reverse.");
  for (int x = 1; x < 5; x++) //Loop the forward stepping enough times for motion to be visible
  {
    //Read direction pin state and change it
    int state = digitalRead(dir);
    if (state == HIGH)
    {
      digitalWrite(dir, LOW);
    }
    else if (state == LOW)
    {
      digitalWrite(dir, HIGH);
    }

    for (int y = 0; y < 1000; y++)
    {
      digitalWrite(stp, HIGH); //Trigger one step
      delay(1);
      digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
      delay(1);
    }
  }
//  Serial.println("Enter new option");
//  Serial.println();
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
