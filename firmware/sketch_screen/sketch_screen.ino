#include <IRremote.h>
#include <UTFT.h>
#include <UTouch.h>
#include <UTFT_Buttons.h>
#include <stdlib.h>

#define PRIVACY_TIME 1
#define DEFAULT_LR_POSITION 2
#define DEFAULT_ROT_POSITION 90
#define DEFAULT_TILT_POSITION 90


extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];

UTFT         myGLCD(ITDB32S,38,39,40,41);
UTouch       myTouch(6,5,4,3,2);
UTFT_Buttons myButtons(&myGLCD, &myTouch);



void setup(){
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.setFont(SmallFont);
  
  myTouch.InitTouch(PORTRAIT);
  myTouch.setPrecision(PREC_EXTREME);
  
  myButtons.setTextFont(BigFont);
  myButtons.setSymbolFont(Dingbats1_XL);
  
  myButtons.setButtonColors(0xFD20, VGA_WHITE, 0xFD20, VGA_RED, VGA_BLACK);
  
  Serial1.begin(9600);
}


void loop(){
  
  myGLCD.clrScr();
  
  int butDirections, butPrivacy, pressed_button;
  int short privacyTime = PRIVACY_TIME;
  char privateArray[5];
  
  butDirections = myButtons.addButton(10, 10, 220, 40, "Movement");
  butPrivacy = myButtons.addButton(10, 60, 220, 250, "PRIVACY!");
  myButtons.drawButtons();
  
  while(true){
    if (myTouch.dataAvailable() == true){
      
      pressed_button = myButtons.checkButtons();

      if(pressed_button == butDirections){
        
        myButtons.deleteAllButtons();
        directions();
        
        break;
      }
      else if(pressed_button == butPrivacy){
        
        Serial1.write(5);
        
        for(int i = privacyTime; i >= 0; i--){
          myButtons.relabelButton(butPrivacy, itoa(i, privateArray, 10), true);
          delay(1000);
        }
        
        Serial1.write(6);
        myButtons.relabelButton(butPrivacy, "PRIVACY!", true);
      }
    }
  }
}


void directions(){
  
  myGLCD.clrScr();
  
  int butLeftLR, butPositionLR, butRightLR, butLeftROT, butPositionROT, butRightROT, butDownTILT, butPositionTILT, butUpTILT, butBack, pressed_button;
  int short LR = DEFAULT_LR_POSITION;
  int short ROT = DEFAULT_ROT_POSITION;
  int short TILT = (DEFAULT_TILT_POSITION + 5);
  char LRArray[5], ROTArray[5], TILTArray[5];
  
  myGLCD.print("Move Left/Right", CENTER, 10);
  myGLCD.print("Rotate Left/Right", CENTER, 110);
  myGLCD.print("Tilt Up/Down", CENTER, 210);

  butPositionLR = myButtons.addButton(10, 30, 220, 30, itoa(LR, LRArray, 10));  
  butLeftLR = myButtons.addButton(10, 70, 105, 30, "<<");
  butRightLR = myButtons.addButton(125, 70, 105, 30, ">>");
  butPositionROT = myButtons.addButton(10, 130, 220, 30, itoa(ROT, ROTArray, 10));
  butLeftROT = myButtons.addButton(10, 170, 105, 30, "<<");
  butRightROT = myButtons.addButton(125, 170, 105, 30, ">>");
  butDownTILT = myButtons.addButton(10, 230, 50, 30, "Dwn");
  butPositionTILT = myButtons.addButton(70, 230, 100, 30, itoa((TILT - 5), TILTArray, 10));
  butUpTILT = myButtons.addButton(180, 230, 50, 30, "Up");
  butBack = myButtons.addButton(10, 280, 40, 30, "<");
  myButtons.drawButtons();
        
  while(true){
    if(myTouch.dataAvailable() == true){
      
      pressed_button = myButtons.checkButtons();
       
      if(pressed_button == butPositionLR){
        
        Serial1.write(LR);
      }
      else if(pressed_button == butLeftLR && LR > 1){
        
        LR--;
        myButtons.relabelButton(butPositionLR, itoa(LR, LRArray, 10), true);
      }
      else if(pressed_button == butRightLR && LR < 3){
        
        LR++;
        myButtons.relabelButton(butPositionLR, itoa(LR, LRArray, 10), true);
      }
      else if(pressed_button == butPositionROT){
        
        Serial1.write(ROT);
      }
      else if(pressed_button == butLeftROT && ROT > 10){
        
        ROT -= 10;
        myButtons.relabelButton(butPositionROT, itoa(ROT, ROTArray, 10), true);
      }
      else if (pressed_button == butRightROT && ROT < 170){
        
        ROT += 10;
        myButtons.relabelButton(butPositionROT, itoa(ROT, ROTArray, 10), true);
      }
      else if(pressed_button == butDownTILT && TILT > 15){
        
        TILT -= 10;
        myButtons.relabelButton(butPositionTILT, itoa((TILT - 5), TILTArray, 10), true);
      }
      else if(pressed_button == butPositionTILT){
        
        Serial1.write(TILT);
      }
      else if(pressed_button == butUpTILT && TILT < 115){
        
        TILT += 10;
        myButtons.relabelButton(butPositionTILT, itoa((TILT - 5), TILTArray, 10), true); 
      }
      else if(pressed_button == butBack){
        
        myButtons.deleteAllButtons();
        break;
      }
    }
  }
}

