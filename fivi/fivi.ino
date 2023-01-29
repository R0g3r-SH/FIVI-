#include  <ESP8266WiFi.h>
#include <FirebaseESP8266.h>


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "DHT.h"


#define WIFI_SSID "HOME-9C39"
#define WIFI_PASSWORD "ABC2514ECF4241CA"

#define FIREBASE_HOST "fivi-31d19-default-rtdb.firebaseio.com"

/** The database secret is obsoleted, please use other authentication methods,
   see examples in the Authentications folder.
*/
#define FIREBASE_AUTH "NdNnSqss4xEny1gR6cVnrioqTaHEcVZieFNPCNLo"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

FirebaseData fbdo;
FirebaseJson json;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

uint8_t DHTPin = 6;
DHT dht(DHTPin, DHTTYPE);
float Temperature;
float Humidity;


void setup()
{

  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  display.println("Connecting to Wi-Fi");
  display.display();
  delay(1000);
  Serial.println("Conectando FIVI :) ....");
  display.clearDisplay();
  display.println("Conectando FIVI :)...");
  display.display();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    display.print(".");
    display.display();
    delay(300);
  }


  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);


  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  fbdo.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  fbdo.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(fbdo, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(fbdo, "tiny");

  //optional, set the decimal places for float and double data to be stored in database
  Firebase.setFloatDigits(2);
  Firebase.setDoubleDigits(6);
  pinMode(DHTPin, INPUT);
  dht.begin();


}

void postTemp() {

  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity
  Serial.print(Temperature);
  Serial.println(Humidity);

  Firebase.pushFloat(fbdo, "/DHT22/Humidity", Humidity);
  Firebase.pushFloat(fbdo, "/DHT22/Temperature", Temperature);

  if (fbdo.errorReason()) {
    Serial.println(fbdo.errorReason());
    return;
  }

}



void loop()
{


}
