// Wheatley Cam Basic movement firmware
// Nick McComb
// [mccombn@onid.oregonstate.edu]

//WheatleyRobotics


//Limit switches
//Green is white D1 Right
//Orange is left D0 Left

#include <Servo.h> 
#include <IRremote.h>

Servo movement;
Servo rotate;  
Servo tilt;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 

int led = 11;                 //A10
int reedSwitch = 13;          //B4
int RECV_PIN = 10;            //C7
int PRIVATE_PIN = 14;         //A7
const short tiltPin = 20;     //F1
const short rotatePin = 21;   //F0
const short movementPin = 19; //F4


const short rightLimit = 6;   //D1 yellow/green
const short leftLimit = 5;    //D0 yellow/orange

IRrecv irrecv(RECV_PIN);
decode_results results;

//Amount of time to be private when using sparkfun remote (seconds)
int privacyTime = 10;

//Motor speed (difference from 94 stop position, so about at max right now)
const int motorSpeed = 70;

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
  
  Serial.begin(9600);
  
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
  
  pinMode(PRIVATE_PIN, OUTPUT);
  /* END TEENSY */

  movement.write(88);

  //Initial calibrate (find where it is)
    while(!digitalRead(leftLimit)){
      digitalWrite(led, HIGH);
    }
  digitalWrite(led, LOW);
  movement.write(94);  //Stop moving
  goRight();
  currentPos = 1;
  
  //Enable IR receiver
  irrecv.enableIRIn();
  
  Serial.begin(9600);
} 

int alt = 0;


//loops cases overlook:

//	1: possition 1
//	2: possition 2
//	3: possition 3
//	5: unknown, need to look into
//	6: unknown, need to look into
//	0's: Rotates Camera
//	5's: Tilts Camera
char input;
void loop() 
{ 
   if(Serial.available()){

    input = Serial.read();
    //Serial.print(input);

    switch(input){

    case 1:
	  moveToPos(input);
      break;
    case 2:
	  moveToPos(input);
      break;
    case 3:
	  moveToPos(input);
      break;
    case 5:
      // NEED TO IMPLAMENT
      break;
    case 6:
      // NEED TO IMPLAMENT
      break;
    case 10:
	  rotateTo(input);
      break;
    case 15:
      tiltTo(input);
      break;
    case 20:
      rotateTo(input);
      break;
    case 25:
      tiltTo(input);
      break;
    case 30:
      rotateTo(input);
      break;
    case 35:
      tiltTo(input);
      break;
    case 40:
      rotateTo(input);
      break; 
    case 45:
      tiltTo(input);
      break;
    case 50:
      rotateTo(input);
      break;
    case 55:
      tiltTo(input);
      break;
    case 60:
      rotateTo(input);
      break;   
    case 65:
      tiltTo(input);
      break;
    case 70:
      rotateTo(input);
      break;
    case 75:
      tiltTo(input);
      break;
    case 80:
      rotateTo(input);
      break;
    case 85:
      tiltTo(input);
      break;
    case 90:
      rotateTo(input);
      break;
    case 95:
      tiltTo(input);
      break;
    case 100:
      rotateTo(input);
      break;
    case 105:
      tiltTo(input);
      break;
    case 110:
      rotateTo(input);
      break;
    case 115:
      tiltTo(input);
      break;
    case 120:
      rotateTo(input);
      break;
    case 130:
      rotateTo(input);
      break;
    case 140:
      rotateTo(input);
      break;
    case 150:
      rotateTo(input);
      break;
    case 160:
      rotateTo(input);
      break;
    case 170:
      rotateTo(input);
      break;

    }
  }

  if(irrecv.decode(&results)){

    Serial.println(results.value, HEX);
    
    
    switch(results.value){

    //Sparkfun remote0 cases
    case 0x10EFF807:
      moveToPos(1);
      break;
    case 0x10EF7887:
      moveToPos(2);
      break;
    case 0x10EF58A7:
      moveToPos(3);
      break;
    case 0x10EFD827:
      digitalWrite(PRIVATE_PIN, HIGH);
      for(int i = 0; i < privacyTime; i++)
        delay(1000);
      digitalWrite(PRIVATE_PIN, LOW);
      break;
    case 0x10EF10EF:
      rotateTo(currentRotation - 10);
      break;
    case 0x10EF807F:
      rotateTo(currentRotation + 10);
      break;
    case 0x10EF00FF:
      tiltTo(currentTilt - 10);
      break;
    case 0x10EFA05F:
      tiltTo(currentTilt + 10);
      break;
    case 0x10EF20DF:
      rotateTo(90);
      tiltTo(90);
      break;
      
      
    //Touch remote cases
    case 0x10EF0001:
      moveToPos(1);
      break;
    case 0x10EF0002:
      moveToPos(2);
      break;
    case 0x10EF0003:
      moveToPos(3);
      break;
    case 0x10EF0005:
      digitalWrite(PRIVATE_PIN, HIGH);
      break;
    case 0x10EF0006:
      digitalWrite(PRIVATE_PIN, LOW);
      break;
    case 0x10EF000A:
      rotateTo(10);
      break;
    case 0x10EF000F:
      tiltTo(10);
      break;
    case 0x10EF0014:
      rotateTo(20);
      break;
    case 0x10EF0019:
      tiltTo(20);
      break;
    case 0x10EF001E:
      rotateTo(30);
      break;
    case 0x10EF0023:
      tiltTo(30);
      break;
    case 0x10EF0028:
      rotateTo(40);
      break;
    case 0x10EF002D:
      tiltTo(40);
      break;
    case 0x10EF0032:
      rotateTo(50);
      break;
    case 0x10EF0037:
      tiltTo(50);
      break;
    case 0x10EF003C:
      rotateTo(60);
      break;
    case 0x10EF0041:
      tiltTo(60);
      break;
    case 0x10EF0046:
      rotateTo(70);
      break;
    case 0x10EF004B:
      tiltTo(70);
      break;
    case 0x10EF0050:
      rotateTo(80);
      break;
    case 0x10EF0055:
      tiltTo(80);
      break;
    case 0x10EF005A:
      rotateTo(90);
      break;
    case 0x10EF005F:
      tiltTo(90);
      break;
    case 0x10EF0064:
      rotateTo(100);
      break;
    case 0x10EF0069:
      tiltTo(100);
      break;
    case 0x10EF006E:
      rotateTo(110);
      break;
    case 0x10EF0073:
      tiltTo(110);
      break;
    case 0x10EF0078:
      rotateTo(120);
      break;
    case 0x10EF0082:
      rotateTo(130);
      break;
    case 0x10EF008C:
      rotateTo(140);
      break;
    case 0x10EF0096:
      rotateTo(150);
      break;
    case 0x10EF00A0:
      rotateTo(160);
      break;
    case 0x10EF00AA:
      rotateTo(170);
      break;
    }
    
    irrecv.resume();
  }
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
  movement.write(94 + motorSpeed); //Move right past the 'current' magnet
  delay(1000);  

  //Light the led if the switch is activated *Probably not necessary*
  if(digitalRead(reedSwitch) == HIGH) 
    digitalWrite(led,LOW);
  else
    digitalWrite(led, HIGH);


  //Prev 103
  movement.write(170);  //Move right until switch
  delay(100);
  while(digitalRead(reedSwitch) == HIGH);  //Do nothing while the switch is high (active low)

  movement.write(94 + 6);  //Slow down slightly
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
  movement.write(94 - motorSpeed);  //Move left past the 'current' magnet
  delay(1000);  

  //Light the led if the switch is activated *Probably not necessary*
  if(digitalRead(reedSwitch) == HIGH)
    digitalWrite(led,LOW);
  else
    digitalWrite(led, HIGH);


  movement.write(94 - motorSpeed); //Move left until switch
  delay(100);
  while(digitalRead(reedSwitch) == HIGH); //Do nothing while the switch is high (active low)

  movement.write(88);  //Slow down slightly
  delay(100);

  movement.write(94);  //Stop
  digitalWrite(led, HIGH);
} 

