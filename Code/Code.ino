#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define DHTTYPE DHT11
#define dht_dpin 12 // Pin D6 sur NodeMCU

const char* ssid = "REDMI 15C";
const char* password = "hafsaelf000";

// Remplacez par "http://10.145.236.57:8000/api/post/" 
const char* serverName = "http://hafsaelf06.pythonanywhere.com/api/add/";

DHT dht(dht_dpin, DHTTYPE);

void setup() {
  dht.begin();
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Vérification de la lecture du capteur DHT11
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Échec de la lecture du capteur DHT11 !");
    delay(2000);
    return;
  }

  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  temperature = ");
  Serial.print(temperature);
  Serial.println("C");

// Envoi des valeurs au serveur Web
  WiFiClient client;
  HTTPClient http;
  DynamicJsonDocument jsonDoc(200); // Utilisation de DynamicJsonDocument pour la sérialisation JSON
  jsonDoc["temperature"] = temperature;
  jsonDoc["humidite"] = humidity;
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);
  
  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/json");
  Serial.println(jsonStr);
  int httpResponseCode = http.POST(jsonStr);
  
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    }

    http.end();
 

  // Pause de 10 secondes entre chaque envoi
  delay(10000);
}
