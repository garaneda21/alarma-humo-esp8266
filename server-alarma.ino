#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <StreamString.h>
#include <ArduinoJson.h>
#include <DHT.h>

#ifndef STASSID
#define STASSID "Sombrero"
#define STAPSK "patata48"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

const int rojo = D1;
const int sensor = D2;

DHT dht(D2, DHT22);

void handleRoot() {
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  StaticJsonDocument<300> JSONData;

  float t = dht.readTemperature();
  bool alerta = t > 23 ? true : false;

  JSONData["temp"] = t;
  JSONData["alerta"] = alerta;

  char data[300];

  serializeJson(JSONData, data);

  server.enableCORS(true);
  server.send(200, "application/json", data);
}

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rojo, OUTPUT);
  pinMode(sensor, INPUT);

  digitalWrite(rojo, 1);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) { Serial.println("MDNS responder started"); }

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");

  dht.begin();
  delay(2000);

  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(rojo, 0);
}

void loop(void) {
  server.handleClient();
  MDNS.update();

  float t = dht.readTemperature();

  if (t > 23) {
    digitalWrite(rojo, HIGH);
  } else {
    digitalWrite(rojo, LOW);
  }
}
