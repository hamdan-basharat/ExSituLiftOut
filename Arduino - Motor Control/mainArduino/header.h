/*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is the header file showing all used definitions, prototypes to be implemented, and structs for all .cpp files
 */
 
#include <stdint.h> 
#include <SoftwareSerial.h> //serial communication
#include <Arduino.h> //basic arduino packages

//extern SoftwareSerial Serial;

/* ----------------------
 * Definitions
   ----------------------*/
//Declare pin functions on Arduino
#define stp_x 2
#define dir_x 3
#define EN_x  7

#define stp_y 8
#define dir_y 9
#define EN_y  10

#define MS1 4
#define MS2 5
#define MS3 6

//Also declared as an attribute of the specific motors
#define x_min_lim A0
#define x_max_lim A1
#define y_min_lim A2
#define y_max_lim A3

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


/* ----------------------
 * Prototypes
   ---------------------*/ 

//general.cpp
char toLower(char c);
serialStr getTokens(String userInput);

//dualMotor.cpp
void moveMotor(Motor activeMotor, int numSteps, int dir, char step_type);
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
int calibrate(Motor activeMotor);
