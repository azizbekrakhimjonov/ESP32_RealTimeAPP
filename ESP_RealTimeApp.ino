#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "swaggeruz";
const char* password = "python01";
const char* serverUrl = "https://510ea43818d5.ngrok-free.app/press";  

const int buttonPin = 27;  
bool lastState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);  

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  bool currentState = digitalRead(buttonPin);

  if (lastState == LOW && currentState == HIGH) {
    HTTPClient http;
    http.begin(serverUrl); 
    http.addHeader("Content-Type", "application/json");
    int responseCode = http.POST("{}");
    http.end();

    Serial.println("Button press sent!");
  }

  lastState = currentState;
  delay(10);
}
