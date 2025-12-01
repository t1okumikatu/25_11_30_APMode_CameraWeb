#include "esp_camera.h"
#include <WiFi.h>

//
// WARNING!!! PSRAM IC required for UXGA resolution and high JPEG quality
//            Ensure ESP32 Wrover Module or other board with PSRAM is selected
//            Partial images will be transmitted if image exceeds buffer size
//
//            You must select partition scheme from the board menu that has at least 3MB APP space.
//            Face Recognition is DISABLED for ESP32 and ESP32-S2, because it takes up from 15
//            seconds to process single frame. Face Detection is ENABLED if PSRAM is enabled as well

// ===================
// Select camera model
// ===================
#define CAMERA_MODEL_XIAO_ESP32S3 // Has PSRAM
#include "camera_pins.h"
//Wi-Fiタブ用-----------------
struct WiFitype {
  char ssid[32];
  char pass[64];
  char ssid2[32];
  char pass2[64];
};
struct WiFitype wifi;

struct FixedIPtype {
  byte Flag;
  unsigned long IP;
  unsigned long MASK;
  unsigned long GATE;
};
struct FixedIPtype FixedIP;


void startCameraServer();
//void setupLedFlash(int pin);

void setup() {
  //Serial.begin(250000);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  config();
  



  WiFi.begin(wifi.ssid, wifi.pass);
  long WiFiTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > WiFiTime + 10000) break;
  }
  if (WiFi.status() != WL_CONNECTED) {
    //WiFi.mode(WIFI_AP_STA);
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP-S3", "12345678");
    const IPAddress ip(192, 168, 4, 1);
    const IPAddress gateway(192, 168, 4, 1);
    const IPAddress netmask(255, 255, 255, 0);
    WiFi.softAPConfig(ip, gateway, netmask);
  }
  //変更----------------------------------------------

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
  pinMode(6, OUTPUT);  //LEDライト追加分
  delay(5000);
}

void loop() {
  // Do nothing. Everything is done in another task by the web server
  delay(10000);
}