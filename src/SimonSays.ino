int inputPin = A0;
int ledPins[] = {D2, D1, D6, D7};
int inputValues[] = {170, 27, 117, 196};
int buttonsToClick[1000];
int buttonsToClickPointer = -1;
int gameLength = 0;

int getLedPinFromValue(int value);
void resetGame();
void blinkLeds();

void setup()
{

  //setup the leds to be an output
  for (int i = 0; i < 4; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }

  //firstly restart the game to start game logic
  resetGame();

  //declare serial baude rate
  Serial.begin(9600);
}

void loop()
{

  //check if we need to show the user the order of buttons
  if(buttonsToClickPointer == -1){
    //show the led order in buttonsToClick array until the next value isnt set
    for(int i = 0; i < 1000;i++){
      if(buttonsToClick[i] == 0){ break;}

      digitalWrite(buttonsToClick[i],HIGH);
      delay(500-(gameLength/100));
      digitalWrite(buttonsToClick[i],LOW);
      delay(500-(gameLength/100));
    }
    //finaly set the pointer to index 0
    buttonsToClickPointer = 0;
  }

  //get read input on A0 analog pin and convert value to a pin
  int readVal = analogRead(inputPin);
  int clickedButton = getLedPinFromValue(readVal);
  
  //if we dont got an input then return
  if(clickedButton == -1){ return; }

  //show clicked led
  digitalWrite(clickedButton, HIGH);
  delay(500);
  digitalWrite(clickedButton, LOW);

  //check if we got right input
  if(buttonsToClick[buttonsToClickPointer] == clickedButton){
    Serial.println("Right input");
    //do we reach the end of the streak?
    if(buttonsToClickPointer == gameLength){
      //show the user thats his input was right
      blinkLeds();
      //add new field to buttonsToClick
      buttonsToClick[buttonsToClickPointer+1] = ledPins[random(4)];
      //reset pointer to show leds again
      buttonsToClickPointer = -1;
      //increment the gameLength
      gameLength++;
      return;
    }
    //increment the pointer to point at next array field
    buttonsToClickPointer++;
  }else{
    //input was wrong
    Serial.println("Worng input");
    //show user that his input was wrong
    for(int i = 0; i<3;i++){
      blinkLeds();
    }
    //reset game
    resetGame();
  }
}

int getLedPinFromValue(int value)
{
  for (int i = 0; i < 4; i++)
  {
    int diff = inputValues[i] - value;
    if (diff < 0)
    {
      diff = diff * -1;
    }
    if (diff <= 5)
    {
      return ledPins[i];
    }
  }
  //nothing found return;
  return -1;
}

void resetGame(){
  for(int i = 0;i<1000;i++){
    buttonsToClick[i] = 0;
  }
  buttonsToClick[0] = ledPins[random(4)];
  gameLength = 0;
  buttonsToClickPointer=-1;
}

void blinkLeds(){
    for(int i = 0; i<4;i++){
      digitalWrite(ledPins[i],HIGH);
    }
    delay(500);
    for(int i = 0; i<4;i++){
      digitalWrite(ledPins[i],LOW);  
    }
    delay(500);
}