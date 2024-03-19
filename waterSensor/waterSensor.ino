const int rainSensorPin = 2; // water sensor connected to pin 2
const int buzzerPin = 3;     // buzzer connected to pin 3

void setup() {
  pinMode(rainSensorPin, INPUT); // set rain sensor pin as input
  pinMode(buzzerPin, OUTPUT);    // set buzzer pin as output
  Serial.begin(9600);            // initialize serial communication at 9600 baud rate
  Serial.println("running");
}

void loop() {
  int isRain = digitalRead(rainSensorPin); // read the state of the rain sensor
  Serial.println("running");
  while (isRain == HIGH) {  // while no rain is detected
    Serial.println("nope");
    isRain = digitalRead(rainSensorPin); // update rain sensor reading
  }

  digitalWrite(buzzerPin, HIGH); // turn on the buzzer
  Serial.println("water sensed");
  delay(1000);                    // wait for 1 second
  digitalWrite(buzzerPin, LOW);  // turn off the buzzer
}
