

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <time.h>

#include "DHT.h"


#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#define FIREBASE_HOST ""

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


/** The database secret is obsoleted, please use other authentication methods,
   see examples in the Authentications folder.
*/
#define FIREBASE_AUTH ""

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define DHTPin D6
DHT dht(DHTPin, DHTTYPE);
float Temperature;
float Humidity;
int electro = 13;
int enable = 1;

String hora1 = "07:00";
String hora2 = "07:20";
String hora3 = "07:40";
String hora4 = "08:00";///se toma medicion
String hora5 = "08:20";
String hora6 = "08:40";
String hora7 = "09:00";
String hora8 = "09:20";
String hora9 = "09:40";
String hora10 = "10:00";
String hora11 = "10:20";
String hora12 = "10:40";
String hora13 = "11:00";
String hora14 = "11:20";
String hora15 = "11:40";
String hora16 = "12:00";
String hora17 = "12:20";
String hora18 = "12:40";
String hora19 = "13:00";
String hora20 = "13:20";
String hora21 = "13:40";
String hora22 = "14:00";//setoma medicion
String hora23 = "14:20";
String hora24 = "14:40";
String hora25 = "15:00";
String hora26 = "15:20";
String hora27 = "15:40";
String hora28 = "16:00";
String hora29 = "16:20";
String hora30 = "16:40";
String hora31 = "17:00";
String hora32 = "17:20";
String hora33 = "17:40";
String hora34 = "18:00";
String hora35 = "18:20";
String hora36 = "18:40";
String hora37 = "19:00";///se toma medicion

//Define FirebaseESP8266 data object
FirebaseData fbdo;

FirebaseJson json;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
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
  display.clearDisplay();
  delay(2000);
  display.println("Conectando FIVI :)...");
  display.display();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    display.print(".");
    display.display();
    delay(300);

  }
  display.clearDisplay();
  delay(2000);
  display.setCursor(0, 10);
  Serial.println();
  display.println("Connected with IP:  ");
  display.println(WiFi.localIP());
  display.println("RED:  ");
  display.println(WIFI_SSID);
  display.display();
  delay(2000);
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  pinMode(DHTPin, INPUT);
  dht.begin();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  fbdo.setBSSLBufferSize(1024, 1024);
  //Set the size of HTTP response buffers in the case where we want to work with large data.
  fbdo.setResponseSize(1024);
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(fbdo, 1000 * 60);


  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
  setenv("TZ", "CST6CDT,M4.1.0,M10.5.0", 1);
  get_Hour_First();
}

void postTemp() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity
  Serial.print(Temperature);
  Serial.println(Humidity);
  String tim=get_time();
  String hou=get_Hour();

FirebaseJson json;
FirebaseJson json2;
FirebaseJson json3;

json.set("temp", Temperature);
json.set("hum", Humidity);
json.set("time", tim);
json.set("hour",hou);


if (Firebase.pushJSON(fbdo, "/DHT", json)) {

  Serial.println(fbdo.dataPath());

  Serial.println(fbdo.pushName());

  Serial.println(fbdo.dataPath() + "/"+ fbdo.pushName());

} else {
  Serial.println(fbdo.errorReason());
}

}


String get_Hour_First() {
  time_t now;
  time(&now);
  char time_output[30];
  // See http://www.cplusplus.com/reference/ctime/strftime/ for strftime functions
  strftime(time_output, 30, "%H:%M", localtime(&now));
  display.clearDisplay();
  display.setCursor(3, 10);
  delay(2000);
  display.println("Ajustando           ");
  display.println("Zona Horaria...     ");
  display.display();
  for (int i = 0; i < 10; i++) {
    display.print(".");
    display.display();
    delay(3000);
  }
  strftime(time_output, 30, "%H:%M", localtime(&now));
  startFivi();
  return String(time_output); // returns Sat 20-Apr-19 12:31:45
}

String get_Hour() {
  time_t now;
  time(&now);
  char time_output[30];
  // See http://www.cplusplus.com/reference/ctime/strftime/ for strftime functions
  strftime(time_output, 30, "%H:%M", localtime(&now));
  return String(time_output); // returns Sat 20-Apr-19 12:31:45
}

void startFivi() {
  Serial.println("Listo para comenzar :)");
  display.clearDisplay();
  delay(200);
  display.setCursor(0, 10);
  display.println("Listo para comenzar :)");
  delay(3000);
  display.clearDisplay();
  delay(200);
  display.setCursor(0, 10);
  display.println("Connected with IP:  ");
  display.println(WiFi.localIP());
  display.println("RED:  ");
  display.println(WIFI_SSID);
  display.println(get_time());
  display.display();
  delay(200);
}

String get_time() {
  time_t now;
  time(&now);
  char time_output[30];
  // See http://www.cplusplus.com/reference/ctime/strftime/ for strftime functions
  strftime(time_output, 30, "%a %d-%m-%y %T", localtime(&now));
  return String(time_output); // returns Sat 20-Apr-19 12:31:45
}

void startFivi2() {
  display.clearDisplay();
  delay(200);
  display.setCursor(0, 10);
  display.println("Connected with IP:  ");
  display.println(WiFi.localIP());
  display.println("RED:  ");
  display.println(WIFI_SSID);
  display.println(get_time());
  display.display();
  delay(200);

}
void regar() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(500);
}

void loop() {

  startFivi2();
  Serial.println(get_Hour());
  if (get_Hour() == hora1) {
    while (enable == 1) {
      regar();
      enable = 0;
    }
  }
  else if (get_Hour() == hora2) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora3) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora4) {
    while (enable == 1) {
      regar();
      postTemp();
      enable = 0;
    }

  }
  else if (get_Hour() == hora5) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora6) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora7) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora8) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora9) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora10) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora11) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora12) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else  if (get_Hour() == hora13) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora14) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora15) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora16) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora17) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora18) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora19) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora20) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora21) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora22) {
    while (enable == 1) {
      regar();
      postTemp();
      enable = 0;
    }

  }
  else if (get_Hour() == hora23) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora24) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora25) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora26) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora27) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora28) {
    while (enable == 1) {
      regar();
      enable = 0;
    }

  }
  else if (get_Hour() == hora29) {
    while (enable == 1) {
      regar();
      enable = 0;
  
    }

  }
  else if (get_Hour() == hora30) {
    while (enable == 1) {
      regar();
      
      enable = 0;
    }
  }
  else if (get_Hour() == hora31) {
    while (enable == 1) {
      regar();
      
      enable = 0;
    }

  }
  else if (get_Hour() == hora32) {
    while (enable == 1) {
      regar();
      
      enable = 0;
    }
  }
  else if (get_Hour() == hora33) {
    while (enable == 1) {
      regar();
      
      enable = 0;
    }

  }
  else if (get_Hour() == hora34) {
    while (enable == 1) {
      regar();
      
      enable = 0;
    }

  }
  else if (get_Hour() == hora35) {
    while (enable == 1) {
      regar();
      
      enable = 0;
    }

  }
  else if (get_Hour() == hora36) {
    while (enable == 1) {
      regar();
      
      enable = 0;
    }

  }
  else if (get_Hour() == hora37) {
    while (enable == 1) {
      regar();
      postTemp();
      enable = 0;
    }
    
  } else {
    enable = 1;
  }
  delay(500);
}
