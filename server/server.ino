#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

const char *user = "controle1";
const char *pass = "1234567890"; 

#define PIN_LED D4
#define PIN_LIGHT D1
#define PIN_AUTOMATIC D2
#define PIN_SPEED A0

WebSocketsServer server = WebSocketsServer(8080);

uint8_t _speed;
uint8_t _light;
uint8_t _automatic;


void evt(uint8_t, WStype_t, uint8_t *, size_t);
void buttons();
void sendData();


uint8_t btn_light;
uint8_t btn_automatic;

bool connected;
bool systemUpdates;
unsigned long timer;

void setup() {

  WiFi.mode(WIFI_AP);
  WiFi.softAP(user, pass);

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LIGHT, INPUT);
  pinMode(PIN_AUTOMATIC, INPUT);

  connected = false;
  systemUpdates = false;
  timer = 0;
  
  server.onEvent(evt);
  server.begin();
}

void loop() {

  digitalWrite(PIN_LED, connected);
  
  buttons();

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

void buttons() {

  if(millis() - timer < 10) return;

  uint8_t t_speed, t_light, t_automatic;
  
  t_speed = (analogRead(PIN_SPEED)-1) >> 2;
  t_light = digitalRead(PIN_LIGHT);
  t_automatic = digitalRead(PIN_AUTOMATIC);

  if(abs(_speed - t_speed) > 8) {
    _speed = t_speed;
    systemUpdates = true;
  }

  if(btn_light && !t_light) {
    _light = !_light;
    systemUpdates = true;
  }

  if(btn_automatic && !t_automatic) {
    _automatic = !_automatic;
    systemUpdates = true;
  }


  btn_light = t_light;
  btn_automatic = t_automatic;

  timer = millis();
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
