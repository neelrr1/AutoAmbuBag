// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(3);
int pos = 0;    // variable to store the servo position
int bpm = 30;
int pot = 0;
int travelTime = 900;
float itime = 0;
float etime = 0;
bool goIn = true;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(255);
 
  motor.run(RELEASE);
  if(goIn){motor.run(BACKWARD);}
  else{motor.run(FORWARD);}
  delay(10000);
}

void loop() { 
  
}
