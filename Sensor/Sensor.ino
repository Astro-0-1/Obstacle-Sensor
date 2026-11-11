const int trigPin = 9;     // sends the ping
const int echoPin = 10;    // listens for the echo
const int ledPin = 13;     // built-in LED

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  long duration, inches, cm;

  // send the ping (HC-SR04 needs a 10 microsecond HIGH pulse)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // listen for the echo (stop waiting after 30000 us = about 5 meters)
  duration = pulseIn(echoPin, HIGH, 30000);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");

  // light part
  if (cm == 0) {
    // no echo, nothing close, LED off
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  else if (cm < 20) {
    // very close: LED stays on, STOP
    digitalWrite(ledPin, HIGH);
    delay(100);
  }
  else if (cm < 100) {
    // getting close: blink, faster as you get closer
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(cm * 5);
  }
  else {
    // far away: LED off
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}