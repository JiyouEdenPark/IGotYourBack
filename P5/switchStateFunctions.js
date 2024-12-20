// function to switch state to guess
function switchToGuess() {
  //change state to guess
  state_guess = true;
  state_input = false;
  
  //input string
  input_string = inString;
  
  //display guess screen
  displayGuessInput();  
}

// function to switch state to input
function switchToInput() {
  //change state to input
  state_guess = false;
  state_input = true;
  
  //initialize input string
  input_string = '';
  
  //display input screen and hide next button
  toInputButton.hide();
  displayInput();
}

// function to switch state to waiting >> send serial data to Arduino
function switchToWait() {
  //change state to input
  state_guess = false;
  state_input = false;
  
  //send to serial
  serial.println(input_string);
  console.log("sent string: "+input_string);
  
  //initialize input string
  input_string = '';
  
  //initialize guess string
  guess_string = '';
  
  //display wait screen and hide next button
  toWaitingButton.hide();
  displayWait();
}