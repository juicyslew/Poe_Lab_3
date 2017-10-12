#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const byte IR[2] = {A0, A1};
const int threshold = 500;
const byte cautiousness = 3;
const byte maxspd = 35;

long prev_t = 0;
int ir_val[2] = {100, 100};
String result = "";
//byte TapeRead = 0;
float Rspd;
float Lspd;
float spd[2] = {0, 0};

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *MotorR = AFMS.getMotor(1);
Adafruit_DCMotor *MotorL = AFMS.getMotor(2);

void setup() {
  // put your setup code here, to run once:
  pinMode(IR[0], INPUT);
  pinMode(IR[1], INPUT);
  AFMS.begin();
  Serial.begin(9600);
  MotorR->run(FORWARD);
  MotorL->run(FORWARD);
}

void loop() {
  // put your main code here, to run repeatedly:
  ir_val[0] = analogRead(IR[0]);
  ir_val[1] = analogRead(IR[1]);
  Rspd = max((threshold - ir_val[0])/cautiousness, 0);
  Lspd = max((threshold - ir_val[1])/cautiousness, 0);
  spd[0] = maxspd-min(Rspd,maxspd);
  spd[1] = maxspd-min(Lspd,maxspd);
  MotorR->setSpeed(spd[0]);
  MotorL->setSpeed(spd[1]);
  
  /*if (ir_val[0] < threshold){
    TapeRead += 1;
  }
  if (ir_val[1] < threshold){
    TapeRead += 2;
  }*/
  /*switch (TapeRead) { works
    case 2:
      //do something when var equals 1
      MotorR->setSpeed(40);
      MotorR->run(FORWARD);
      MotorL->setSpeed(0);
      MotorL->run(BACKWARD);
      break;
    case 1:
      //do something when var equals 2
      MotorR->setSpeed(0);
      MotorR->run(BACKWARD);
      MotorL->setSpeed(40);
      MotorL->run(FORWARD);
      break;
    case 3:
      MotorR->setSpeed(40);
      MotorR->run(FORWARD);
      MotorL->setSpeed(40);
      MotorL->run(FORWARD);
      break;
    default:
      MotorR->setSpeed(40);
      MotorR->run(FORWARD);
      MotorL->setSpeed(40);
      MotorL->run(FORWARD);
      // if nothing else matches, do the default
      // default is optional
    break;
  }*/
  result = result + ir_val[0] + "|" + ir_val[1] + "|" + spd[0] + "|" + spd[1];
  Serial.println(result);
  result = "";
  //TapeRead = 0;
}
