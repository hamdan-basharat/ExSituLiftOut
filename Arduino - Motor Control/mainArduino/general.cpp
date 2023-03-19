/*
 * Tony Fan 200003466
 * Ex-situ-Liftout
 * McMaster University - Capstone Group
 * This is the source file for general functions not explicitly for calibration or the motors
 */

/* ----------------------
 * Included Files
   ---------------------*/ 
#include "header.h"

/* ----------------------
 * Definitions
   ----------------------*/

char toLower(char c) {
  //input: c is any char
  //output: the same character converted to a lowercase letter
  //converts the provided character to lower case
  if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
  return c;
}

serialStr getTokens(String userInput){
  //assumed delimiter is "," and that the userInput has at least 5 tokens to match. This function takes the user input and separates them accordingly
  //input: the user inputted string, it should be delimited by commas and of the format (x_steps, direction, y_steps, direction, step type)
  //output a serialStr struct where all the individual components are separated into attributes
  
  char* token; //token will hold all the matched tokens of components
  int str_len = userInput.length() + 1; //length
  char userInputArray[str_len];//add 1 for null termination character of string
  serialStr tempStruct;//this is the returned structure
  
  userInput.toCharArray(userInputArray, str_len); //convert to char array and store in local array
  token = strtok(userInputArray,","); //get all tokens

  int index = 0;
  while (token != NULL) { //go through all tokens collected
    //Serial.println(token); //print current token
    switch(index){
      case 0: //store x_stp
        tempStruct.x_stp = atoi(token);//convert from ascii to integer to store this number
        break;  
        
      case 1: //store x_dir
        if (token[0] == 'f'){ //token is only one character so grab the first index
          tempStruct.x_dir = 0;//convert from ascii to integer to store this number
        } else {tempStruct.x_dir = 1;} //received reverse
        break;
        
      case 2: //store y_stp
        tempStruct.y_stp = atoi(token);//convert from ascii to integer to store this number
        break;
        
      case 3: //store y_dir
        if (token[0] == 'f'){ //token is only one character so grab the first index
          tempStruct.y_dir = 0;//convert from ascii to integer to store this number
        } else {tempStruct.y_dir = 1;}
        break;
        
      case 4: //store the type of step
        tempStruct.step_type = token[0];
        break;
    } //end switch
    
    index++; //move to next token
    token=strtok(NULL, ",");//remove current token
      
   }//end while
   return tempStruct;
}



  
