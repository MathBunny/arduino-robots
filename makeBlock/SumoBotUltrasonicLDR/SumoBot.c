#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#include <MeMCore.h>

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
MePort lightsensor_6(6);
MBotDCMotor motor(0);
MeUltrasonicSensor ultrasonic_3(3);



void setup(){
    
}

void loop(){
    
    if((lightsensor_6.aRead2()) < ( 100 )){
        motor.move(4,100);
    }else{
        if((ultrasonic_3.distanceCm()) < (20)){
            motor.move(1,100);
        }else{
            motor.move(4,100);
        }
    }
    
}

