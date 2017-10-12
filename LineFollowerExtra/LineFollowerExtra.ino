#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const byte IR[2] = {A0, A1};
const int threshold = 400;
const byte cautiousness = 3;
const byte maxspd = 40;

long prev_t = 0;
int ir_val[2] = {100, 100};
String result = "";
//byte TapeRead = 0;
float Rspd;
float Lspd;
float Rospd;
float Lospd;

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
  
  Rspd = maxspd-min(max((threshold - ir_val[0])/cautiousness, 0),maxspd);
  Lspd = maxspd-min(max((threshold - ir_val[1])/cautiousness, 0),maxspd);
  
  MotorR->setSpeed((Rspd + Rospd)/2);
  MotorL->setSpeed((Lspd + Lospd)/2);
  
  Rospd = Rspd;
  Lospd = Lspd;
  
  result = result + ir_val[0] + "|" + ir_val[1];
  Serial.println(result);
  result = "";
}
