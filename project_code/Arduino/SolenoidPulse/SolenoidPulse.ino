int transistorPin = 3;
int rate = 10;
int spacing = 5000;

void setup(){
  pinMode( transistorPin, OUTPUT);
  Serial.begin(19200);
}

void loop(){
  analogWrite( transistorPin, 255 );
  delay(rate);
  analogWrite( transistorPin, 0 );
  delay(spacing);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    if (inChar == '0'){
      rate = 10;
      spacing = 500;
    } else if (inChar == '1'){
      rate = 100;
      spacing = 500;
    } else if (inChar == '2'){
      rate = 500;
      spacing = 500;
    } else if (inChar == '3'){
      rate = 1000;
      spacing = 500;
    }
  }
}
