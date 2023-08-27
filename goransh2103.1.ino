#include <DHT.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h>

#define DHT_PIN A4
#define DHT_TYPE DHT11
#define WIFI_SSID "guruji4g"
#define WIFI_PASS "05142310"
#define API_KEY "26WO7DMFBYHZXNRC"

DHT dht(DHT_PIN, DHT_TYPE);
WiFiClient client;

void setup() {
  Serial.begin(9600);
  initializeSensors();
  connectToWiFi();
  initializeThingSpeak();
}

void loop() {
  readAndSendSensorData();
  delay(30000);  // Wait for 30 seconds before sending the next data
}

void initializeSensors() {
  dht.begin();
}

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void initializeThingSpeak() {
  ThingSpeak.begin(client);
}

void readAndSendSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);

 int response = ThingSpeak.writeFields(2251068, API_KEY);
  if (response == 200) {
    Serial.println("Data sent to ThingSpeak successfully!");
  } else {
    Serial.println("Error sending data to ThingSpeak.");
  }
}
