/*************************************************
   Public Constants
 *************************************************/

#define NOTE_C4  262  //need
#define NOTE_E4  330 //need
#define NOTE_G4  392 // need
#define NOTE_B4  494 //need


int button[]={A1,A3,A4,A5}; // 4 control buttons up left down right
 
// notes in the melody:
int tones[] = {262, 330, 392, 494};   
//tones to play with each button (c, e, g, b)

int roundsToWin = 4;
//make an array of numbers that will be the sequence that the player needs to remember
int buttonSequence[16]; 

int buzzerPin = A0;
int pressedButton=4; // keep pressed button 4 as nothing
int roundCounter=1;
long startTime=0;
long timeLimit=5000; // 2 sec to hit button

boolean gameStarted = false;

//up game dovvn messages
int scrollspeed=20;//Set the scroll speed ( lower=faster)

int x;
int y;

//Columns
int latchPin1 = 12;  //Pin connected to ST_CP of 1st 74595   ANODE 
int clockPin1 = 13;  //Pin connected to SH_CP of 1st 74595  ANODE 
int dataPin1 = 11;   //Pin connected to DS of 1st 74595    ANODE 

int latchPin2 = 6;  //Pin connected to ST_CP of 2nd 74595   CATHODE
int clockPin2 = 7;  //Pin connected to SH_CP of 2nd 74595   CATHODE
int dataPin2 = 5;   //Pin connected to DS of 2nd 74595    CATHODE

//BITMAP
//Bits in this array represents one LED of the matrix
// 8 is # of rows, 6 is # of LED matrices
byte bitmap[8][3]; 

int numZones = sizeof(bitmap) / 8; // One Zone refers to one 8 x 8 Matrix ( Group of 8 columns)
int maxZoneIndex = numZones-1;
int numCols = numZones * 8;

//FONT DEFENITION
byte alphabets[][8] = {
   {0,0,0,0,0},//Space
 {255,144,144,144,255},//A
 {127, 73, 73, 73, 54},//B
 {62, 65, 65, 65, 34},//C
 {127, 65, 65, 34, 28},//D
 {255, 137, 137, 137, 137},//E
 {0, 68, 40, 16, 0},//F
 {0, 16, 40, 68, 0},//G
 {8, 16, 32, 16, 8},//H
 {0, 129, 255, 129, 0},//I
 {32, 16, 8, 16, 32},//J
 {255, 24, 60, 231, 129},//K
 {255, 1, 1, 1, 1},//L
 {255, 64, 32, 64, 255},//M
 {255,64, 32, 16, 255},//N
 {255, 129, 129, 129, 255},//O
 {127, 72, 72, 72, 48},//P
 {62, 65, 69, 66, 61},//Q
 {127, 72, 76, 74, 49},//R
 {241, 145, 145, 145, 159},//S
 {64, 64, 127, 64, 64},//T
 {126, 1, 1, 1, 126},//U
 {124, 2, 1, 2, 124},//V
 {254,1, 2, 1, 254},//W
 {99, 20, 8, 20, 99},//X
 {240, 16, 31, 16, 240},//Y
 {127, 34, 20, 8, 0},//Z
};

void setup() {
 pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);
  
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
//buttons
  pinMode(button[0], INPUT_PULLUP);
  pinMode(button[1], INPUT_PULLUP);
  pinMode(button[2], INPUT_PULLUP);
  pinMode(button[3], INPUT_PULLUP);

  pinMode(buzzerPin,OUTPUT);
 //Clear bitmap
reset();
gameTitle();
 }

//FUNCTIONS
// Displays bitmap array in the matrix
void RefreshDisplay(){
 for (int row = 0; row < 8; row++) {
   int rowbit = 1 << row;
   digitalWrite(latchPin2, LOW);//Hold latchPin LOW for transmitting data
   shiftOut(dataPin2, clockPin2, MSBFIRST, rowbit);   //Transmit data

   //Start sending column bytes
   digitalWrite(latchPin1, LOW);//Hold latchPin LOW for transmitting data

   //Shift out to each matrix
   for (int zone = maxZoneIndex; zone >= 0; zone--) 
   {
     shiftOut(dataPin1, clockPin1, MSBFIRST, bitmap[row][zone]);
   }

   //flip both latches at once to eliminate flicker
   digitalWrite(latchPin1, HIGH);//Return the latch pin 1 high to signal chip
   digitalWrite(latchPin2, HIGH);//Return the latch pin 2 high to signal chip

   //Wait
   delayMicroseconds(300);
 }
}

// Converts row and colum to bitmap bit and turn it off/on
void Plot(int col, int row, bool isOn){
 int zone = col / 8;
 int colBitIndex = x % 8;
 byte colBit = 1 << colBitIndex;
 if (isOn)
   bitmap[row][zone] =  bitmap[y][zone] | colBit;
 else
   bitmap[row][zone] =  bitmap[y][zone] & (~colBit);
}
// Plot each character of the message one column at a time, updated the display, shift bitmap left.

//Show game name "Simon Says"
void gameTitle() {
  char msg[] ="SIMONSAYS";//Change the text here.
 for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
 {
   int alphabetIndex = msg[charIndex] - '@';
   if (alphabetIndex < 0) alphabetIndex=0;
   
   //Draw one character of the message
   // Each character is 5 columns wide, loop two more times to create 2 pixel space betwen characters
   for (int col = 0; col < 7; col++)
   {
     for (int row = 0; row < 8; row++)
     {
       // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
       bool isOn = 0; 
       if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
       Plot( numCols-1, row, isOn); //Draw on the rightmost column, the shift loop below will scroll it leftward.
     }
     for (int refreshCount=0; refreshCount < scrollspeed; refreshCount++)
       RefreshDisplay();
     //Shift the bitmap one column to left
     for (int row=0; row<8; row++)
     {
       for (int zone=0; zone < numZones; zone++)
       {
         //This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
         bitmap[row][zone] = bitmap[row][zone] >> 1;
         // Shift over lowest bit from the next zone as highest bit of this zone.
         if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
       }
     }
   }
 }
 }


//Show message "win"
void winText(){
  char msg[] ="WIN";//Change the text here.
 for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
 {
   int alphabetIndex = msg[charIndex] - '@';
   if (alphabetIndex < 0) alphabetIndex=0;
   
   //Draw one character of the message
   // Each character is 5 columns wide, loop two more times to create 2 pixel space betwen characters
   for (int col = 0; col < 7; col++)
   {
     for (int row = 0; row < 8; row++)
     {
       // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
       bool isOn = 0; 
       if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
       Plot( numCols-1, row, isOn); //Draw on the rightmost column, the shift loop below will scroll it leftward.
     }
     for (int refreshCount=0; refreshCount < scrollspeed; refreshCount++)
       RefreshDisplay();
     //Shift the bitmap one column to left
     for (int row=0; row<8; row++)
     {
       for (int zone=0; zone < numZones; zone++)
       {
         //This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
         bitmap[row][zone] = bitmap[row][zone] >> 1;
         // Shift over lowest bit from the next zone as highest bit of this zone.
         if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
       }
     }
   }
 }
}
// Show message "lose"
void loseText(){
  char msg[] ="LOSS ";//Change the text here.
 for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
 {
   int alphabetIndex = msg[charIndex] - '@';
   if (alphabetIndex < 0) alphabetIndex=0;
   
   //Draw one character of the message
   // Each character is 5 columns wide, loop two more times to create 2 pixel space betwen characters
   for (int col = 0; col < 7; col++)
   {
     for (int row = 0; row < 8; row++)
     {
       // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
       bool isOn = 0; 
       if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
       Plot( numCols-1, row, isOn); //Draw on the rightmost column, the shift loop below will scroll it leftward.
     }
     for (int refreshCount=0; refreshCount < scrollspeed; refreshCount++)
       RefreshDisplay();
     //Shift the bitmap one column to left
     for (int row=0; row<8; row++)
     {
       for (int zone=0; zone < numZones; zone++)
       {
         //This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
         bitmap[row][zone] = bitmap[row][zone] >> 1;
         // Shift over lowest bit from the next zone as highest bit of this zone.
         if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
       }
     }
   }
 }
}
void arrowRightText(){
  char msg[] ="F";//Change the text here.
 for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
 {
   int alphabetIndex = msg[charIndex] - '@';
   if (alphabetIndex < 0) alphabetIndex=0;
   
   //Draw one character of the message
   // Each character is 5 columns wide, loop two more times to create 2 pixel space betwen characters
   for (int col = 0; col < 7; col++)
   {
     for (int row = 0; row < 8; row++)
     {
       // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
       bool isOn = 0; 
       if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
       Plot( numCols-1, row, isOn); //Draw on the rightmost column, the shift loop below will scroll it leftward.
     }
     for (int refreshCount=0; refreshCount < scrollspeed; refreshCount++)
       RefreshDisplay();
     //Shift the bitmap one column to left
     for (int row=0; row<8; row++)
     {
       for (int zone=0; zone < numZones; zone++)
       {
         //This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
         bitmap[row][zone] = bitmap[row][zone] >> 1;
         // Shift over lowest bit from the next zone as highest bit of this zone.
         if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
       }
     }
   }
 }
}
void arrowLeftText(){
  char msg[] ="G";//Change the text here.
 for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
 {
   int alphabetIndex = msg[charIndex] - '@';
   if (alphabetIndex < 0) alphabetIndex=0;
   
   //Draw one character of the message
   // Each character is 5 columns wide, loop two more times to create 2 pixel space betwen characters
   for (int col = 0; col < 7; col++)
   {
     for (int row = 0; row < 8; row++)
     {
       // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
       bool isOn = 0; 
       if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
       Plot( numCols-1, row, isOn); //Draw on the rightmost column, the shift loop below will scroll it leftward.
     }
     for (int refreshCount=0; refreshCount < scrollspeed; refreshCount++)
       RefreshDisplay();
     //Shift the bitmap one column to left
     for (int row=0; row<8; row++)
     {
       for (int zone=0; zone < numZones; zone++)
       {
         //This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
         bitmap[row][zone] = bitmap[row][zone] >> 1;
         // Shift over lowest bit from the next zone as highest bit of this zone.
         if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
       }
     }
   }
 }
}
void arrowUpText(){
  char msg[] ="H";//Change the text here.
 for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
 {
   int alphabetIndex = msg[charIndex] - '@';
   if (alphabetIndex < 0) alphabetIndex=0;
   
   //Draw one character of the message
   // Each character is 5 columns wide, loop two more times to create 2 pixel space betwen characters
   for (int col = 0; col < 7; col++)
   {
     for (int row = 0; row < 8; row++)
     {
       // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
       bool isOn = 0; 
       if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
       Plot( numCols-1, row, isOn); //Draw on the rightmost column, the shift loop below will scroll it leftward.
     }
     for (int refreshCount=0; refreshCount < scrollspeed; refreshCount++)
       RefreshDisplay();
     //Shift the bitmap one column to left
     for (int row=0; row<8; row++)
     {
       for (int zone=0; zone < numZones; zone++)
       {
         //This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
         bitmap[row][zone] = bitmap[row][zone] >> 1;
         // Shift over lowest bit from the next zone as highest bit of this zone.
         if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
       }
     }
   }
 }
}
void arrowDownText(){
  char msg[] ="J";//Change the text here.
 for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
 {
   int alphabetIndex = msg[charIndex] - '@';
   if (alphabetIndex < 0) alphabetIndex=0;
   //Draw one character of the message
   // Each character is 5 columns wide, loop two more times to create 2 pixel space betwen characters
   for (int col = 0; col < 7; col++)
   {
     for (int row = 0; row < 8; row++)
     {
       // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
       bool isOn = 0; 
       if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
       Plot( numCols-1, row, isOn); //Draw on the rightmost column, the shift loop below will scroll it leftward.
     }
     for (int refreshCount=0; refreshCount < scrollspeed; refreshCount++)
       RefreshDisplay();
     //Shift the bitmap one column to left
     for (int row=0; row<8; row++)
     {
       for (int zone=0; zone < numZones; zone++)
       {
         //This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
         bitmap[row][zone] = bitmap[row][zone] >> 1;
         // Shift over lowest bit from the next zone as highest bit of this zone.
         if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
       }
     }
   }
 }
}
void winSequence(){
    //play the 1Up noise
  tone(buzzerPin, 1318, 150);   //E6
  delay(175);
  tone(buzzerPin, 1567, 150);   //G6
  delay(175);
  tone(buzzerPin, 2637, 150);   //E7
  delay(175);
  tone(buzzerPin, 2093, 150);   //C7
  delay(175);
  tone(buzzerPin, 2349, 150);   //D7
  delay(175);
  tone(buzzerPin, 3135, 500);   //G7
  delay(500);
  winText();
   do {
    pressedButton = buttonCheck();
     gameTitle();
  } while (pressedButton > 3);
  delay(100);
  gameStarted = false;
}

void loseSequence(){
  tone(buzzerPin, 130, 250);   //E6
  delay(275);
  tone(buzzerPin, 73, 250);   //G6
  delay(275);
  tone(buzzerPin, 65, 150);   //E7
  delay(175);
  tone(buzzerPin, 98, 500);   //C7
  delay(500);
  loseText();
   //wait until a button is pressed
  do {
    pressedButton = buttonCheck();
    gameTitle();
  } while (pressedButton > 3) ;
  delay(200);
  gameStarted = false;   //reset the game so that the start sequence will play again.
}
void reset (){
   for (int row = 0; row < 8; row++) {
   for (int zone = 0; zone <= maxZoneIndex; zone++) {
     bitmap[row][zone] = 0; 
   }
 }  noTone(buzzerPin);
 }
void loop() {

  if (gameStarted == false) {   //if the game hasn't started yet
    startSequence();            //flash the start sequence
    roundCounter = 0;           //reset the round counter
    delay(1500);                //wait a second and a half
    gameStarted = true;         //set gameStarted to true so that this sequence doesn't start again
  }

  //each round, start by flashing out the sequence to be repeated
  for (int i = 0; i <= roundCounter; i++) { 
  //go through the array up to the current round number
    flashLED(buttonSequence[i]);          
    //turn on the LED for that array position and play the sound
    delay(200);                           
    //wait
    reset();                          
    //turn all of the LEDs off
    delay(200);
  }

  //then start going through the sequence one at a time and see if the user presses the correct button
  
  for (int i = 0; i <= roundCounter; i++) { 
  //for each button to be pressed in the sequence
    startTime = millis();       //record the start time
    while (gameStarted == true) { 
    //loop until the player presses a button or the time limit is up (the time limit check is in an if statement)
      pressedButton = buttonCheck();      
      //every loop check to see which button is pressed
      if (pressedButton < 4) {            
      //if a button is pressed... (4 means that no button is pressed)
        flashLED(pressedButton);          
        //flash the LED for the button that was pressed
        if (pressedButton == buttonSequence[i]) { 
        //if the button matches the button in the sequence
          delay(250);                   
          //leave the LED light on for a moment
          reset();                  
          //then turn off all of the lights and
          break;                        
          //end the while loop (this will go to the next number in the for loop)

        } else {                          
        //if the button doesn't match the button in the sequence
          loseSequence();               
          //play the lose sequence (the loose sequence stops the program)
          break;                        
          //when the program gets back from the lose sequence, break the while loop so that the game can start over
        }
      } else {                            
      //if no button is pressed
        reset();                      
        //turn all the LEDs off
      }
      //check to see if the time limit is up
      if (millis() - startTime > timeLimit) { 
      //if the time limit is up
        loseSequence();                       
        //play the lose sequence
        break;                                
        //when the program gets back from the lose sequence, break the while loop so that the game can start over
      }
    }
  }
  if (gameStarted == true) {
    roundCounter = roundCounter + 1;      
    //increase the round number by 1
    if (roundCounter >= roundsToWin) {             
     //if the player has gotten to the 16th round
      winSequence();                      
      //play the winning song
    }
    delay(500);                           
    //wait for half a second between rounds
  }
}

void flashLED(int ledNumber){
 switch(ledNumber){
   case 0: arrowUpText(); break;
   case 1: arrowLeftText(); break;
   case 2: arrowDownText(); break;
   case 3: arrowRightText(); break;
 }
  tone(buzzerPin,tones[ledNumber]);
}
int buttonCheck(){
   if (digitalRead(button[0]) == LOW) {
    return 0;
  } else if (digitalRead(button[1]) == LOW) {
    return 1;
  } else if (digitalRead(button[2]) == LOW) {
    return 2;
  } else if (digitalRead(button[3]) == LOW) {
    return 3;
  } else {
    return 4; //this will be the value for no button being pressed
  }
}
void startSequence() {
  randomSeed(analogRead(A2));   //make sure the random numbers are really random
  //populate the buttonSequence array with random numbers from 0 to 3
  for (int i = 0; i <= roundsToWin; i++) {
    buttonSequence[i] = round(random(0, 4));
  } // when the game starts
  for (int i = 0; i <= 3; i++) {
    tone(buzzerPin, tones[i], 200); //play one of the 4 tones
    delay(100);   //wait for a moment
  } //this will repeat 4 times
}