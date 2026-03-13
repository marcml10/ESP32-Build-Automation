#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Cant see";
const char* password = "12341234";

WebServer server(80); // Create a server on port 80 (standard web port)
const int ledPin = 2;

// The "Home Page" code (HTML)
void handleRoot() {
  String html = "<html><body><h1>ESP32 Remote Control</h1>";
  html += "<p><a href=\"/on\"><button style='font-size:30px;'>TURN ON</button></a></p>";
  html += "<p><a href=\"/off\"><button style='font-size:30px;'>TURN OFF</button></a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }

  Serial.println("\nConnected!");
  Serial.print("Go to this IP: ");
  Serial.println(WiFi.localIP());

  // Define what happens when you visit different links
  server.on("/", handleRoot);
  server.on("/on", []() {
    digitalWrite(ledPin, HIGH);
    handleRoot(); // Refresh page
  });
  server.on("/off", []() {
    digitalWrite(ledPin, LOW);
    handleRoot(); // Refresh page
  });

  server.begin(); // Start the server
}

void loop() {
  server.handleClient(); // Keep listening for web visitors
}