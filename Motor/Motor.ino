/*
* Created by Hannah Mason
* on 8/30/2019
* for EECE 4263 Lab 02
*/

//#define DEBUG

// Constants for speed, direction, and button pins
#define FORWARD D5
#define BACKWARD D6
#define SPEED_BUTTON D1
#define DIRECTION_BUTTON D0
#define FAST (1024 - 1)
#define SLOW FAST/2
#define OFF 0

// Using functions instead of variables so that
// the value is updated each time its called
#define change_speed digitalRead(SPEED_BUTTON)
#define change_direction digitalRead(DIRECTION_BUTTON)

// Making lists of all possible speeds and directions
// and indexes to keep track of the current ones
// (Simpler than a bunch of if/else or switch statements)
int speeds[3] = {OFF, SLOW, FAST};
int directions[2] = {FORWARD, BACKWARD};
int speed_i = 0;
int direction_i = 0;

void setup() {
  // initialize pins for output and input
  pinMode(FORWARD, OUTPUT);
  pinMode(BACKWARD, OUTPUT);
  pinMode(SPEED_BUTTON, INPUT);
  pinMode(DIRECTION_BUTTON, INPUT);
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
}

// the loop function runs over and over again forever
void loop() {
  if (change_speed || change_direction){
    delay(15);
    //Serial.println("Button pressed.");
    if (change_speed && !change_direction){
      #ifdef DEBUG
      Serial.println("CHANGE SPEED");
      #endif
      speed_i = (speed_i + 1)%3;
    }
    if (change_direction && !change_speed){
      #ifdef DEBUG
      Serial.println("CHANGE DIRECTION");
      #endif
      direction_i = (direction_i + 1)%2;
    }
    while (change_speed || change_direction){
      if (change_direction && change_speed){
        #ifdef DEBUG
        Serial.println("STOP ALL");
        #endif
        speed_i = 0;
        direction_i = 0;
      }
      // inside the while loop so that updates are near immediate
      go(directions[direction_i],speeds[speed_i]); 
    }
  }
}

//the general GO function
void go(int direction, int speed){
  if (direction == FORWARD){
    go_forward(speed);
  }
  else if (direction == BACKWARD){
    go_backward(speed);
  }
  else{
    analogWrite(BACKWARD, OFF);
    analogWrite(FORWARD, OFF);
  }
}

// handle the specific directions to ensure
// both direction pins aren't high at the same time
void go_forward(int speed){
  analogWrite(BACKWARD, OFF);
  analogWrite(FORWARD, speed);
}

void go_backward(int speed){
  analogWrite(FORWARD, OFF);
  analogWrite(BACKWARD, speed);
}
