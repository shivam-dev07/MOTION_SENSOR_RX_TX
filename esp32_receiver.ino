
#include <WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>

const char* ssid = "MARCOS X";
const char* password = "00000000";
#define BLYNK_AUTH_TOKEN "ZNN2H9Z1xu2W8XNsEzu_gcO5yvFdgzyo" //Enter your blynk auth token
char auth[] = BLYNK_AUTH_TOKEN;
WiFiServer server(80);

int motion_detected = 0;
int timer = 0;
#define led_pin  2
#define relay_pin1 13 // Relay pin
#define relay_pin2 12 // Relay pin
#define relay_pin3 14 // Relay pin
#define relay_pin4 27 // Relay pin

BLYNK_WRITE(V0) {
  bool value1 = param.asInt();
  // Check these values and turn the relay1 ON and OFF
  if (value1 == 1) {
    digitalWrite(relay_pin1, LOW);
  } else {
    digitalWrite(relay_pin1, HIGH);
  }
}
BLYNK_WRITE(V1) {
  bool value2 = param.asInt();
  // Check these values and turn the relay2 ON and OFF
  if (value2 == 1) {
    digitalWrite(relay_pin2, LOW);
  } else {
    digitalWrite(relay_pin2, HIGH);
  }
}
BLYNK_WRITE(V2) {
  bool value3 = param.asInt();
  // Check these values and turn the relay2 ON and OFF
  if (value3 == 1) {
    digitalWrite(relay_pin3, LOW);
  } else {
    digitalWrite(relay_pin3, HIGH);
  }
}
BLYNK_WRITE(V3) {
  bool value4 = param.asInt();
  // Check these values and turn the relay2 ON and OFF
  if (value4 == 1) {
    digitalWrite(relay_pin4, LOW);
  } else {
    digitalWrite(relay_pin4, HIGH);
  }
}
BLYNK_WRITE(V5) {
  bool value4 = param.asInt();
  // Check these values and turn the relay2 ON and OFF
  if (value4 == 1) {
    
      digitalWrite(relay_pin1, LOW);
      digitalWrite(relay_pin2, LOW);
      digitalWrite(relay_pin3, LOW);
      digitalWrite(relay_pin4, LOW);
  } else {
      digitalWrite(relay_pin1, HIGH);
      digitalWrite(relay_pin2, HIGH);
      digitalWrite(relay_pin3, HIGH);
      digitalWrite(relay_pin4, HIGH);
  }
}
void setup() {
 
  pinMode(led_pin, OUTPUT);
  pinMode(relay_pin1,OUTPUT);
  pinMode(relay_pin2,OUTPUT);
  pinMode(relay_pin3,OUTPUT);
  pinMode(relay_pin4,OUTPUT);
  digitalWrite(led_pin, LOW);
  digitalWrite(relay_pin1, HIGH);
  digitalWrite(relay_pin2, HIGH);
  digitalWrite(relay_pin3, HIGH);
  digitalWrite(relay_pin4, HIGH);
  
  WiFi.begin(ssid, password);
  Blynk.begin(auth, ssid, password, "blynk.cloud", 80);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  server.begin();
  Serial.println("Server started");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Blynk.run();
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    if (request.indexOf("/motion-detected") != -1) {
      motion_detected = 1;
      digitalWrite(led_pin, HIGH);
      digitalWrite(relay_pin1, LOW);
      digitalWrite(relay_pin2, LOW);
      digitalWrite(relay_pin3, LOW);
      digitalWrite(relay_pin4, LOW);
    }
    client.flush();
    client.stop();
  }
  
  if (motion_detected) {
    timer++;
    delay(1000);
    if (timer == 10) {
      motion_detected = 0;
      digitalWrite(led_pin, LOW);
      digitalWrite(relay_pin1, HIGH);
      digitalWrite(relay_pin2, HIGH);
      digitalWrite(relay_pin3, HIGH);
      digitalWrite(relay_pin4, HIGH);
      timer = 0;
    }
  }
}

