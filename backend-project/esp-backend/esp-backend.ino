/* Hey!
 * This program will show to you how to make a simple POST request sending
 * a JSON using EasyHTTP library.
 * ArduinoJSON is a dependency!
 */

#include <EasyHTTP.h>
#include <SimpleDHT.h>

// Network info
char* ssid = "brisa-1360849";
char* password = "m8109yam";

String baseURL = "http://192.168.1.7:3000";

EasyHTTP http(ssid, password);
SimpleDHT11 dht(21);

void setup() {
  
  Serial.begin(115200);
  http.connectWiFi();
  http.setBaseURL(baseURL);

}

void loop() {
  DynamicJsonDocument doc(32);
  String payload = "";

  byte temperature = 0;
  byte humidity = 0;

  dht.read(&temperature, &humidity, NULL);

  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  serializeJson(doc, payload);
  
  String response = http.post("/sensor", payload);
  Serial.println(response);

  delay(3000);
}
