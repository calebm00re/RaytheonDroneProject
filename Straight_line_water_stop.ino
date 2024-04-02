#include <Servo.h>
const int rainSensorPin = 2; // water sensor connected to pin 2
const int buzzerPin = 3;     // buzzer connected to pin 3
Servo esc_1;  // create servo object to control the PWM signal
Servo esc_2;
int power = 0;


void setup() {
  pinMode(rainSensorPin, INPUT); // set rain sensor pin as input
  pinMode(buzzerPin, OUTPUT);    // set buzzer pin as output
  Serial.begin(9600);            // initialize serial communication at 9600 baud rate
  Serial.println("running");
  esc_1.attach(10);  // make sure to use a PWM capable pin
  esc_2.attach(11);
}

void kys() {
  Serial.print("entering kys loop");
  set_esc_power(esc_1, 0);
  set_esc_power(esc_2, 0);
  digitalWrite(buzzerPin, HIGH);
  delay(2000);
  digitalWrite(buzzerPin, LOW);
  while (true) {}
}

bool checkStop() {
  int isRain = digitalRead(rainSensorPin);
  if (isRain != HIGH) {
    Serial.println("WET");
    return true;
  } else {
    Serial.println("DRY");
  }
  return false;
}

void acc(int max, int inc) {
  for (power = 0; power < max; power += inc) {
    set_esc_power(esc_1, power);
    set_esc_power(esc_2, power);
    delay(20);

    if (checkStop()) {
      kys();
    }
  }
}

void deacc(int starting, int inc) {
  for (power = starting; power > 0; power -= inc) {
    set_esc_power(esc_1, power);
    set_esc_power(esc_2, power);
    delay(20);

    if (checkStop()) {
      kys();
    }                    
  }
}
void steady(int inc, int duration) {
  for (int i = 0; i < duration; i += inc) {
    delay(inc);
    Serial.println(checkStop());
    if (checkStop()) {
      kys();
    }   
  }
}

void loop() {
  acc(50,5);
  steady(50, 10000);
  deacc(50,5);
}

void set_esc_power (Servo esc, int power){
  power = constrain(power, -100, 100);
  int signal_min = 1050;
  int signal_max = 1950;
  int signal_output = map(power, -100, 100, signal_min, signal_max); //map(value, fromLow, fromHigh, toLow, toHigh)
  esc.writeMicroseconds(signal_output);
}
