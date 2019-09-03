#define FORWARD D5
#define BACKWARD D6
#define S_BUTTON D1
#define D_BUTTON D0
#define FAST (1024 - 1)
#define SLOW FAST/2
#define OFF 0
#define debounce_delay 50
#define change_speed digitalRead(S_BUTTON)
#define change_direction digitalRead(D_BUTTON)
int speeds[3] = {OFF, SLOW, FAST};
int directions[2] = {FORWARD, BACKWARD};
int speed_i = 0;
int direction_i = 0;

/* need to work on the debouncing thing
 * and need to fix the all off thing
 */

void setup() {
  // initialize pins for output
  pinMode(FORWARD, OUTPUT);
  pinMode(BACKWARD, OUTPUT);
  pinMode(S_BUTTON, INPUT);
  pinMode(D_BUTTON, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  if (change_speed || change_direction){
    delay(15);
    //Serial.println("Button pressed.");
    if (change_speed && !change_direction){
      Serial.println("CHANGE SPEED");
      speed_i = (speed_i + 1)%3;
    }
    if (change_direction && !change_speed){
      Serial.println("CHANGE DIRECTION");
      direction_i = (direction_i + 1)%2;
    }
    while (change_speed || change_direction){
      if (change_direction && change_speed){
        Serial.println("STOP ALL");
        speed_i = 0;
      }
      go(directions[direction_i],speeds[speed_i]);
    }
    //Serial.println("Button released.");
    //Serial.print("DIRECTION: ");
    //Serial.println(directions[direction_i]);
    //Serial.print("SPEED: ");
    //Serial.println(speeds[speed_i]);
  }
}

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

void go_forward(int speed){
  analogWrite(BACKWARD, OFF);
  analogWrite(FORWARD, speed);
}

void go_backward(int speed){
  analogWrite(FORWARD, OFF);
  analogWrite(BACKWARD, speed);
}
