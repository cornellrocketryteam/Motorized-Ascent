void setup() {
  Serial.begin(9600);

  pinMode(6, OUTPUT); // direction
  pinMode(7, OUTPUT); // pulse
  
  digitalWrite(6, LOW);

}

void loop() {
  digitalWrite(7,HIGH);
  delay(1);
  digitalWrite(7, LOW);
  delay(1);

}