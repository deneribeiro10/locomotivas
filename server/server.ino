#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include "config.h"

const char *user = "controle1";
const char *pass = "1234567890"; 

#define PIN_LED D4
#define PIN_LIGHT D1
#define PIN_AUTOMATIC D2
#define PIN_SPEED A0

WebSocketsServer server = WebSocketsServer(8080);

// train info
uint8_t _speed = 0;
uint8_t _light = true;
uint8_t _automatic = true;

// communication
void evt(uint8_t, WStype_t, uint8_t *, size_t);
void sendData();

// how the system handle speed updates
unsigned long timer_speed = 0;
void updateSpeed();

// how the system handle light updates
uint8_t btn_light_state = 0;
uint8_t last_btn_light_read = 0;
unsigned long timer_light = 0;
void updateLight();

// how the system handle automatic updates
uint8_t btn_automatic_state = 0;
uint8_t last_btn_automatic_read = 0;
unsigned long timer_automatic = 0;
void updateAutomatic();

// board status
bool connected = false;
bool systemUpdates = false;

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(user, pass);

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LIGHT, INPUT);
  pinMode(PIN_AUTOMATIC, INPUT);
  
  server.onEvent(evt);
  server.begin();
}

void loop() {
  digitalWrite(PIN_LED, connected);
  
  updateSpeed();
  updateLight();
  updateAutomatic();

  sendData();

  server.loop();
}

void evt(uint8_t num, WStype_t type, uint8_t *msg, size_t len) {
  switch(type) {
    case WStype_CONNECTED:
      connected = true;
      break;
    
    case WStype_DISCONNECTED:
      connected = false;
      break;

    default: ; 
  }
}

void sendData() {
  if(!systemUpdates || !connected) return;
  uint8_t values[3];
  values[0] = _speed;
  values[1] = _light;
  values[2] = _automatic;
  server.broadcastBIN(values, 3);
  systemUpdates = false;
}

void updateSpeed() {
  if(millis() - timer_speed < UPDATE_SPEED_EVERY_MS) return; 
  uint8_t t_speed = (analogRead(PIN_SPEED) >> (10 - SPEED_RESOLUTION_BITS)) << (8 - SPEED_RESOLUTION_BITS);
  if(t_speed != _speed) {
    _speed = t_speed;
    systemUpdates = true;
    timer_speed = millis();
  }
}

void updateLight() {
  uint8_t r = digitalRead(PIN_LIGHT);
  if(r != last_btn_light_read) {
    timer_light = millis();
  }

  if(millis() - timer_light > DEBOUNCE_DELAY_MS) {
    if(r != btn_light_state) {
      btn_light_state = r;
      if(btn_light_state == LOW) {
        _light = !_light;
        systemUpdates = true;
      }
    }
  }

  last_btn_automatic_read = r;
}

void updateAutomatic() {
  uint8_t r = digitalRead(PIN_AUTOMATIC);
  if(r != last_btn_automatic_read) {
    timer_automatic = millis();
  }

  if(millis() - timer_automatic > DEBOUNCE_DELAY_MS) {
    if(r != btn_automatic_state) {
      btn_automatic_state = r;
      if(btn_automatic_state == LOW) {
        _automatic = !_automatic;
        systemUpdates = true;
      }
    }
  }

  last_btn_automatic_read = r;
}
