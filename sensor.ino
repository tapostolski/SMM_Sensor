#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>

/////////// CONFIGURATION ///////////
// SENSOR ID
const int sensorId = ;

// WIFI CONFIGURATION
const char* ssid = "";
const char* password = ";
const String serverUrl = "";

// BASIC AUTH DATA
const char* authUsername = "";
const char* authPassword = "";

// TIMING
unsigned long lastDataSend = 0;
const unsigned long sendInterval = 15 * 60 * 1000; //15 mins

// PINS
const int sensorPin = A0;
const int buttonPin = D5;
const int ledPin = D6;

// LED
#define NUMPIXELS 1
#define LED_BRIGHTNESS 64
Adafruit_NeoPixel pixels(NUMPIXELS, ledPin, NEO_GRB + NEO_KHZ800);

// CALIBRATION
const int dryValue = 280;
const int wetValue = 800;
/////////// CONFIGURATION ///////////

// BATTERY
SFE_MAX1704X lipo;
double batteryVoltage = 0;
double batteryPercentage = 0;

unsigned long ledEndTime = 0;
bool ledActive = false;
bool sendingData = false;

void setup() {

  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);

  pixels.begin();
  pixels.setBrightness(LED_BRIGHTNESS);
  pixels.clear();
  pixels.show();

  Wire.begin(D2, D1);

  if (!lipo.begin()) {
    Serial.println("MAX17043 NIE WYKRYTY!");
  } else {
    lipo.quickStart();
    lipo.setThreshold(20);
    Serial.println("MAX17043 OK");
  }

  connectToWiFi();
}

void loop() {

  handleButton();

  if (ledActive && millis() > ledEndTime && !sendingData) {
    ledOff();
  }

  if (WiFi.status() == WL_CONNECTED) {
    if (millis() - lastDataSend >= sendInterval) {
      sendingData = true;
      sendMoistureData();
      sendingData = false;
      lastDataSend = millis();
    }
  }

  delay(10);
}

void handleButton() {

  if (digitalRead(buttonPin) == LOW && !ledActive && !sendingData) {

    delay(30);

    if (digitalRead(buttonPin) == LOW) {

      Serial.println("PRZYCISK!");

      readBattery();
      showBatteryOnLED();

      ledEndTime = millis() + 3000;
      ledActive = true;

      while (digitalRead(buttonPin) == LOW) {
        delay(10);
      }
    }
  }
}

void readBattery() {

  batteryVoltage = lipo.getVoltage();

  if (batteryVoltage >= 4.0) batteryPercentage = 90;
  else if (batteryVoltage >= 3.8) batteryPercentage = 60;
  else if (batteryVoltage >= 3.6) batteryPercentage = 30;
  else batteryPercentage = 10;
}

void showBatteryOnLED() {

  if (batteryPercentage >= 75) {
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  } else if (batteryPercentage >= 40) {
    pixels.setPixelColor(0, pixels.Color(255, 255, 0));
  } else if (batteryPercentage >= 20) {
    pixels.setPixelColor(0, pixels.Color(255, 100, 0));
  } else {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  }

  pixels.show();
}

void ledOff() {
  pixels.clear();
  pixels.show();
  ledActive = false;
}

void setLEDColor(int r, int g, int b) {
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();
}

void sendMoistureData() {

  int rawValue = analogRead(sensorPin);
  int moisture = map(rawValue, dryValue, wetValue, 0, 100);
  moisture = constrain(moisture, 0, 100);

  WiFiClient client;
  HTTPClient http;

  String payload = "{\"moisture\":" + String(moisture) + ",\"sensor_id\":" + String(sensorId) + "}";

  http.begin(client, serverUrl);
  http.addHeader("Content-Type", "application/json");
  http.setAuthorization(authUsername, authPassword);

  int httpCode = http.POST(payload);

  http.end();
}

void connectToWiFi() {

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
