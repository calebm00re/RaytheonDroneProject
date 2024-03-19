#include <Servo.h>

Servo esc_1;  // create servo object to control the PWM signal
Servo esc_2;
int power = 0;

void setup() {
  esc_1.attach(10);  // make sure to use a PWM capable pin
  esc_2.attach(11);
}

void loop() {
  // we are starting at 0 to avoid the motor jumping and then going up to 100% forward
  // with a delay of 20 milliseconds and 100 steps, this for loop will take 2 seconds to complete
  for (power = 0; power < 50; power += 1) {
    set_esc_power(esc_1, power);
    set_esc_power(esc_2, power);
    delay(20);
  }

   delay(5000);
  
  
  // now we will go from 100% forward to 0 (stopped)
  // with a delay of 20 milliseconds and 100 steps, this for loop will take 2 seconds to complete
  for (power = 50; power > 0; power -= 1) {
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
