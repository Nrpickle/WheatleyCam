#include <IRremote.h>

int input;
IRsend irsend;

void setup(){

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop(){

  if(Serial1.available()){

    input = Serial1.read();
    Serial.print(input);

    switch(input){

    case 1:
      for(int i = 0; i < 3; i++){
        irsend.sendNEC(0x10EF001, 32);
      }
      break;
    case 2:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0002, 32);
      }
      break;
    case 3:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0003, 32);
      }
      break;
    case 5:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0005, 12);
      } 
      break;
    case 6:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0006, 12);
      }
      break;
    case 10:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF000A, 12);
      }
      break;
    case 15:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF000F, 12);
      }
      break;
    case 20:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0014, 12);
      }
      break;
    case 25:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0019, 12);
      }
      break;
    case 30:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF001E, 12);
      }
      break;
    case 35:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0023, 12);
      }
      break;
    case 40:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0028, 12);
      }
      break; 
    case 45:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF002D, 12);
      }
      break;
    case 50:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0032, 12);
      }
      break;
    case 55:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0037, 12);
      }
      break;
    case 60:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF003C, 12);
      }
      break;   
    case 65:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0065, 12);
      }
      break;
    case 70:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0046, 12);
      }
      break;
    case 75:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF004B, 12);
      }
      break;
    case 80:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0050, 12);
      }
      break;
    case 85:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0055, 12);
      }
      break;
    case 90:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF005A, 12);
      }
      break;
    case 95:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF005F, 12);
      }
      break;
    case 100:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0064, 12);
      }
      break;
    case 105:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0069, 12);
      }
      break;
    case 110:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF006E, 12);
      }
      break;
    case 115:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0073, 12);
      }
      break;
    case 120:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0078, 12);
      }
      break;
    case 130:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0082, 12);
      }
      break;
    case 140:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF008C, 12);
      }
      break;
    case 150:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF0096, 12);
      }
      break;
    case 160:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF00A0, 12);
      }
      break;
    case 170:
      for(int i = 0; i < 3; i++){
        irsend.sendSony(0x10EF00AA, 12);
      }
      break;

    }
  }
  delay(1000);
}

