// variable to hold an instance of the p5.webserial library:
const serial = new p5.WebSerial();
let inString; //string received from arduino == what was written on the back 

//states to change with input from arduino
let state_guess = false;
let state_input = false;

//input words
let input_string = 'ITP'; //word to send to arduino & answer
let guess_string = ''; //word guessed

//score level (3 tiers) -- global for possible interaction
let score_level;

// Limit the input length to 7 characters
let max_length = 7; 

// store response from checkInput
let check_valid = 0; 

// timeout setting for fetching result from API
let debounceTimeout;

//letter to display
let ltr='';

//Text height for alignment
let h;

//button to go to next state
let toInputButton;
let toWaitingButton;

// Local profane words dictionary - courtesy of google-profanity-words
let profanityList = []; 
function preload() {
  profanityList = loadStrings('profanity_en.txt');
  myFont = loadFont('ms-sans-serif-2.ttf');
  imgFun = loadImage('fun.png');
  imgAlmost = loadImage('almost.png');
  imgPerfect = loadImage('perfect.png');
  imgGoodbye = loadImage('goodbye_2.png');
}

function setup() {
  createCanvas(windowWidth, windowHeight);
  background('#818181');
  
  textAlign(CENTER, TOP);
  textSize(24);
  h = textAscent() + textDescent(); // height of a line of text at 24 font-size
  textFont(myFont);
  imageMode(CENTER);
  
  //create button to input state and hide
  toInputButton = createButton('YES');
  toInputButton.hide();
  
  //create button to waiting state and hide
  toWaitingButton = createButton('NEXT');
  toWaitingButton.hide();  
  
  serialSetup();

  //set up initial screen 
  if (state_input) {
    displayInput();
  } else if (state_guess) {
    displayGuessInput();  
  } else {
    displayWait();
  }
}

function draw() {
  console.log("received string: "+inString, "input_string: "+input_string, "guess_string: "+guess_string);
}