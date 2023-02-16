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

//structure to hold the motor attributes
typedef struct motor {
  char id; //the id of the motor, x or y
  int stp; //the pin number in which to decide to step
  int dir; //the pin number for direction
  int EN; // the pin number to enable this motor
} Motor;

//Declare variables for functions
int x; //default loop variable used in motor function
int y; //default loop variable used in motor function
int state;

//motor datatypes initialized into struct for easier passing between functions
Motor motor_x = {.id = 'x', .stp = stp_x, .dir = dir_x, .EN = EN_x};
Motor motor_y = {.id = 'y', .stp = stp_y, .dir = dir_y, .EN = EN_y};

void setup() {
  pinMode(stp_x, OUTPUT);
  pinMode(stp_y, OUTPUT);

  pinMode(dir_x, OUTPUT);
  pinMode(dir_y, OUTPUT);

  pinMode(EN_x, OUTPUT);
  pinMode(EN_y, OUTPUT);

  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  resetBEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control program");
  Serial.println();
  //Print function list for user selection
  Serial.println("Enter letter (x or y) for motor selection:");
  Serial.println();
}


//Main loop
void loop() {
  char user_input; // the input from serial.read whenever it's called
  Motor activeMotor; //the current motor we want to target
  int mode; //the function we want to call for the motor's movement
  digitalWrite(EN_x, LOW); //Pull enable pin low to set FETs active and allow motor control
  digitalWrite(EN_y, LOW);

  //choose which motor to use
  while (Serial.available()== 0) {};//blocking statement, basically just wait until something is available to read from serial
  user_input = Serial.read(); //Read user input and trigger appropriate function
  activeMotor = chooseMotor(user_input);

  //TODO this read loops back if an invalid value is given rather than just continuing
  printModes();
  while (Serial.available()== 0) {};//blocking statement, basically just wait until something is available to read from serial
  user_input = Serial.read(); //Read user input and trigger appropriate function
  activateMode(user_input,activeMotor);
    
  
  resetBEDPins();
}//end main loop

//my helper functions
char toLower(char c) {
  //input: c is any char
  //output: the same character converted to a lowercase letter
  if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
  return c;
}

Motor chooseMotor (char choice){
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
  Serial.println("3. Turn at 1/16th microstep mode.");
  Serial.println("4. Step forward and reverse directions.");
  Serial.println();
}

void activateMode(int choice, Motor activeMotor){
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
      Serial.println("Small steps.");
      SmallStepMode(activeMotor.stp,activeMotor.dir);
      return;
    }
    else if(choice =='4')
    {
      Serial.println("Forward then backward.");
      ForwardBackwardStep(activeMotor.stp,activeMotor.dir);
      return;
    }
    else
    {
      Serial.println("Invalid option entered.");
      printModes();
      while (Serial.available()== 0) {};//blocking statement, basically just wait until something is available to read from serial
      choice = Serial.read(); //Read user input and trigger appropriate function
    }
  }
}
//Default microstep mode function
void StepForwardDefault(int stp, int dir)
{
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for (x = 0; x < 1000; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}

//Reverse default microstep mode function
void ReverseStepDefault(int stp, int dir)
{
  Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  for (x = 0; x < 1000; x++) //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp, HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}

// 1/16th microstep foward mode function
void SmallStepMode(int stp, int dir)
{
  Serial.println("Stepping at 1/16th microstep mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  digitalWrite(MS1, HIGH); //Pull MS1,MS2, and MS3 high to set logic to 1/16th microstep resolution
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
  for (x = 0; x < 1000; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}

//Forward/reverse stepping function
void ForwardBackwardStep(int stp, int dir)
{
  Serial.println("Alternate between stepping forward and reverse.");
  for (x = 1; x < 5; x++) //Loop the forward stepping enough times for motion to be visible
  {
    //Read direction pin state and change it
    state = digitalRead(dir);
    if (state == HIGH)
    {
      digitalWrite(dir, LOW);
    }
    else if (state == LOW)
    {
      digitalWrite(dir, HIGH);
    }

    for (y = 0; y < 1000; y++)
    {
      digitalWrite(stp, HIGH); //Trigger one step
      delay(1);
      digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
      delay(1);
    }
  }
  Serial.println("Enter new option");
  Serial.println();
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
