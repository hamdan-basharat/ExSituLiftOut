/*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is the main arduino file for execution
 */

/* ----------------------
 * Included Files
   ---------------------*/ 
#include "header.h"

/* ----------------------
 * Definitions
   ----------------------*/
//the structures describing the components received in the serial read
serialStr x_str;
serialStr y_str;
   
//motor datatypes initialized into struct for easier passing between functions
Motor motor_x = {
  .id = 'x', 
  .stp_pin = stp_x, 
  .dir_pin = dir_x, 
  .EN = EN_x, 
  .min_pin = x_min_lim, //redundant but useful for passing as a parameter
  .max_pin = x_max_lim
  };

Motor motor_y = {
  .id = 'y', 
  .stp_pin = stp_y, 
  .dir_pin = dir_y, 
  .EN = EN_y, 
  .min_pin = y_min_lim, 
  .max_pin = y_max_lim
  };

/* --------------------------------------------
 * Setup and Main functions begin here
  --------------------------------------------*/ 
void setup() {
   //set all digital pins
  pinMode(stp_x, OUTPUT);
  pinMode(stp_y, OUTPUT);

  pinMode(dir_x, OUTPUT);
  pinMode(dir_y, OUTPUT);

  pinMode(EN_x, OUTPUT);
  pinMode(EN_y, OUTPUT);

  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  //set the analog pins for motor limiters
  pinMode(x_min_lim, INPUT_PULLUP);
  pinMode(x_max_lim, INPUT_PULLUP);
  pinMode(y_min_lim, INPUT_PULLUP);
  pinMode(y_max_lim, INPUT_PULLUP);

  resetBEDPins(); //Set step, direction, microstep and enable pins to default states
  //-------------- Calibrate -------------- //
  digitalWrite(EN_x, LOW); //Pull enable pin low to set FETs active and allow motor control
  digitalWrite(EN_y, LOW);
  //motor_x.max_step = calibrate(motor_x);
  //motor_y.max_step = calibrate(motor_y);
  
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control program");
  
}

//Main loop
void loop() {
  String user_input; // the input from serial.read whenever it's called
  Motor activeMotor; //the current motor we want to target
  int mode; //the function we want to call for the motor's movement
  serialStr commands;
  
  digitalWrite(EN_x, LOW); //Pull enable pin low to set FETs active and allow motor control
  digitalWrite(EN_y, LOW);

  //read the serial string
  Serial.println("Enter the serial string delimited by commas (x_steps, direction, y_steps, direction, step type)");
  
  while (Serial.available()== 0) {};//blocking statement, basically just wait until something is available to read from serial
  user_input = Serial.readString(); //Read user input and trigger appropriate function

  //grab serial string components
  commands = getTokens(user_input); //collect tokens and store them in local struct
//  Serial.println(commands.x_stp);
//  Serial.println(commands.x_dir);
//  Serial.println(commands.y_stp);
//  Serial.println(commands.y_dir);
//  Serial.println(commands.step_type);
  
  //move both motors sequentially with the struct arguments
  moveMotor(motor_x, commands.x_stp, commands.x_dir, commands.step_type);
  moveMotor(motor_y, commands.y_stp, commands.y_dir, commands.step_type);

//  

////  
//  
//  // -------------- choose which motor to use -------------- //
//  Serial.println("Enter letter (x or y) for motor selection:");
//  Serial.println();
//  while (Serial.available()== 0) {};//blocking statement, basically just wait until something is available to read from serial
//  user_input = Serial.read(); //Read user input and trigger appropriate function
//  activeMotor = chooseMotor(user_input,motor_x, motor_y);
//
//  // ---------- Choose which mode to move the motor (e.g, forward, reverse...) ------//
//  printModes(); //Print function list for user selection
//  while (Serial.available()== 0) {};//blocking statement, basically just wait until something is available to read from serial
//  user_input = Serial.read(); //Read user input and trigger appropriate function
//  activateMode(user_input,activeMotor);

  
  resetBEDPins(); //reset for next run

}//end main loop
