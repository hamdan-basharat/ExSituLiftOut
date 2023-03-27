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

Motor manip = {
  .id = 'z', 
  .stp_pin = manip_stp, 
  .dir_pin = manip_dir, 
  .EN = manip_EN, 
  .min_pin = 0, //non existant for this one
  .max_pin = 0
};


Adafruit_MCP23X17 mcp; // mcp unit object for extended I/O

Joystick js; // joystick data declared for global use
/* --------------------------------------------
 * Setup and Main functions begin here
  --------------------------------------------*/ 
void setup() {
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Starting Ex-situ liftout.");
  
  //begin I2C for IO extender, assumed address is at 0x20 because the three address pins should be set LOW
  if (!mcp.begin_I2C()) {
    Serial.println("Error in I2C connection.");
    //while (1); //UNCOMMENT
  }
  
  //set all digital pins for XY stepper motors
  pinMode(stp_x, OUTPUT);
  pinMode(stp_y, OUTPUT);

  pinMode(dir_x, OUTPUT);
  pinMode(dir_y, OUTPUT);

  pinMode(EN_x, OUTPUT);
  pinMode(EN_y, OUTPUT);

  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  //set the IO extended pins for motor limiters to pulled high
  mcp.pinMode(x_min_lim, INPUT_PULLUP); 
  mcp.pinMode(x_max_lim, INPUT_PULLUP);
  mcp.pinMode(y_min_lim, INPUT_PULLUP);
  mcp.pinMode(y_max_lim, INPUT_PULLUP);

  //pin for the push button on the joystick
  pinMode(js_but, INPUT_PULLUP);

  resetBEDPins(); //Set step, direction, microstep and enable pins to default states
  
  //-------------- Calibrate -------------- //
  digitalWrite(EN_x, LOW); //Pull enable pin low to set FETs active and allow motor control
  digitalWrite(EN_y, LOW);

  //UNCOMMENT THESE 
  //motor_x.max_step = calibrate(motor_x,mcp);
  //motor_y.max_step = calibrate(motor_y,mcp);

  //----- Manual mode until joystick is hit -----//
  while (digitalRead(js_but)==1){ //button input is pulled high so keep looping until it is pressed (LOW)
    js = getJS();
    jsMove(js, motor_x, motor_y);
//    Serial.println("in joystick mode");
  }

  Serial.println("Begin serial motor control program");
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
  
  while (Serial.available()== 0) { //blocking statement, basically just wait until something is available to read from serial
    //check if joystick is hit, this will control the micro manipulator
    js = getJS(); //get joystick position
    jsMove(js, manip);  //move manipulator according to the joystick
  }
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
