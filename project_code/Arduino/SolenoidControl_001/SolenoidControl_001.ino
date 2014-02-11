int transistorPin = 3;

void setup(){
  pinMode( transistorPin, OUTPUT);
  Serial.begin(19200);
}

void loop(){
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    if (inChar == '0'){
      analogWrite( transistorPin, 0 );
    } else {
      analogWrite( transistorPin, 255 );
    }
  }
}
