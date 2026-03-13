#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Cant see";
const char* password = "12341234";

WebServer server(80);
const int ledPin = 2;
bool ledState = false;

void handleRoot() {
  String color = ledState ? "#00ff7f" : "#ff4d4d";
  String status = ledState ? "ON" : "OFF";
  
  String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<style>body{background:#121212; color:white; font-family:sans-serif; text-align:center; padding-top:50px;}";
  html += ".btn{display:block; width:200px; margin:20px auto; padding:20px; border-radius:15px; text-decoration:none; font-weight:bold; font-size:20px; color:white;}";
  html += ".on{background:#2ecc71;} .off{background:#e74c3c;}";
  html += ".status{font-size:40px; color:" + color + ";}</style></head><body>";
  html += "<h1>ESP32 CONTROL</h1>";
  html += "<div class='status'>" + status + "</div>";
  html += "<a href='/on' class='btn on'>TURN ON</a>";
  html += "<a href='/off' class='btn off'>TURN OFF</a>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  
  server.on("/", handleRoot);
  server.on("/on", []() { ledState = true; digitalWrite(ledPin, HIGH); handleRoot(); });
  server.on("/off", []() { ledState = false; digitalWrite(ledPin, LOW); handleRoot(); });
  
  server.begin();
  Serial.println("SYSTEM READY");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}