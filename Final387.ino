
#include <Servo.h>

Servo writer, eraser;  

int sx=116;   //standard width of the letters
int sy=144;   //standard height of letters 
int len=0;    //length of current string written on board
const int stepPin = 12;   //x stepper output
const int dirPin = 11;    //x stepper direction
const int stepPin2 = 13; // y stepper output
const int dirPin2 = 2;    //y stepper direction
char state='a';           //initial state to wait for string
String message;           //string to be written on board

void setup() {
  pinMode(stepPin,OUTPUT);    
  pinMode(dirPin,OUTPUT);
  digitalWrite(dirPin,LOW);     //initialize everything low
  digitalWrite(stepPin,LOW);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  digitalWrite(dirPin2,LOW);
  digitalWrite(stepPin2,LOW);
  writer.attach(10);            //initialize servos
  eraser.attach(9);
  eraser.write(90);             //initialize eraser and pen
  penOff();
  delay(5000);                  //wait 5 seconds to assure 9V supplied to motors
}

/*
 * 
 * NOTE: different servos will have different positions. Either calibrate the servos or 
 * change numbers in code (in set up and in penOff(), penOn(), and erase()
 * 
 */


//pushes pen away from whiteboard
void penOff(){
    writer.write(55);
    delay(500);
}

//allows pin to touch whiteboard
void penOn(){
  writer.write(145);
  delay(500);
}

//erases the whiteboard
void erase(){
    eraser.write(15);
    writer.write(145);
    //moves eraser down to ensure everything gets erased
    //sweeps back and forth all the way to the top of the board
    moveY(40,true);
    moveX(124,false);
    for(int i=0;i<4;i++){
    moveX(((sx+40)*len)+20,false);
    moveY(20,false);
    moveX(((sx+40)*len)+20,true);
    moveY(20,false);
    }

    //deactivates eraser and pushes pen away 
    writer.write(55);
    delay(100);
    eraser.write(90);

    //moves back to the original position
    moveX(((sx+40)*len),false);
    moveY(120,true);
    //goes back to initial state
    state='a';
}

//moves the stepper motor in y direction
void moveY(int y, bool d){
  //chooses direction, true moves pen down
  if(d)
   digitalWrite(dirPin2,HIGH);
  else
    digitalWrite(dirPin2,LOW);
  //steps however many times it is told
  for(int x = 0; x < y; x++) {
    digitalWrite(stepPin2,HIGH); 
    delay(2);
    digitalWrite(stepPin2,LOW);
    delay(2); 
  }
}

//moves stepper in x direction
void moveX(int x, bool d){
  
//chooses direction, true moves pen to the right
  if(d)
    digitalWrite(dirPin,LOW); 
  else
  
    digitalWrite(dirPin,HIGH); 

  //stepps however many times it is told
  for(int y = 0; y < x; y++) {
    digitalWrite(stepPin,HIGH);
    delay(1);
    digitalWrite(stepPin,LOW);
    
    delay(1); 
  }

  
}

//writes whatever letter is sent onto the board
//each letter ends in the bottom right corner with pen off
//moves standard gap of 40 steps between letters to prepare for next letter
void letter(char a){
  int x,y,z;
  //each letter of the alphabet hardcoded using standard widths and heights.
  switch(a){
    
    case 'a':
      penOn();
      moveY(sy,false);
      moveX(sx,true);
      moveY(sy,true);
      penOff();
      moveX(sx,false);
      moveY(sy/2,false);
      penOn();
      moveX(sx,true);
      penOff();
      moveY(sy/2,true);
      break;
      
   case 'b':
      penOn();
      moveY(sy,false);
      moveX(sx/2,true);
      moveY(sy/2,true);
      penOff();
      moveX(sx/2,false);
      penOn();
      moveX(sx,true);
      moveY(sy/2,true);
      moveX(sx,false);
      penOff();
      moveX(sx,true);
      break;

    case 'c':
      moveY(sy,false);
      moveX(sx,true);
      penOn();
      moveX(sx,false);
      moveY(sy,true);
      moveX(sx,true);
      penOff();
      break;

    case 'd':
        penOn();
        moveY(sy,false);
        for(x=0;x<sx;x++){
        moveX(1,true);
        z=x*sy/sx/2;
        moveY(z-y,true);
        y=z;
      }
      y=0;
      z=0;
      for(x=0;x<sx;x++){
        moveX(1,false);
        z=x*sy/sx/2;
        moveY(z-y,true);
        y=z;
      }
      penOff();
      moveX(sx,true);
      break;
      
    case 'e':
      penOn();
      moveY(sy,false);
      moveX(sx,true); 
      penOff();
      moveX(sx,false);
      moveY(sy/2,true);
      penOn();
      moveX(sx/2,true);
      penOff();
      moveX(sx/2,false);
      moveY(sy/2,true);
      penOn();
      moveX(sx,true);
      penOff();
      break;

     case 'f':
      penOn();
      moveY(sy,false);
      moveX(sx,true); 
      penOff();
      moveX(sx,false);
      moveY(sy/2,true);
      penOn();
      moveX(sx/2,true);
      penOff();
      moveX(sx/2,true);
      moveY(sy/2,true);
      break;

    case 'g':
      moveY(sy,false);
      moveX(sx,true);
      penOn();
      moveX(sx,false);
      moveY(sy,true);
      moveX(sx,true);
      moveY(sy/2,false);
      moveX(sx/2,false);
      penOff();
      moveY(sy/2,true);
      moveX(sx/2,true);
      break;
      
    case 'h':
      penOn();
      moveY(sy,false);
      penOff();
      moveY(sy/2,true);
      penOn();
      moveX(sx,true);
      penOff();
      moveY(sy/2, false);
      penOn();
      moveY(sy,true);
      penOff();
      break;

    case 'i':
      penOn();
      moveX(sx,true);
      penOff();
      moveY(sy,false);
      penOn();
      moveX(sx,false);
      penOff();
      moveX(sx/2, true);
      penOn();
      moveY(sy,true);
      penOff();
      moveX(sx/2,true);
      break;

    case 'j':
      moveY(sy/2, false);
      penOn();
      moveY(sy/2, true);
      moveX(sx,true);
      moveY(sy, false);
      penOff();
      moveY(sy, true);
      break;
      
    case 'k':
      penOn();
      moveY(sy,false);
      penOff();
      moveX(sx,true);
      penOn();
      for(x=0;x<sx;x++){
        moveX(1,false);
        z=x*sy/sx/2;
        moveY(z-y,true);
        y=z;
      }
      moveX(sx,true);
      moveY(sy/2,true);
      penOff();
      break;

    case 'l':
      moveY(sy,false);
      penOn();
      moveY(sy, true);
      moveX(sx,true);
      penOff();
      break;

    case 'm':
       penOn();
       moveY(sy,false);
       moveX(sx/2,true);
       moveY(sy*3/4,true);
       moveY(sy*3/4,false);
       moveX(sx/2,true);
       moveY(sy,true);
       penOff();
       break;
      
    case 'n':
      penOn();
      moveY(sy,false);
      moveX(sx,true);
      moveY(sy,true);
      penOff();
      break;
    
    case 'o':
      penOn();
      moveY(sy,false);
      moveX(sx,true);
      moveY(sy,true);
      moveX(sx,false);
      penOff();
      moveX(sx,true);
      break;

   case 'p':
      penOn();
      moveY(sy,false);
      moveX(sx,true);
      moveY(sy/2,true);
      moveX(sx,false);
      penOff();
      moveX(sx,true);
      moveY(sy/2,true);
      break;

    case 'q':
      penOn();
      moveY(sy,false);
      moveX(sx,true);
      moveY(3*sy/4,true);
      z=0;
      y=0;
      for(x=0;x<sx/4;x++){
        moveX(1,false);
        z=x*sy/sx;
        moveY(z-y,true);
        y=z;
      }
      moveX(3*sx/4,false);
      penOff();
      moveX(3*sx/4,true);
      moveY(sy/4,false);
      penOn();
      z=0;
      y=0;
      for(x=0;x<sx/4;x++){
        moveX(1,true);
        z=x*sy/sx;
        moveY(z-y,true);
        y=z;
      }
      penOff();
      break;
    
    case 'r':
      penOn();
      moveY(sy,false);
      moveX(sx,true);
      moveY(sy/2,true);
      moveX(sx,false);
      z=0;
      y=0;
      penOn();
      for(x=0;x<sx;x++){
        moveX(1,true);
        z=x*sy/sx/2;
        moveY(z-y,true);
        y=z;
      }
      penOff();
      break;

    case 's':
      penOn();
      moveX(sx,true);
      moveY(sy/2,false);
      moveX(sx,false);
      moveY(sy/2,false);
      moveX(sx,true);
      penOff();
      moveY(sy,true);
      break;

      
    case 't':
      moveY(sy,false);
      penOn();
      moveX(sx,true);
      penOff();
      moveX(sx/2,false);
      penOn();
      moveY(sy,true);
      penOff();
      moveX(sx/2,true);
      break;

    case 'u': 
      moveY(sy,false);
      penOn();
      moveY(sy,true);
      moveX(sx,true);
      moveY(sy,false);
      penOff();
      moveY(sy,true);
      break;

    case 'v': 
      moveY(sy,false);
      penOn();
      moveY(sy/2,true);
      z=0;
      y=0;
      for(x=0;x<sx/2;x++){
        moveX(1,true);
        z=x*sy/sx;
        moveY(z-y,true);
        y=z;
      }
      z=0;
      y=0;
      for(x=0;x<sx/2;x++){
        moveX(1,true);
        z=x*sy/sx;
        moveY(z-y,false);
        y=z;
      }
      moveY(sy/2,false);
      penOff();
      moveY(sy,true);
      break;

    case 'w':
       
       moveY(sy,false);
       penOn();
       moveY(sy,true);
       moveX(sx/2,true);
       moveY(sy/4,false);
       moveY(sy/4,true);
       moveX(sx/2,true);
       moveY(sy,false);
       penOff();
       moveY(sy,true);
       break;

    case 'x':
      z=0;
      y=0;
      penOn();
      for(x=0;x<sx;x++){
        moveX(1,true);
        z=x*sy/sx;
        moveY(z-y,false);
        y=z;
      }
      penOff();
      moveX(sx, false);
      z=0;
      y=0;
      penOn();
      for(x=0;x<sx;x++){
        moveX(1,true);
        z=x*sy/sx;
        moveY(z-y,true);
        y=z;
      }
      penOff();
      break;

    case 'y':
      moveY(sy,false);
      penOn();
      moveY(sy/2, true);
      moveX(sx,true);
      moveY(sy/2, false);
      penOff();
      moveY(sy/2, true);
      moveX(sx/2,false);
      penOn();
      moveY(sy/2, true);
      penOff();
      moveX(sx/2,true);
      break;

    case 'z':
      moveY(sy,false);
      penOn();
      moveX(sx,true);
      z=0;
      y=0;
      penOn();
      for(x=0;x<sx;x++){
        moveX(1,false);
        z=x*sy/sx;
        moveY(z-y,true);
        y=z;
      }
      moveX(sx,true);
      penOff();
     
      break;

    //blank space
    case ' ':
      moveX(sx,true);
      break;
  }
  //after letter is concluded, it moves right 40 steps to begin next letter
  moveX(40,true);
}

//writes the message on the board by sending one letter at a time
void text(){
  int i=0;
  //sets the length global variable to the length of the string
  len=message.length();

  //writes every letter one by one
  while(i<len){
    letter(message[i]);
    i++;
  }
  
  //moves the pen to the right enough to see the full string written on the board
  moveX(124,true);

  //changes state
  state='e';
}

int cycle=0;//variable only used for hardcoding strings to be written
void waitForString(){
  //delay to simulate waiting for a string
  delay(3000);
  //this method would be where it is waiting for user input
  //since no user input is available, hard coded a demo
  switch(cycle){
    case 0:
      message="project";
      break;
    case 1:
      message="abcdefghijklm";
      break;
    case 2:
      message="nopqrstuvwxyz";
      break;
  }
    cycle=((++cycle)%3);
  state='b';
}

//sets the width of each letter smaller if more letters in string
void processCommand(){
    switch(message.length()/8){
      case 0: 
        sx=116;
        sy=144;
        state='c';
        break;
      case 1:
        sx=116/2;
        sy=144/2;
        state='c';
        break;
      
      //error if it cant fit on board (not used with current hardcoded strings)
      default:
        state='d';
        break;
    }
    

}

//only used if user input is used
void error(){
  //print error message to whatever user input is being used
  state='a';
}

//waits for user input to erase the board, since no user input is used
//delay is used to simulate
void waitForErase(){
  //command to erase
  delay(5000);
  state='f';
}

//finite state 
void loop() {
 switch(state){
  case 'a':
    waitForString();
    break;
  case 'b':
    processCommand();
    break;
  case 'c':
    text();
    break;
  case 'd':
    error();
    break;
  case 'e': 
    waitForErase();
    break;
  case 'f':
    erase();
 }
}

