#include <Arduino.h>

#define LED_PIN 2 // Most ESP32 dev boards have an internal blue LED on pin 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("System starting...");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED is ON");
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED is OFF");
  delay(1000);
}