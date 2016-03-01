#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#include <MeMCore.h>

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double d;
MeUltrasonicSensor ultrasonic_3(3);
MBotDCMotor motor(0);



void setup(){
    
}

void loop(){
    
    d = ultrasonic_3.distanceCm();
    if((ultrasonic_3.distanceCm()) < (20)){
        motor.move(1,100);
    }else{
        motor.move(4,100);
    }
    
}

