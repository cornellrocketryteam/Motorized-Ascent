
void setup(){  
  Serial.begin(115200); // begin serial with 115200 baud rate
  
  // confirm serial connection
  while (!Serial) {
    ;
  }

}

int incoming_byte = 0;
 
void loop(){
  
  if (Serial.available() > 0){
      incoming_byte = Serial.read();
      
      if (incoming_byte != 10){
        Serial.print("I received: ");
        Serial.println(incoming_byte, DEC);
      }
  }
}