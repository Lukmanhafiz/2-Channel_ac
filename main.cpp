#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Gree.h>
#include <ir_Haier.h>

// ===================== WiFi =====================
const char* ssid     = "NOC";
const char* password = "noc2023!";

// ===================== Pin IR =====================
#define IR_GREE 22
#define IR_HAIER 23

// ===================== WebSocket =====================
WebSocketsClient webSocket;

// ===================== IR Setup =====================
IRGreeAC acGree(IR_GREE);
IRHaierAC acHaier(IR_HAIER);

bool greePower = false;
bool haierPower = false;
int  greeTemp  = 24;
int  haierTemp = 24;

// -------------------- Proses Pesan dari Node-RED --------------------
void handleMessage(String payload) {
  Serial.println("[ESP32] RX RAW: " + payload);

  StaticJsonDocument<300> doc;
  DeserializationError err = deserializeJson(doc, payload);
  if (err) {
    Serial.println("[ESP32] JSON Error");
    return;
  }

  String device_id = doc["device_id"] | "";
  String action    = doc["action"]    | "";

  Serial.println("[ESP32] Device: " + device_id + " | Action: " + action);

  if (device_id == "Stand Batik 1") {
    if (action == "on") {
      greePower = true;
      acGree.setMode(kGreeCool);
      acGree.setTemp(greeTemp);
      acGree.setFan(kGreeFanAuto);
      acGree.on();
      acGree.send();

      haierPower = true;
      acHaier.setMode(kHaierAcCool);
      acHaier.setTemp(haierTemp);
      acHaier.setFan(kHaierAcFanAuto);
      acHaier.send();

      Serial.println("[ESP32] Gree & Haier: ON");
    }
    else if (action == "off") {
      greePower = false;
      acGree.off();
      acGree.send();

      haierPower = false;
      Serial.println("[ESP32] Gree & Haier: OFF");
    }
  }
}

// -------------------- WebSocket Event --------------------
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_CONNECTED:
      Serial.println("[ESP32] Connected to Node-RED");
      break;
    case WStype_TEXT:
      handleMessage(String((char*)payload));
      break;
    case WStype_DISCONNECTED:
      Serial.println("[ESP32] Disconnected from Node-RED");
      break;
  }
}

// ===================== SETUP =====================
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("[ESP32] Connecting WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[ESP32] WiFi connected! IP: " + WiFi.localIP().toString());

  // WebSocket ke Node-RED
  webSocket.begin("192.168.223.21", 1880, "/ac-control");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);

  // Inisialisasi AC
  acGree.begin();
  acHaier.begin();
  acGree.off();
  Serial.println("[ESP32] Ready for commands...");
}

// ===================== LOOP =====================
void loop() {
  webSocket.loop();
}
