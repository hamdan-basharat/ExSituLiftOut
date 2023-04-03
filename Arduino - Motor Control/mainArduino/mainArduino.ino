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


int mode=0;//changes to choose what mode the joystick/motors operate in
//1:mode needs updating
//0: idle state
//1:move stage 
//2:
//3:

Adafruit_MCP23X17 mcp; // mcp unit object for extended I/O

// joystick data declared for global use

Joystick js; //initialize state of pressed to 1 for later use
Joystick prevJS;//the previous state of the joystick

/* --------------------------------------------
 * Setup and Main functions begin here
  --------------------------------------------*/ 
void setup() {
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Starting Ex-situ liftout.");
  
  //begin I2C for IO extender, assumed address is at 0x20 because the three address pins should be set LOW
//  if (!mcp.begin_I2C()) {
//    Serial.println("Error in I2C connection.");
//    //while (1); //UNCOMMENT
//  }

  //set all digital pins for XY stepper motors
  pinMode(stp_x, OUTPUT);
  pinMode(stp_y, OUTPUT);

  pinMode(dir_x, OUTPUT);
  pinMode(dir_y, OUTPUT);

  pinMode(EN_x, OUTPUT);
  pinMode(EN_y, OUTPUT);

  //Z motor
  pinMode(manip_EN, OUTPUT); 
  pinMode(manip_stp, OUTPUT); 
  pinMode(manip_dir, OUTPUT); 

  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  //pinMode(MS3, OUTPUT);

  //set the IO extended pins for motor limiters to pulled high
  mcp.pinMode(x_min_lim, INPUT_PULLUP); 
  mcp.pinMode(x_max_lim, INPUT_PULLUP);
  mcp.pinMode(y_min_lim, INPUT_PULLUP);
  mcp.pinMode(y_max_lim, INPUT_PULLUP);

  //pin for the push button on the joystick
  pinMode(js_but, INPUT_PULLUP);

  resetBEDPins(); //Set step, direction, microstep and enable pins to default states 
  
  js=getJS(); //initialize state of pressed to 1 for later use
  prevJS=getJS();//the previous state of the joystick
  Serial.println("Begin serial motor control program");
}

//Main loop
void loop() {
  String user_input; // the input from serial.read whenever it's called
  Motor activeMotor; //the current motor we want to target
  serialStr commands;
  
  digitalWrite(EN_x, LOW); //Pull enable pin low to set FETs active and allow motor control
  digitalWrite(EN_y, LOW);

  //read the serial string
  Serial.println("Enter the serial string delimited by commas (x_steps, direction, y_steps, direction, step type)");
  
  while (Serial.available()== 0) { //blocking statement, basically just wait until something is available to read from serial
    //update joystick objects
    prevJS = js; //the previous joystick value
    js = getJS(); //get current joystick position

    //when a button is released, toggle the mode to either control the micro manipulator or stage with joystick with micro steps or whole steps
    if ((prevJS.pressed==0) && (js.pressed==1) && mode!=-1){
      mode = -1;//indicate that mode needs updating
      prevJS.pressed=1;//reset previous push button so as not to trigger the next 
      Serial.println("waiting for mode to be selected"); 
    } 

    if (mode==-1){ //if button was pressed/released, make the joystick change the mode we're in on the next input
      //Serial.println("changemode"); 
      mode = changeMode(js,prevJS);
    } else{ //otherwise we want to make movements happen
      switch(mode){//activate mode 
        //IDLE STATE
        case(0):{ 
          Serial.println("IDLE");
          break;
        }
        
        //move the stage with whole steps (push up)
        case(1):{ 
          Serial.println("MODE1");
          jsMove(js, motor_x, motor_y,'w');
          break;
        }

        //move the manipulator with whole steps
        case(2):{
          Serial.println("MODE2");
          jsMove(js, manip,'w');
          break;
        }

        //move the stage with micro steps
        case(3):{
          Serial.println("MODE3");
          jsMove(js, motor_x, motor_y,'m');
          break;
        }

        //move the manipulator with micro steps (push down)
        case(4):{
          Serial.println("MODE4");
          jsMove(js, manip,'m');
          break;
        }

        //calibrate/center mode, activated by push button
        case(5):{
          Serial.println("MODE5");
          //UNCOMMENT THESE 
          //motor_x.max_step = calibrate(motor_x,mcp);
          //motor_y.max_step = calibrate(motor_y,mcp);
          mode=0;
          break;
        }

        
        default:{break;}
      }
    
    }
    
    //if (!mode){jsMove(js, manip,'m');}//move manipulator according to the joystick //Serial.println("XY MODE");
    //else{jsMove(js, motor_x, motor_y,'m');}//Serial.println("Z MODE");
    
  }
  user_input = Serial.readString(); //Read user input and trigger appropriate function

  //grab serial string components
  commands = getTokens(user_input); //collect tokens and store them in local struct
  
  //move both motors sequentially with the struct arguments
  moveMotor(motor_x, commands.x_stp, commands.x_dir, commands.step_type);
  moveMotor(motor_y, commands.y_stp, commands.y_dir, commands.step_type);
  
  resetBEDPins(); //reset for next run

}//end main loop
