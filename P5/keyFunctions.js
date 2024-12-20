function keyTyped() {
  //only run when state is in input
  if(state_input){
    // Check if the key is a letter (a-z, A-Z)
    if (keyCode != ENTER && key.match(/[a-zA-Z]/) && input_string.length < max_length) {
      ltr = key.toUpperCase();
      input_string += ltr; // Append the letter in uppercase
      displayInput();
    }
  //only run when state is in guess
  } else if(state_guess){
    // Check if the key is a letter (a-z, A-Z)
    if (keyCode != ENTER && key.match(/[a-zA-Z]/) && guess_string.length < max_length) {
      ltr = key.toUpperCase();
      guess_string += ltr; // Append the letter in uppercase
      displayGuessInput();
    }  
  }
}

function keyPressed() {
  //only run when state is in input
  if(state_input){
    if (keyCode === BACKSPACE && input_string.length > 0) {
      input_string = input_string.slice(0, -1); // Remove the last character
      displayInput();
    } else if (keyCode === ENTER && input_string.length > 0 && check_valid < 2) { //display confirm screen only if input is valid (0 or 1)
      displayConfirm();
    }
  //only run when state is in guess
  } else if(state_guess){
    if (keyCode === BACKSPACE && guess_string.length > 0) {
      guess_string = guess_string.slice(0, -1); // Remove the last character
      displayGuessInput();
    } else if (keyCode === ENTER && guess_string.length > 0) {
      displayAnswer();
    }
  }
}

//checks input string valid words and profanity
function checkInput(inputString, callback) {
  let userInput = inputString.toLowerCase();
  
  if(userInput.length > 0) {
    fetch(`https://api.dictionaryapi.dev/api/v2/entries/en/${userInput}`)
    .then(response => {
      if (response.ok) {
        if (profanityList.includes(userInput)) {
          callback(3); // profanity code
        } else {
          callback(1); // valid code
        }
      } else {
        callback(2); // invalid word code
      }
    })
    .catch(error => {
      callback(0); // validation error
    });
  }
}