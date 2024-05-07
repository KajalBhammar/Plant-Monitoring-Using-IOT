#include <DHT.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Firebase_ESP_Client.h>  // Firebase library
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define DHTPIN D1      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22  // DHT 22 (AM2302), AM2321

// DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

// NTP Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
const long timeZoneOffset = 5.5 * 3600;  // Time zone offset for IST (India Standard Time)

// Wi-Fi credentials
const char *ssid = "Kajal";
const char *password = "Kajal@123";

// Soil moisture sensor calibration values
const int dry = 595;  // ADC value for dry soil
const int wet = 239;  // ADC value for wet soil

// Pump pin
#define PUMP_PIN D2

// Firebase configuration
#define API_KEY "AIzaSyDrOFUznr-Tjj01N1aaxU6pH2zqh9B0BhY"
#define DATABASE_URL "https://plantcare-123-default-rtdb.firebaseio.com/"

void setup() {
  // Initialize pump pin
  digitalWrite(PUMP_PIN, HIGH);
  pinMode(PUMP_PIN, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize NTP Client
  timeClient.begin();
  timeClient.setTimeOffset(timeZoneOffset);

 // Initialize Firebase
  FirebaseConfig firebaseConfig;
  firebaseConfig.api_key = API_KEY;
  firebaseConfig.database_url = DATABASE_URL;
  Firebase.begin(&firebaseConfig);
}

void loop() {
  // Read soil moisture
  int soilMoistureVal = analogRead(A0);
  int soilMoisture = map(soilMoistureVal, wet, dry, 0, 100);
  
  // Print soil moisture
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.println("%");

  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print humidity and temperature
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Control pump based on soil moisture and temperature
  if (soilMoisture < 30 && temperature > 25) {
    digitalWrite(PUMP_PIN, LOW);  // Turn on the pump
    Serial.println("Pump turned on.");
  } else {
    digitalWrite(PUMP_PIN, HIGH);  // Turn off the pump
    Serial.println("Pump turned off.");
  }

  // Read water level
  int sensorValue = analogRead(A1);  // Assuming water level sensor is connected to A1
  float waterLevel = map(sensorValue, dry, wet, 0, 100);
  waterLevel = constrain(waterLevel, 0, 100);
  
  // Print water level
  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  // Update time
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);

  // Format date and time
  String currentDate = String(ptm->tm_year + 1900) + "-" + String(ptm->tm_mon + 1) + "-" + String(ptm->tm_mday);
  String currentTime = timeClient.getFormattedTime();

  // Push sensor data to Firebase
  Firebase.pushInt("soilMoisture/" + currentDate, currentTime, soilMoisture);
  Firebase.pushFloat("TemperatureHumidity/" + currentDate, currentTime + "/temperature", temperature);
  Firebase.pushFloat("TemperatureHumidity/" + currentDate, currentTime + "/humidity", humidity);
  Firebase.pushFloat("WaterLevel/" + currentDate, currentTime, waterLevel);

  // Delay for 10 seconds
  delay(10000);
}
