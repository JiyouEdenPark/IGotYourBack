#include <Arduino.h>
#include "ServoEasing.hpp"

//pin setup 
const int switchPin = 2;     // switch(buckle) pin
const int servoPin_x = 3;    // servo pin for robot arm motor x 
const int servoPin_y = 5;    // servo pin for robot arm motor y
const int servoPin_z = 9;    // servo pin for robot arm motor z
const int stateFlagPin = 15;    // servo pin for state flag motor    

//initiator switch state
bool switchState = false;

//states of the unit -- initialized to waiting stte
bool state_chair_waiting = true; // chair has string to print and waiting for user == vacant 
bool state_chair_printing = false; // chair is printing
bool state_monitor = false; // user is guessing / leaving input for the next person 

//string to print 
String print_string = "HELLO"; // initialized to "HELLO"

// Servo objects
ServoEasing servo_x_axis;
ServoEasing servo_y_axis;
ServoEasing servo_z_axis;
ServoEasing servo_flag; // servo for state flag

// Servo initial speed
int general_speed = 38;
int flag_speed = 50;

// Predefined commands for letters
float letter_A_commands[][3] = {
  {150, 70, 140},{112.5, 57.5, 120},{95, 40, 80},{77.5, 57.5, 115},{45, 70, 140},{45, 90, 140},{112.5, 57.5, 120},{77.5, 57.5, 115},{77.5, 77.5, 115}
};
float letter_B_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{150, 70, 140},{150, 90, 140},{115, 35, 70},{95, 40, 80},{81.3, 50, 100},{95, 60, 120},{125, 55, 110},{95, 60, 120},{72.5, 63.8, 130},{95, 70, 150},{150, 70, 140},{150, 90, 140}
};
float letter_C_commands[][3] = {
  {70, 47.5, 95},{95, 40, 80},{120, 47.5, 95},{135, 62.5, 125},{95, 70, 150},{60, 62.5, 125},{60, 82.5, 125}
};
float letter_D_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{150, 70, 140},{150, 90, 140},{115, 35, 70},{95, 40, 80},{81.3, 50, 100},{72.5, 63.8, 130},{95, 70, 150},{150, 70, 140},{150, 90, 140}
};
float letter_E_commands[][3] = {
  {115, 35, 70},{95, 40, 80},{75, 35, 70},{75, 55, 70},{125, 55, 110},{95, 60, 120},{65, 55, 110},{65, 75, 110},{115, 35, 70},{125, 55, 110},{150, 70, 140},{95, 70, 150},{45, 70, 140},{45, 90, 140}
};
float letter_F_commands[][3] = {
  {75, 35, 70},{95, 40, 80},{115, 35, 70},{125, 55, 110},{150, 70, 140},{150, 90, 140},{125, 55, 110},{95, 60, 120},{65, 55, 110},{65, 75, 110}
};
float letter_G_commands[][3] = {
  {85, 37.5, 75},{105, 37.5, 75},{120, 47.5, 95},{135, 62.5, 125},{130, 70, 145},{60, 70, 145},{65, 55, 110},{65, 75, 110},{95, 60, 120},{65, 55, 110},{65, 75, 110}
};
float letter_H_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{150, 70, 140},{150, 90, 140},{125, 55, 110},{95, 60, 120},{65, 55, 110},{65, 75, 110},{75, 35, 70},{65, 55, 110},{45, 70, 140},{45, 90, 140}
};
float letter_I_commands[][3] = {
  {115, 35, 70},{95, 40, 80},{75, 35, 70},{75, 55, 70},{95, 40, 80},{95, 60, 120},{95, 70, 150},{95, 90, 150},{150, 70, 140},{95, 70, 150},{45, 70, 140},{45, 90, 140}
};
float letter_J_commands[][3] = {
  {115, 35, 70},{95, 40, 80},{75, 35, 70},{75, 55, 70},{95, 40, 80},{95, 60, 120},{95, 65, 135},{130, 70, 145},{135, 62.5, 125},{135, 82.5, 125}
};
float letter_K_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{150, 70, 140},{150, 90, 140},{85, 37.5, 75},{95, 52.5, 100},{112.5, 57.5, 120},{95, 65, 135},{60, 70, 145},{60, 90, 145}
};
float letter_L_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{150, 70, 140},{95, 70, 150},{45, 70, 140},{45, 90, 140}
};
float letter_M_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{150, 70, 140},{150, 90, 140},{115, 35, 70},{108.8, 50, 100},{95, 60, 120},{81.3, 50, 100},{75, 35, 70},{65, 55, 110},{45, 70, 140},{45, 90, 140}
};
float letter_N_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{150, 70, 140},{150, 90, 140},{115, 35, 70},{108.8, 50, 100},{95, 60, 120},{72.5, 63.8, 130},{45, 70, 140},{65, 55, 110},{75, 35, 70},{75, 55, 70}
};
float letter_O_commands[][3] = {
  {95, 40, 80},{105, 37.5, 75},{120, 47.5, 95},{135, 62.5, 125},{130, 70, 145},{60, 70, 145},{60, 62.5, 125},{70, 47.5, 95},{85, 37.5, 75},{85, 57.5, 75}
};
float letter_P_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{150, 70, 140},{150, 90, 140},{115, 35, 70},{95, 40, 80},{81.3, 50, 100},{95, 60, 120},{125, 55, 110},{125, 75, 110}
};
float letter_Q_commands[][3] = {
  {95, 40, 80},{105, 37.5, 75},{120, 47.5, 95},{135, 62.5, 125},{130, 70, 145},{60, 70, 145},{60, 62.5, 125},{70, 47.5, 95},{85, 37.5, 75},{85, 57.5, 75},{95, 60, 120},{72.5, 63.8, 130},{45, 70, 140},{45, 90, 140}
};
float letter_R_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{150, 70, 140},{150, 90, 140},{115, 35, 70},{95, 40, 80},{81.3, 50, 100},{95, 60, 120},{125, 55, 110},{112.5, 57.5, 120},{95, 65, 135},{60, 70, 145},{60, 90, 145}
};
float letter_S_commands[][3] = {
  {85, 37.5, 75},{105, 37.5, 75},{120, 47.5, 95},{112.5, 57.5, 120},{77.5, 57.5, 115},{60, 62.5, 125},{60, 70, 145},{130, 70, 145},{130, 90, 145}
};
float letter_T_commands[][3] = {
  {115, 35, 70},{95, 40, 80},{75, 35, 70},{75, 55, 70},{95, 40, 80},{95, 60, 120},{95, 70, 150},{95, 90, 150}
};
float letter_U_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{130, 70, 145},{60, 70, 145},{65, 55, 110},{75, 35, 70},{75, 55, 70}
};
float letter_V_commands[][3] = {
  {115, 35, 70},{112.5, 57.5, 120},{95, 70, 150},{77.5, 57.5, 115},{75, 35, 70},{75, 55, 70}
};
float letter_W_commands[][3] = {
  {115, 35, 70},{125, 55, 110},{130, 70, 145},{95, 60, 120},{95, 52.5, 100},{95, 60, 120},{60, 70, 145},{65, 55, 110},{75, 35, 70},{75, 55, 70}
};
float letter_X_commands[][3] = {
  {115, 35, 70},{108.8, 50, 100},{95, 60, 120},{72.5, 63.8, 130},{45, 70, 140},{45, 90, 140},{75, 35, 70},{81.3, 50, 100},{95, 60, 120},{117.5, 63.8, 130},{150, 70, 140},{150, 90, 140}
};
float letter_Y_commands[][3] = {
  {115, 35, 70},{108.8, 50, 100},{108.8, 70, 100},{75, 35, 70},{81.3, 50, 100},{95, 60, 120},{95, 70, 150},{95, 90, 150}
};
float letter_Z_commands[][3] = {
  {115, 35, 70},{95, 40, 80},{75, 35, 70},{81.3, 50, 100},{95, 60, 120},{117.5, 63.8, 130},{150, 70, 140},{95, 70, 150},{45, 70, 140},{45, 90, 140}
};
float period_commands[][3] = {
  {45, 90, 140},{45, 70, 140},{45, 90, 140}
};

// Struct for letter definitions
struct Letter {
  char letter;
  float (*commands)[3];
  int numCommands;
};

// Define supported letters
Letter letterCommands[] = {
  {'A', letter_A_commands, sizeof(letter_A_commands) / sizeof(letter_A_commands[0])},
  {'B', letter_B_commands, sizeof(letter_B_commands) / sizeof(letter_B_commands[0])},
  {'C', letter_C_commands, sizeof(letter_C_commands) / sizeof(letter_C_commands[0])},
  {'D', letter_D_commands, sizeof(letter_D_commands) / sizeof(letter_D_commands[0])},
  {'E', letter_E_commands, sizeof(letter_E_commands) / sizeof(letter_E_commands[0])},
  {'F', letter_F_commands, sizeof(letter_F_commands) / sizeof(letter_F_commands[0])},
  {'G', letter_G_commands, sizeof(letter_G_commands) / sizeof(letter_G_commands[0])},
  {'H', letter_H_commands, sizeof(letter_H_commands) / sizeof(letter_H_commands[0])},
  {'I', letter_I_commands, sizeof(letter_I_commands) / sizeof(letter_I_commands[0])},
  {'J', letter_J_commands, sizeof(letter_J_commands) / sizeof(letter_J_commands[0])},
  {'K', letter_K_commands, sizeof(letter_K_commands) / sizeof(letter_K_commands[0])},
  {'L', letter_L_commands, sizeof(letter_L_commands) / sizeof(letter_L_commands[0])},
  {'M', letter_M_commands, sizeof(letter_M_commands) / sizeof(letter_M_commands[0])},
  {'N', letter_N_commands, sizeof(letter_N_commands) / sizeof(letter_N_commands[0])},
  {'O', letter_O_commands, sizeof(letter_O_commands) / sizeof(letter_O_commands[0])},
  {'P', letter_P_commands, sizeof(letter_P_commands) / sizeof(letter_P_commands[0])},
  {'Q', letter_Q_commands, sizeof(letter_Q_commands) / sizeof(letter_Q_commands[0])},
  {'R', letter_R_commands, sizeof(letter_R_commands) / sizeof(letter_R_commands[0])},
  {'S', letter_S_commands, sizeof(letter_S_commands) / sizeof(letter_S_commands[0])},
  {'T', letter_T_commands, sizeof(letter_T_commands) / sizeof(letter_T_commands[0])},
  {'U', letter_U_commands, sizeof(letter_U_commands) / sizeof(letter_U_commands[0])},
  {'V', letter_V_commands, sizeof(letter_V_commands) / sizeof(letter_V_commands[0])},
  {'W', letter_W_commands, sizeof(letter_W_commands) / sizeof(letter_W_commands[0])},
  {'X', letter_X_commands, sizeof(letter_X_commands) / sizeof(letter_X_commands[0])},
  {'Y', letter_Y_commands, sizeof(letter_Y_commands) / sizeof(letter_Y_commands[0])},
  {'Z', letter_Z_commands, sizeof(letter_Z_commands) / sizeof(letter_Z_commands[0])},
  {'period', period_commands, sizeof(period_commands) / sizeof(period_commands[0])}
};

void setup() {
  // setup serial 
  Serial.begin(9600);
  while (Serial.available() <= 0) {
    Serial.println("hello"); // send a starting message
    delay(300);              // wait 1/3 second
  }

  // initial positions for the robot arm servos
  servo_x_axis.attach(servoPin_x, 95); // pin 및 시작 X축 각도
  servo_y_axis.attach(servoPin_y, 65); // pin 및 시작 Y축 각도
  servo_z_axis.attach(servoPin_z, 80); // pin 및 시작 Z축 각도

  // initial position for the state flag servo (vacant)
  servo_flag.attach(stateFlagPin, 100); // vacant

  // Servo speed and easing
  setSpeedForAllServos(general_speed);
  setEasingTypeForAllServos(EASE_SINE_IN_OUT);

  delay(500); // 시작 위치로 이동 대기
}

void loop() {
  // read from Hall Effect sensor 
  int sensorValue = digitalRead(switchPin);

  // update switch state
  if(sensorValue == LOW) { 
    switchState = true;
  } else {
    switchState = false;
  }
  
  //if the state is in waiting and the initiator switch changes to true, then change state to printing
  if(state_chair_waiting && switchState) {
    state_chair_waiting = false;
    state_chair_printing = true;
    
    //show 'occupied' on state flag
    changeStateFlag(state_chair_waiting);
  }
  
  //if the state is in printing and switch is still on, write word
  if(state_chair_printing) {
    while(switchState){
      delay(2000); //wait 2 seconds and then start writing
      writeWord(print_string);
      delay(5000); // delay for 5 seconds while user decides whether to try again
      
      // check Hall Effect sensor
      sensorValue = digitalRead(switchPin);
      if(sensorValue == LOW) { 
        switchState = true;
      } else {
        switchState = false;
      }
    }
    
    //after the word is done writing, change states and send Serial 
    state_chair_printing = false;
    state_monitor = true;
    Serial.println(print_string);
  }

  if (Serial.available() > 0) {
    //read input from serial
    String inString = Serial.readStringUntil('\n'); // Reads until newline character

    //if the string isn't the start signal(11111) and it is in monitor state then store the string to be printed with the robot arm and change states to waiting 
    //if (inString != "11111" && state_monitor) {
    if (state_monitor) {
      print_string = inString;
      state_monitor = false;
      state_chair_waiting = true;
    }
  }
  //show 'vacant' on state flag
  changeStateFlag(state_chair_waiting);
}

// function that splits string into letters and calls writeLetter()
void writeWord(String word) {
  //write each letter
  for (size_t i = 0; i < word.length(); i++) {
    char letter = word[i];
    writeLetter(letter);
  }

  //write a period
  Letter* periodd = findLetter('period');

  // Execute each servo command for the letter
  for (int i = 0; i < periodd->numCommands; i++) {
    float x_angle = periodd->commands[i][0];
    float y_angle = periodd->commands[i][1];
    float z_angle = periodd->commands[i][2];

    servo_x_axis.setEaseTo(x_angle, general_speed);
    servo_y_axis.setEaseTo(y_angle, general_speed);
    servo_z_axis.setEaseTo(z_angle, general_speed);

    synchronizeAllServosStartAndWaitForAllServosToStop();
    delay(200); // Adjust delay as needed
  }
}

// function that writes a single letter by executing its predefined servo commands
void writeLetter(char letter) {
  Letter* letterData = findLetter(letter);

  if (letterData) {
    // Execute each servo command for the letter
    for (int i = 0; i < letterData->numCommands; i++) {
      float x_angle = letterData->commands[i][0];
      float y_angle = letterData->commands[i][1];
      float z_angle = letterData->commands[i][2];

      servo_x_axis.setEaseTo(x_angle, general_speed);
      servo_y_axis.setEaseTo(y_angle, general_speed);
      servo_z_axis.setEaseTo(z_angle, general_speed);

      synchronizeAllServosStartAndWaitForAllServosToStop();
      delay(200); // Adjust delay as needed
    }
  } 
}

// Find the letter's command data
Letter* findLetter(char letter) {
  for (int i = 0; i < sizeof(letterCommands) / sizeof(letterCommands[0]); i++) {
    if (letterCommands[i].letter == letter) {
      return &letterCommands[i];
    }
  }
  return nullptr; // Return null if the letter is not supported
}


// function that changes state flag servo 
void changeStateFlag(bool waitingState) {
  if (waitingState) { 
    servo_flag.setEaseTo(100, flag_speed); // when in waiting set target position to 100
  } else { 
    servo_flag.setEaseTo(20, flag_speed); // when in using set target position to 20
  }
  synchronizeAllServosStartAndWaitForAllServosToStop();
}
