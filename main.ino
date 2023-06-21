#include <Mouse.h>
#include <Wire.h>
#include "I2Cdev/I2Cdev.h"
#include "MPU6050/MPU6050.h"

MPU6050 mpu;
int16_t ax,ay,az,gx,gy,gz;
int vx,vy;
int inputPin = 5;
bool enableMouse;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  enableMouse = true;
  pinMode(inputPin,INPUT);
  
  if (!mpu.testConnection()){
    while(1);
  }
  
  Serial.println("Running...");
  }


void loop() {
int val = digitalRead(inputPin);
if (val == HIGH){
  enableMouse = false;
}

else{
  enableMouse = true;
}

if (enableMouse){
  mpu.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
  vx = -(gy)/158;
  Mouse.move(vx,vy);
  delay(20);
}
}
