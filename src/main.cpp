#include <Arduino.h>

// Most ESP32 boards have a built-in blue LED on pin 2
#define LED_PIN 2 

void setup() {
  // Tell the ESP32 that pin 2 is an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // Turn the LED on
  delay(1000);                  // Wait for 1 second (1000 milliseconds)
  digitalWrite(LED_PIN, LOW);   // Turn the LED off
  delay(1000);                  // Wait for 1 second
}