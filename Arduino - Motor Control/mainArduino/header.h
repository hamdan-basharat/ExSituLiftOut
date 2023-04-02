/*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is the header file showing all used definitions, prototypes to be implemented, and structs for all .cpp files
 */
 
#include <stdint.h> 
#include <SoftwareSerial.h> //serial communication
#include <Arduino.h> //basic arduino packages
#include <Adafruit_MCP23X17.h>


/* ----------------------
 * Definitions
   ----------------------*/
//Declare pin functions on Arduino
#define stp_x 9
#define dir_x 8
#define EN_x  12

#define stp_y 3
#define dir_y 2
#define EN_y  4

#define MS1 11
#define MS2 10
//#define MS3 10

////essentially a look up table to all the pins on the MCP23017 I/O extender. See ADAFRUIT git for Pin Name to Pin ID. not all are used
//#define GPA0 0 //e.g GPA0 is represented as 0 in the ADA fruit library
//#define GPA1 1
//#define GPA2 2
//#define GPA3 3
//#define GPA4 4
//#define GPA5 5
//#define GPA6 6
//#define GPA7 7
//
//#define GPB0 8
//#define GPB1 9
//#define GPB2 10
//#define GPB3 11
//#define GPB4 12
//#define GPB5 13
//#define GPB6 14
//#define GPB7 15

//Also declared as an attribute of the specific motors, renamed for clarity and modularity
#define x_min_lim A4
#define x_max_lim A5
#define y_min_lim A6
#define y_max_lim A7

//define joystick pins
#define xStick A1
#define yStick A2
#define js_but A0 //joystick pushdown button

// MANIPULATOR USES PINS 4,3,2
#define manip_EN 7
#define manip_stp 6
#define manip_dir 5

//structure to hold the motor attributes
typedef struct Motor {
  char id; //the id of the motor, x or y
  int stp_pin; //the pin number in which to decide to step
  int dir_pin; //the pin number for direction
  int EN; // the pin number to enable this motor
  uint8_t min_pin;
  uint8_t max_pin;
  int max_step; //the maximum number of steps possible for this motor, the minimum is assumed 0
} Motor;

typedef struct serialStr{
  int x_stp; //number of steps to take in the x direction
  int x_dir; //forward or reverse. 0 is LOW/forward, and 1 is HIGH/reverse
  int y_stp; // number of steps in y direction
  int y_dir; //forward or reverse.  0 is LOW/forward, and 1 is HIGH/reverse
  char step_type; //do whole steps or micro steps
} serialStr;

typedef struct Joystick{
  int pressed; //whether the joystick has been pressed down
  int X; //the x position of the joystick
  int Y; //the y position of the joystick
} Joystick;

/* ----------------------
 * Prototypes
   ---------------------*/ 

//general.cpp
char toLower(char c); //converts given character to lower case
serialStr getTokens(String userInput); //converts string with comma delimited values into multiple strings

//dualMotor.cpp
void moveMotor(Motor activeMotor, int numSteps, int dir, char step_type); //moves a single motor 
void resetBEDPins();

//these functions are only for testing
Motor chooseMotor (char choice, Motor motor_x, Motor motor_y);
int printModes();
void activateMode(int choice, Motor activeMotor);
void StepForwardDefault(int stp_pin, int dir_pin);
void ReverseStepDefault(int stp_pin, int dir_pin);
void SmallStepMode(int stp_pin, int dir_pin);
void SmallStepModeRev(int stp_pin, int dir_pin);

//calibration.cpp
int calibrate(Motor activeMotor,Adafruit_MCP23X17 mcp);

//manualMode.cpp
//note: this isthe joystick manual mode
Joystick getJS();
void jsMove(Joystick js, Motor motor_x, Motor motor_y,char step_type); //moves the XY motors with the joystick
void jsMove(Joystick js, Motor manip,char step_type); //overloaded function for only the micro manipulator motor
int changeMode(Joystick js,Joystick old_js); //chooses what the mode is and returns it
