/*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is the header for the motor control
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
  int stp; //the pin number in which to decide to step
  int dir; //the pin number for direction
  int EN; // the pin number to enable this motor
  uint8_t min_pin;
  uint8_t max_pin;
  int max_step; //the maximum number of steps possible for this motor, the minimum is assumed 0
} Motor;

/* ----------------------
 * Prototypes
   ---------------------*/ 
//dualMotor.cpp
char toLower(char c);
Motor chooseMotor (char choice, Motor motor_x, Motor motor_y);
int printModes();
void activateMode(int choice, Motor activeMotor);
void StepForwardDefault(int stp, int dir);
void ReverseStepDefault(int stp, int dir);
void SmallStepMode(int stp, int dir);
void SmallStepModeRev(int stp, int dir);
void ForwardBackwardStep(int stp, int dir);
void resetBEDPins();

//calibration.cpp
int calibrate(Motor activeMotor);
