#include <ESP8266WiFi.h>

const char* ssid = "MARCOS X";
const char* password = "00000000";
const char* server = "192.168.222.247";

int motion_sensor_pin = D1;

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  pinMode(motion_sensor_pin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(motion_sensor_pin) == 1) {
    WiFiClient client;
    if (client.connect(server, 80)) {
      client.println("GET /motion-detected HTTP/1.1");
      client.println("Host: other_ESP8266_IP_address");,,
      client.println();
    }
    delay(1000);
    client.stop();
  }
}