// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(3);
int pos = 0;    // variable to store the servo position
int bpm = 30;
int pot = 0;
float travelTime; // = 1000;
float travelDistance = 46; //1.811 inch = 46mm = max speed
//Calibrate to hit desired ambu ball pressure ^
float travelSpeed; // = 255;
float itime = 0;
float etime = 0;
bool forward = true;
char endOfPacketMarker = ' ';
String input = "";

void setup() {
  Serial.begin(9600);           // set up Serial at 9600 bauds
  Serial.println('a'=='a');
  Serial.println("Input bpm"); //Wait for BPM input
  while(Serial.available() == 0){}
  if(Serial.available() > 0)
  {
    input = Serial.readStringUntil('*');
    bpm = input.toInt();  //Test this!!
    Serial.println("BPM set to: " + input);
    Serial.flush();
  }
  Serial.read();

  // turn on motor
  motor.setSpeed(255);
 
  motor.run(RELEASE);
  Serial.println("BPM set to: " + bpm);
  //v = d/t
  travelTime = 30.0/bpm * 1000.0; //millisecods
  Serial.println("TravelTime : " + String(travelTime)); //TODO: MAP THIS ALSO? OR SOMEHOW CONSTRAIN IN THE EVENT THAT SPEED IS CONSTRAINED/CHANGED 
  travelSpeed = travelDistance / (travelTime / 1000.0); //max rated speed is 46 mm/s
  Serial.println("UNMAPPED : " + String(travelSpeed));
  //travelSpeed = constrain(travelSpeed, 0, 46);
  travelSpeed = mapfloat(travelSpeed, 0, 46, 0, 255); //Scale from mm/s to 0-255
  Serial.println("MAPPED : " + String(travelSpeed));
  float oldSpeed = travelSpeed; //Check if constrain changes speed, then alert user
  travelSpeed = constrain(travelSpeed, 0, 255);
  if(oldSpeed != travelSpeed){
    Serial.println("Invalid Speed, Setting it to : " + String(mapfloat(travelSpeed, 0, 255, 0, 46)) + "mm/s");
  }
  motor.setSpeed(travelSpeed);
  //while(true){Serial.println(travelTime); Serial.println((30.0/31.0));} //Debug Loop
  //KEEP IN MIND WHICH CODE WILL GET AFFECTED BY CHANGING TRAVELDISTANCE: 
  //HARDCODED CONSTRAINTS AND MAPS, MAX SPEED CONSIDERATIONS, MAX TRAVELTIME, BUGS THAT DON'T ALLOW BPM OVER 30
}

void loop() { 
  Serial.println("Looping");
  Serial.println("TravelTime : " + String(travelTime));
  Serial.println("MAPPED : " + String(travelSpeed));
  Serial.println("UNMAPPED : " + String(travelDistance / (travelTime / 1000.0)));
  if(forward){
    motor.run(FORWARD);
    //Serial.println("forward");
    //delay(travelTime);
    delay(travelTime);
    forward = false;
  }else{
    motor.run(BACKWARD);
    //Serial.println("back");
    //delay(travelTime);
    delay(travelTime);
    forward = true;
  }
}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

