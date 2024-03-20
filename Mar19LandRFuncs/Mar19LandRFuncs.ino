#include <Servo.h>

Servo esc_1;  // create servo object to control the PWM signal
Servo esc_2;
int power = 0;

void setup() {
  esc_1.attach(10);  // make sure to use a PWM capable pin
  esc_2.attach(11);
}

void loop() {
  // put your main code here, to run repeatedly:
  turnright();
  delay(2500);
  turnleft();
  delay(2500);

}

void turnright(){
  for (power = 0; power < 25; power += 5) {
    set_esc_power(esc_1, power);
    set_esc_power(esc_2, power);
    delay(20);
  }

  set_esc_power(esc_1, 50);
  set_esc_power(esc_2, -25);
  delay(600);
  //  delay(5000);
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
  delay(5000);
}

void turnleft(){
  for (power = 0; power < 25; power += 5) {
    set_esc_power(esc_1, power);
    set_esc_power(esc_2, power);
    delay(20);
  }

  set_esc_power(esc_1, -25);
  set_esc_power(esc_2, 50);
  delay(600);
  //  delay(5000);
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
  delay(5000);
}

void set_esc_power (Servo esc, int power){
  power = constrain(power, -100, 100);
  int signal_min = 1050;
  int signal_max = 1950;
  int signal_output = map(power, -100, 100, signal_min, signal_max); //map(value, fromLow, fromHigh, toLow, toHigh)
  esc.writeMicroseconds(signal_output);
}