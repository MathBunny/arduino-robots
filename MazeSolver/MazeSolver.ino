/*
  Horatiu Lazu, Richard Dang & Eric Tseng
  Mr Wong
  June 8, 2015
  The purpose of this program is to assist in the simulation of a robot that utilizes a LDR sensor to traverse and return through a maze.
*/

/* This variable stores the analog port to get the LDR reading from. */
int LDR = A0;

/* This variable is used to store the pin for the LED.*/
int led = 2;

int upperRange = 1000; //this variable stores the upper range of the black
int lowerRange = 580; //this variable stores the lower range of the black

/* The follow are the pins. m1 is motor one, m2 is motor 2. Pin1 and Pin2 represent forward / backwards respectively. */
int m1Pin1 = 5;
int m1Pin2 = 6; // pin 7 on L293D
int m2Pin1 = 9; // pin 2 on L293D
int m2Pin2 = 10;
  
/* This variable is the speed of the robot. */
int speedG = 100;
  


/* This method sets up all of the inputs and outputs for the Arduino. */
void setup(){
  Serial.begin (9600); //turns on the Serial
  pinMode(LDR, INPUT); 
  pinMode(m1Pin1, OUTPUT);
  pinMode(m1Pin2, OUTPUT);
  pinMode(m2Pin1, OUTPUT);
  pinMode(m2Pin1, OUTPUT);
  pinMode(led, OUTPUT);
}

/* This method identifies if there is black detected. */
boolean isBlack(){
  if (inRange(getReading()))
     return true; //see if it's in the range. 
   return false;
}

/* This method verifies to see if the LDR's reading is within a range. */
boolean inRange(int a){
  if (a <= upperRange && a >= lowerRange){
      return true;
  }
  return false;
}

/* This method gets a reading from the LDR sensor. */
int getReading(){
 return analogRead(LDR); 
}

/* The purpose of this method is to ouptut the reading for the LDR.*/
void outputReading(){
  int reading = analogRead(LDR);
  Serial.print("LDR Reading: ");
  Serial.println(reading); 
  delay(10);
}

/* The purpose of this method is to go straight.  */
void goStraight(){
   analogWrite(m1Pin1, 0); // set pin 2 on L293D low
   analogWrite(m1Pin2,   speedG); // set pin 7 on L293D high
   
   analogWrite(m2Pin1, 0); // set pin 2 on L293D low
   analogWrite(m2Pin2, speedG); // set pin 7 on L293D high
}


/* The purpose of this method is to turn right. */
void goRight(){
   analogWrite(m1Pin1, 0); // set pin 2 on L293D low 25??
   analogWrite(m1Pin2,   0 ); // set pin 7 on L293D high
        
   analogWrite(m2Pin1, 0); // set pin 2 on L293D low
   analogWrite(m2Pin2,   speedG ); // set pin 7 on L293D high
    
}

/* The purpose of this method is to turn left.*/
void goLeft(){
   analogWrite(m1Pin1, 0); // set pin 2 on L293D low 
   analogWrite(m1Pin2, speedG); // set pin 7 on L293D high
        
   analogWrite(m2Pin1, speedG); // speedG WAS HERE...
   analogWrite(m2Pin2,    0); // set pin 7 on L293D high ZERO!!
    
}

/* This method executes continually in a loop. 
   Target logic: Turn left while on black, and turn right while on white.*/
void loop(){
  //outputReading();
 while(isBlack()){
     goLeft(); 
  }
  delay(50);
  while(!isBlack()){
     goRight(); //turn right at a speed of 100 (out of 255)
  }
  goStraight(); //go straight at a speed of 100
  delay(15); //allow time to go straight
}
