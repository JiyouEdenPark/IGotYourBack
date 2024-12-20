//function to display your input
function displayInput() {
  //remove next button if in input mode
  toWaitingButton.hide();
  
  //reset the input area
  background('#c3c3c3');
  strokeWeight(4);
  stroke('#000000');
  line(width,0,width,height);
  line(0,height,width,height);
  stroke('#fdffff');
  line(0,0,width,0);
  line(0,0,0,height)

  //top bar
  noStroke();
  fill('#010081');
  rect(2,2,width-4,30);
  textAlign(LEFT, CENTER);
  textSize(18);
  fill('#fdffff');
  text('I Got Your Back',10,15);
  textAlign(CENTER, CENTER);

  //input box
  noStroke();
  fill('#fdffff');
  rect(width/2-width*2/5, height/2-height*3/10+30, width*4/5, height*3/5);
  strokeWeight(2);
  stroke('#000000');
  line(width/2-width*2/5, height/2+height*3/10+30,width/2+width*2/5, height/2+height*3/10+30);
  line(width/2+width*2/5, height/2+height*3/10+30,width/2+width*2/5, height/2-height*3/10+30);
  stroke('#fdffff');
  line(width/2-width*2/5, height/2-height*3/10+30,width/2+width*2/5, height/2-height*3/10+30);
  line(width/2-width*2/5, height/2-height*3/10+30,width/2-width*2/5, height/2+height*3/10+30);
  
  //instructions
  noStroke();
  fill('#000000')
  textSize(24);
  text('LEAVE A MESSAGE FOR THE NEXT PERSON', width/2, height*3/25+30);
  textSize(18);
  text('write one word (up to 7 letters) and press enter', width/2, height*3/25+30+(h*1.2));
  
  //display the updated string
  noStroke();
  textSize(24);
  text(input_string, width / 2, height / 2);

  //underline what is newly being written
  stroke(1);
  if(input_string.length > 0) {
    let ww = textWidth(input_string);
    let w = textWidth(ltr);
    line(width / 2 + ww / 2-w, height / 2 + h, width / 2 + ww / 2, height / 2 + h);
  }
  
  //display output from check input (valid word, profanity)
  noStroke();
  if(input_string == "ITP") {
    check_valid = 1;
  } else {
    clearTimeout(debounceTimeout);
    debounceTimeout = setTimeout(() => {
      checkInput(input_string, result => {
        check_valid = result;
  
        // Re-render validation message
        if (check_valid == 2) {
          textSize(18);
          text(input_string + ' is not a valid word', width / 2, height - 50);
          textSize(24);
        } else if (check_valid == 3) {
          textSize(18);
          text('Please be nice 😥', width / 2, height - 50);
          textSize(24);
        }
      });
    }, 300); // 300ms debounce
  }
}

//function to display whether you want to confirm your input
function displayConfirm() {
  //reset the input area
  background('#c3c3c3');
  strokeWeight(4);
  stroke('#000000');
  line(width,0,width,height);
  line(0,height,width,height);
  stroke('#fdffff');
  line(0,0,width,0);
  line(0,0,0,height)

  //top bar
  noStroke();
  fill('#010081');
  rect(2,2,width-4,30);
  textAlign(LEFT, CENTER);
  textSize(18);
  fill('#fdffff');
  text('I Got Your Back',10,15);
  textAlign(CENTER, CENTER);
  
  //input box
  noStroke();
  fill('#fdffff');
  rect(width/2-width*2/5, height/2-height*3/10+30, width*4/5, height*3/5);
  strokeWeight(2);
  stroke('#000000');
  line(width/2-width*2/5, height/2+height*3/10+30,width/2+width*2/5, height/2+height*3/10+30);
  line(width/2+width*2/5, height/2+height*3/10+30,width/2+width*2/5, height/2-height*3/10+30);
  stroke('#fdffff');
  line(width/2-width*2/5, height/2-height*3/10+30,width/2+width*2/5, height/2-height*3/10+30);
  line(width/2-width*2/5, height/2-height*3/10+30,width/2-width*2/5, height/2+height*3/10+30);
  
  //instructions
  noStroke();
  fill('#000000')
  textSize(24);
  text('YOUR MESSAGE FOR THE NEXT PERSON', width/2, height*3/25+30);
  
  //confirm message
  text(input_string, width / 2, height / 2); 
  textSize(18);
  text('to confirm: press  NEXT button', width / 2, height / 2+h*2.5);
  text('to rewrite: press  BACKSPACE key', width / 2, height / 2+h*3.5);
  
  //show button to go to next state
  toWaitingButton.position(width/2-toWaitingButton.width/2, height*0.85);
  if(check_valid == 1 && input_string.length > 0) {
    toWaitingButton.show();
  } else if(check_valid > 1 || input_string.length == 0) {
    toWaitingButton.hide();
  }
  toWaitingButton.mousePressed(switchToWait);
}

//function to display what you're guessing 
function displayGuessInput() {
  //reset the input area
  background('#c3c3c3');
  strokeWeight(4);
  stroke('#000000');
  line(width,0,width,height);
  line(0,height,width,height);
  stroke('#fdffff');
  line(0,0,width,0);
  line(0,0,0,height)

  //top bar
  noStroke();
  fill('#010081');
  rect(2,2,width-4,30);
  textAlign(LEFT, CENTER);
  textSize(18);
  fill('#fdffff');
  text('I Got Your Back',10,15);
  textAlign(CENTER, CENTER);

  //input box
  noStroke();
  fill('#fdffff');
  rect(width/2-width*2/5, height/2-height*3/10+30, width*4/5, height*3/5);
  strokeWeight(2);
  stroke('#000000');
  line(width/2-width*2/5, height/2+height*3/10+30,width/2+width*2/5, height/2+height*3/10+30);
  line(width/2+width*2/5, height/2+height*3/10+30,width/2+width*2/5, height/2-height*3/10+30);
  stroke('#fdffff');
  line(width/2-width*2/5, height/2-height*3/10+30,width/2+width*2/5, height/2-height*3/10+30);
  line(width/2-width*2/5, height/2-height*3/10+30,width/2-width*2/5, height/2+height*3/10+30);
  
  //instructions
  noStroke();
  fill('#000000')
  textSize(24);
  text('GUESS WHAT YOU GOT', width/2, height*3/25+30);
  textSize(18);
  text('type and press enter', width/2, height*3/25+30+(h*1.2));
  textSize(24);
    
  //display the updated string
  text(guess_string, width / 2, height / 2);

  //underline what is newly being written
  stroke(1);
  if(guess_string.length > 0) {
    let ww = textWidth(guess_string);
    let w = textWidth(ltr);
    line(width / 2 + ww / 2-w, height / 2 + h, width / 2 + ww / 2, height / 2 + h);
  }
}

//function to display the answer and your guess (score)
function displayAnswer() {
  //reset the input area
  background('#fdffff'); 

  //top bar
  noStroke();
  fill('#010081');
  rect(2,2,width-4,30);
  textAlign(LEFT, CENTER);
  textSize(18);
  fill('#fdffff');
  text('I Got Your Back',10,15);
  textAlign(CENTER, CENTER);
  
  //show answer
  fill('#000000')
  textSize(24);
  text("You had on your back: "+inString, width/2, height*3/25+30);
  text("You guessed: "+guess_string, width/2, height*3/25+30+(h*1.2));
  
   //compute score
  let answer_len = inString.length-1;
  let compare_len = min(answer_len, guess_string.length);
  let correct_len = 0;
  for(i = 0; i < compare_len; i++){
    if(inString[i] == guess_string[i]) correct_len++;
  }
  
  let score = correct_len/answer_len;
  
  //give feedback
  if(score == 1 && answer_len == guess_string.length) {
    score_level = 1;
    image(imgPerfect, width/2, height/2+30, 460, 381);
    text('Perfect score!!! :D', width/2, height/2+h);
  } else if((score >= 0.7 && score < 1)||(score == 1 && answer_len != guess_string.length)) {
    score_level = 2;
    image(imgAlmost, width/2, height/2+30, 430, 381);
    text('You almost got it! :3', width/2, height/2+h);
  } else {
    score_level = 3;
    image(imgFun, width/2, height/2+30, 447, 381);
    text('At least you had fun, right? :P', width/2, height/2+h);
  }
  text('Ready to leave a message for the next person?', width/2, height/2+2*h);
  
  //show button to go to next state
  toInputButton.position(width/2-toInputButton.width/2, height/2+3*h);
  toInputButton.show();
  toInputButton.mousePressed(switchToInput);
}

//function to display wait
function displayWait() {
  background('#fdffff'); 
  
  //top bar
  noStroke();
  fill('#010081');
  rect(2,2,width-4,30);
  textAlign(LEFT, CENTER);
  textSize(18);
  fill('#fdffff');
  text('I Got Your Back',10,15);
  textAlign(CENTER, CENTER);
  
  //message
  image(imgGoodbye, width/2, height*0.4, width , width*1087/3453)
  fill('#000000');
  textSize(24);
  text('Thank you! <3\n\nfrom: I GOT YOUR BACK crew', width/2, height*0.75);
}