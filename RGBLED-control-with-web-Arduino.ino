#include <Wire.h>

#define LEDR 3
#define LEDG 6
#define LEDB 5

void turnoff(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
//  while (1 < Wire.available()) { // loop through all but the last
//    char c = Wire.read(); // receive byte as a character
//    Serial.print(c);         // print the character
//  }
//  int x = Wire.read();    // receive byte as an integer
//  if(x == 0){
//    digitalWrite(13,HIGH);
//  }
//  else if(x == 1){
//    digitalWrite(13,LOW);
//  }
//  Serial.println(x);         // print the integer

int red_color = Wire.read();
int green_color = Wire.read();
int blue_color = Wire.read();

Serial.print(red_color);
Serial.print(green_color);
Serial.println(blue_color);

  analogWrite(LEDR,red_color);
  analogWrite(LEDG,green_color);
  analogWrite(LEDB,blue_color);
}

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  turnoff();
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);           // start serial for output
}

void loop() {
  delay(100);
}
