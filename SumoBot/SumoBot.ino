/** MACKENZIE SCIENCE AND ENGINEERING OLYMPICS ROBOTICS TEAM -- SUMOBOT CODE (Horatiu Lazu) */

/* This is the constant for the front sensor */
const int frontSensor = 1;

/* These variables store the motor pins, and the enable pin for the H-Bridge */
const int motor1Forward = 5;
const int motor1Backward = 6;
const int motor2Forward = 7;
const int motor2Backward = 8;
const int enablePin = 9;

/* These are the variables for the left / right motors.
First index = power used for going forwards
Second index = power used for going backwards */
int motor1[2] = {0,0};
int motor2[2] = {0,0};

/* This variable stores the maximum distance that will be taken into consideration by the robot. */
const int MAX_DISTANCE_RANGE = 25;
/* This variable is the constant speed for going straight. */
const int FORWARD_SPEED = 80;
/* This is the variable for the non-dominant turning speed. Negative means it turns one wheel backwards while other forwards*/
const int NON_DOMINANT_TURNING_SPEED = -255;
/* This is the rotation speed. */
const int ROTATION_SPEED = 255;

/* This method sets up the pinMode */
void setup() {
    Serial.begin(9600);
    
    /* Setup the motor pins as output */
    pinMode(motor1Forward, OUTPUT);
    pinMode(motor1Backward, OUTPUT);
    pinMode(motor2Forward, OUTPUT);
    pinMode(motor2Backward, OUTPUT);
    
    /* Set the enable pin to output, and make it high */
    pinMode(enablePin, OUTPUT);
    digitalWrite(enablePin, HIGH); //active enable pin
    
    resetMotorSpeed();
}

/* This method converts the microsends to centimeters, by taking into consideration the speed of sound. */
long microsecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
}

/* This resets the motor speed */
void resetMotorSpeed(){
    motor1[0] = motor1[1] = motor2[0] = motor2[1] = 0;
}

/* This method updates the speed. */
void updateSpeed(){
    digitalWrite(motor1Forward, motor1[0]);
    digitalWrite(motor1Backward,motor1[1]);
    digitalWrite(motor2Forward,motor2[0]);
    digitalWrite(motor2Backward,motor2[1]);
}

/* This method lets the robot go forward. */
void goForward(int speedF){
    motor1[0] = motor2[0] = speedF;
    motor1[1] = motor2[1] = 0;
    updateSpeed();
}

/* This method lets you turn.*/
void turn(int rSpeed, int lSpeed){
    motor1[0] = lSpeed;
    motor1[1] = 0;
    motor2[0] = rSpeed;
    motor2[1] = 0;
    updateSpeed();
}

/* This is the rotation */
void rotate(){
    motor1[0] = motor2[1] = ROTATION_SPEED;
    motor1[1] =motor2[0] = 0;
    updateSpeed();
}

/* This method goes backwards */
void goBackwards(int speedB){
    motor1[0] = motor2[0] = 0;
    motor1[1] =  motor2[1] = speedB;
    updateSpeed();
}

/* This will get the ping from a sensor. */
int ping(){
    long duration, inches, cm;
    int pingPin = (1);
    
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);
    
    return microsecondsToCentimeters(duration);
}

/* This sees if the other robot is in the range. */
boolean withinAcceptableRange(){
    if (ping() <= MAX_DISTANCE_RANGE){
        return true;
    }
    return false;
}

/* Main method. This does the execution for the robot.*/
void loop() {
    if (withinAcceptableRange()){
        goForward(FORWARD_SPEED);
    }
    else{
        turn(NON_DOMINANT_TURNING_SPEED, ROTATION_SPEED);
    }
    delay(10); // update instructions every 10 ms.
}
