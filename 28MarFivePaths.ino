#include <Servo.h>

Servo esc_1;  // create servo object to control the PWM signal
Servo esc_2;
int power = 0;

void setup() {
  esc_1.attach(10);  // make sure to use a PWM capable pin
  esc_2.attach(11);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //THESE FUNCTIONS ALL WORK
  //just uncomment what you need, numbers may need adjustment on a football field

  //ch1
  SalLP();
  //ch2
  straight(5000);
  //ch3
  LShape(5000);
  //ch4
  laneSwap(5000, 2500);
  //ch5
  randomBonus();

}

//Challenge 1, Sit and Look Pretty
/*
hold their position
for the duration of the challenge run (i.e., stay stationary with no evasive maneuvers).
*/
void SaLP(){
  //water checking logic
  return;
}

//Challenge 2, Straight Line
/*
The UGV will
traverse the field following a straight line staying without evasive maneuvers at a speed
configurable (expected: ~12 seconds per yard or ~0.17 MPH (~13 seconds / meter)).
*/

void straight(int forward){
  goForward(forward);
  return;
}

//Challenge 3, Lshape 
/*
At a time designated by the swim lane, each UGV will
make a 90 degree turn to the right, move forward 2 yards, then a 90 degree turn to the left and
then maintain a straight course until crossing the finish line.

Forward is how long until we need to turn
*/
void LShape(int forward){
  goForward(forward);
  delay(1000);
  turnright(750);
  goForward(1000);
  delay(1000);
  turnleft(750);
  goForward(forward);
  return;
}

//Challenge 4, Lane Swap
/*
The UGVs
will start to make a straight vector without evasive maneuvers across the field at a high
configurable (expected: ~4.05 seconds per yard or ~0.49MPH) speed. At a pre-determined
time, in accordance with table 1, each UGV will swap routes with another UGV by making two
90 degree turns.
*/

void laneSwap(int forward, int laneSwap){
  goForward(forward);
  delay(1000);
  turnright(750);
  goForward(laneSwap);
  delay(1000);
  turnleft(750);
  goForward(forward);
  return;
}


//Challenge 5, Bonus Random
/*
Each UGV will take a random path across the field while avoiding all other UGVs.
*/

void randomBonus(int forward){
  //implement later
}

//give it how long you want to run in a straight line
//will go forward and stop
void goForward(int time){
  accelerate(50);
  delay(time);
  brake(50);
}

void turnright(int time){
  Serial.print("turning right");
  set_esc_power(esc_1, 50);
  set_esc_power(esc_2, -25);
  delay(time);
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
}

void turnleft(int time){
  Serial.print("turning left");
  set_esc_power(esc_1, -25);
  set_esc_power(esc_2, 50);
  delay(time);
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
}

//helpers for going forward
//accept speed that we want (depends on which challege [hella slow {like 13 sec / meter}])
void accelerate(int speed){
  for (power = 0; power < speed; power += 1) {
    set_esc_power(esc_1, power);
    set_esc_power(esc_2, power);
    delay(20);
  }
}

//accept speed we are at
void brake(int speed){
  for (power = speed; power > 0; power -= 1) {
    set_esc_power(esc_1, power);
    set_esc_power(esc_2, power);
    delay(20);                       
  }
}

void set_esc_power (Servo esc, int power){
  power = constrain(power, -100, 100);
  int signal_min = 1050;
  int signal_max = 1950;
  int signal_output = map(power, -100, 100, signal_min, signal_max); //map(value, fromLow, fromHigh, toLow, toHigh)
  esc.writeMicroseconds(signal_output);
}