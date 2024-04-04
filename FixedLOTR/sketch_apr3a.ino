#include <Servo.h>
const int rain_sensor_pin = 2;
const int buzzer_pin = 3;
Servo esc_1;
Servo esc_2;
int power = 0;
bool testing = true;

void setup() {
  pinMode(rain_sensor_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);  
  esc_1.attach(10);
  esc_2.attach(11);
  Serial.begin(9600);
}

void kys() {
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
  digitalWrite(buzzer_pin, HIGH);
  if (testing) {
    delay(2000);
    digitalWrite(buzzer_pin, LOW);
  }
  while (true) {/*infinite loop*/}
}

bool check_stop() {
  int is_rain = digitalRead(rain_sensor_pin);
  if (is_rain != HIGH) {
    Serial.println("WET");
    return true;
  } else {
    Serial.println("DRY");
  }
  return false;
}

void loop() {
  //ch1
  //SaLP();
  //ch2
  to_isengard(10000, 50);
  //ch3
  find_you_a_box(5000, 5000, 5000, 25, 1000);
  //ch4
  into_the_mines(5000, 7000, 10000, 25, 1000);
  //ch5
  show_us_the_meaning_of_haste(5000);
  
  balrog();
}

void SaLP() {
  while (!check_stop()) {}
  kys();
  return;
}

void to_isengard(int travel_time, int top_speed) {
  go_forward(travel_time, top_speed);
  return;
}

void find_you_a_box(int initial, int middle, int end, int speed, int turn_time) {
  go_forward(initial, speed);
  turn_right(turn_time);
  go_forward(middle, speed);
  turn_left(turn_time);
  go_forward(end, speed);
  return;
}

void into_the_mines(int initial, int middle, int end, int speed, int turn_time) {
  go_forward(initial, speed);
  turn_right(turn_time);
  go_forward(middle, speed);
  turn_left(turn_time);
  go_forward(end, speed);
  return;
}

void show_us_the_meaning_of_haste(int time) {
  set_esc_power(esc_1, 100);
  set_esc_power(esc_2, 100);
  steady(100, time);
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
}

void balrog() {
  bool gandalf = true;
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
  while (gandalf) {/* you shall not pass */}
}

void turn_right(int time) {
  Serial.print("turning right");
  set_esc_power(esc_1, 50);
  set_esc_power(esc_2, -25);
  delay(time);
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
}

void turn_left(int time) {
  Serial.print("turning left");
  set_esc_power(esc_1, -25);
  set_esc_power(esc_2, 50);
  delay(time);
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
}

void accelerate(int max, int inc) {
  for (power = 0; power < max; power += inc) {
    set_esc_power(esc_1, power);
    set_esc_power(esc_2, power);
    delay(20);

    if (check_stop()) {
      kys();
    }
  }
}

void brake(int starting, int inc) {
  for (power = starting; power > 0; power -= inc) {
    set_esc_power(esc_1, power);
    set_esc_power(esc_2, power);
    delay(20);

    if (check_stop()) {
      kys();
    }                    
  }
}

void go_forward(int time, int top_speed) {
  accelerate(top_speed, 5);
  steady(top_speed, time);
  brake(top_speed, 5);
}

void steady(int inc, int duration) {
  for (int i = 0; i < duration; i += inc) {
    delay(inc);
    if (check_stop()) {
      kys();
    }   
  }
}

void set_esc_power(Servo esc, int power) {
  power = constrain(power, -100, 100);
  int signal_min = 1050;
  int signal_max = 1950;
  int signal_output = map(power, -100, 100, signal_min, signal_max); //map(value, fromLow, fromHigh, toLow, toHigh)
  esc.writeMicroseconds(signal_output);
}