void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

int toggle = 0;
char incomingByte = 0;

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    
    Serial.print("I recieved: ");
    Serial.println(incomingByte);
    
    if(incomingByte == 'b')
      digitalWrite(13, HIGH);
    else if(incomingByte == 'o')
      digitalWrite(13, LOW);
  }
  
  delay(50);
}
