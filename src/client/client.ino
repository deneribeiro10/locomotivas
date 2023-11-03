#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

const char *user = "controle1";
const char *pass = "1234567890"; 

#define PIN_LED D3
#define PIN_MT0 D1
#define PIN_MT1 D2

uint8_t speed = 128;
uint8_t light = 0;
uint8_t autom = 0;

WebSocketsClient client;

void waitForWifi();
void evt(WStype_t, uint8_t *, size_t);
void setDefaultValues();
void writeValues();

bool systemUpdates = true;

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(user, pass);

  writeValues();

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_MT0, OUTPUT);
  pinMode(PIN_MT1, OUTPUT);

  waitForWifi();

  client.onEvent(evt);
  client.begin("192.168.4.1", 8080, "/");

}

void loop() {
  writeValues();

  client.loop();
}

void waitForWifi() {
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(PIN_LED, HIGH);
    delay(100);
    digitalWrite(PIN_LED, LOW);
    delay(100);
  }
}

void evt(WStype_t type, uint8_t *msg, size_t len) {
  switch(type) {
    case WStype_CONNECTED:
      break;

    case WStype_DISCONNECTED:
      setDefaultValues();
      break;

    case WStype_BIN:
      speed = msg[0];
      light = msg[1];
      autom = msg[2];
      break;
  }
  systemUpdates = true;
}

void setDefaultValues() {
  speed = 192;
  light = 1;
}

void writeValues() {
  if(!systemUpdates) return;

  if(autom) setDefaultValues();

  if(speed >= 128) {
    analogWrite(PIN_MT0, 0);
    analogWrite(PIN_MT1, speed-128);
  } else {
    analogWrite(PIN_MT0, 128-speed);
    analogWrite(PIN_MT1, 0);
  }

  digitalWrite(PIN_LED, light);

  systemUpdates = false;
}