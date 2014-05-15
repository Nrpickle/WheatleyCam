// Wheatley Cam Basic movement firmware
// Nick McComb
// [mccombn@onid.oregonstate.edu]

//WheatleyRobotics


//Limit switches
//Green is white D1 Right
//Orange is left D2 Left

#include <Servo.h> 
Servo movement;
Servo rotate;  
Servo tilt;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
              
 
int pos = 0;    // variable to store the servo position 

int led = 11;                 //A10
int reedSwitch = 13;          //B4

const short tiltPin = 20;     //F1
const short rotatePin = 21;   //F0
const short movementPin = 19; //F4

const short rightLimit = 6;   //D1
const short leftLimit = 7;    //D2

byte currentPos;

int currentRotation = 90;
int currentTilt;

const int servoDelay = 20;

const byte maxPosition = 3;  //Maximum supported position for movement
const byte minRotateAngle = 10;
const byte maxRotateAngle = 170; 
const byte minTiltAngle = 10;
const byte maxTiltAngle = 110;

//Function Prototypes (technically not required in Arduino, but nice for reference)
void moveToPos(int desiredPos);
void rotateTo(int degree);
void tiltTo(int degree);

//Helper functions
void goRight(); 
void goLeft();


void setup() 
{ 
  //Attach all of the servos
  tilt.attach(tiltPin); 
  rotate.attach(rotatePin);
  movement.attach(movementPin);
  
  //Init
  rotate.write(90);     //Init rotation at "straight ahead"
  currentRotation = 90;
  
  tilt.write(90);       //Init tilt at "straight ahead"
  currentTilt = 90; 
 
  movement.write(94);   //Movement stop position
  //END Init
  
  
  /* TEENSY */
  pinMode(rightLimit, INPUT_PULLUP);
  pinMode(leftLimit, INPUT_PULLUP);
  
  pinMode(led, OUTPUT);
  pinMode(reedSwitch, INPUT_PULLUP);
  /* END TEENSY */
  
  movement.write(88);
  
  Initial calibrate (find where it is)
  while(!digitalRead(leftLimit)){
    digitalWrite(led, HIGH);
  }
  digitalWrite(led, LOW);
  movement.write(94);  //Stop moving
  goRight();
  currentPos = 1;
} 

int alt = 0;
 
 

 
 
void loop() 
{ 
  
  moveToPos(2);
  
  delay(1000);
  
  moveToPos(1);
  
  delay(1000);
  
  moveToPos(3);
  
  delay(1000);
    
}


/*
func: moveToPos

desc: This function takes in an integer and moves Wheatley to that 
	position on the rail. Currently the available positions are between 1
	and maxPosition.

	Function exits if it does not receive a valid value as determined 
	by constants.
*/
void moveToPos(int desiredPos){
  
  //Error checking
  if (desiredPos <= 0)
    return;
  if (desiredPos > maxPosition)
	return;
  
  int delta = desiredPos - currentPos; //Number needed to travel right
  
  if(delta > 0){ //Need to travel right
    for(int i = 0; i < delta; ++i){
      goRight();
      delay(100);      
    }    
  }
  else if (delta < 0) { // Need to travel left
    delta = abs(delta);
    for(int i = 0; i < delta; ++i){
      goLeft();
      delay(100);      
    }
  }
  
  currentPos = desiredPos;
}


/*
func: rotateTo

desc: Rotates Wheatley's camera to the specified degree (absolute).

	Function exits if it does not receive a valid value as determined 
	by constants.
*/

void rotateTo(int degree){

  //Input constraint
  if (degree < minRotateAngle)
    return;
  if (degree > maxRotateAngle)
    return;

  int degreesToMove = abs(currentRotation - degree);
  
  //Smooths the turn (makes it a little creepier too)
  for(int i = 0; i < degreesToMove; ++i){
    movement.write(94); //Don't move! (makes it smoother)
    
    if((currentRotation - degree) > 0)
      rotate.write(currentRotation - i);
    else
      rotate.write(currentRotation + i);
    delay(servoDelay);
  }
  
  rotate.write(degree);
  currentRotation = degree;
}

/*
func: tiltTo

desc: Tilts Wheatley's camera to the specified degree (absolute).

	Function exits if it does not receive a valid value as determined 
	by constants.
*/
void tiltTo(int degree){

  //Input constraint
  if (degree < minTiltAngle)
    return;
  if (degree > maxTiltAngle)
    return;

  int degreesToTilt = abs(currentTilt - degree);
  
  //Smooths the turn (makes it a little creepier too)  
  for(int i = 0; i < degreesToTilt; ++i){
    movement.write(94); //Don't move!    
    
    if((currentTilt - degree) > 0)
      tilt.write(currentTilt - i);
    else
      tilt.write(currentTilt + i);
    delay(servoDelay);
  }
  
  tilt.write(degree);
  currentTilt = degree;
}

/*
func: goRight
*HELPER FUNCTION*

desc: Moves Wheatley to the magnet to it's right. "Right" is as oriented
	when the camera is facing forward. 
*/
void goRight(){
  movement.write(103); //Move right past the 'current' magnet
  delay(1000);  
  
  //Light the led if the switch is activated *Probably not necessary*
  if(digitalRead(reedSwitch) == HIGH) 
    digitalWrite(led,LOW);
  else
    digitalWrite(led, HIGH);
  
  movement.write(103);  //Move right until switch
  delay(100);
  while(digitalRead(reedSwitch) == HIGH);  //Do nothing while the switch is high (active low)
 
  movement.write(100);  //Slow down slightly
  delay(100);
 
  movement.write(94);  //Stop
  digitalWrite(led, HIGH);
} 


/*
func: goLeft
*HELPER FUNCTION*

desc: Moves Wheatley to the magnet to it's left. "Left" is as oriented
	when the camera is facing forward. 
*/
void goLeft(){
  movement.write(85);  //Move left past the 'current' magnet
  delay(1000);  
  
  //Light the led if the switch is activated *Probably not necessary*
  if(digitalRead(reedSwitch) == HIGH)
    digitalWrite(led,LOW);
  else
    digitalWrite(led, HIGH);
  
  
  movement.write(85); //Move left until switch
  delay(100);
  while(digitalRead(reedSwitch) == HIGH); //Do nothing while the switch is high (active low)
 
  movement.write(88);  //Slow down slightly
  delay(100);
 
  movement.write(94);  //Stop
  digitalWrite(led, HIGH);
} 
