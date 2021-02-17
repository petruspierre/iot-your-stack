#include <WiFi.h>
#include <EspMQTTClient.h>
#include <SimpleDHT.h>

SimpleDHT11 dht(21);

EspMQTTClient client(
  "brisa-1360849",
  "m8109yam",
  "broker.hivemq.com",  // MQTT Broker server ip
  "client-esp-iot"      // Client name that uniquely identify your device
);

void setup() {
  Serial.begin(115200);
}

void onConnectionEstablished() {
  Serial.println("Connected to MQTT");
}

void loop() {
  byte temperature = 0;
  byte humidity = 0 ;
  dht.read(&temperature, &humidity, NULL);
  
  client.publish("iot-your-stack/temperature", String(temperature));
  client.publish("iot-your-stack/humidity", String(humidity)); 

  delay(5000);
  client.loop();
}
