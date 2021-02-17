import { StatusBar } from 'expo-status-bar';
import React, { useEffect, useState } from 'react';
import { StyleSheet, Text, View } from 'react-native';
import AsyncStorage from '@react-native-async-storage/async-storage';
import init from 'react_native_mqtt';

export default function App() {
  const [temperature, setTemperature] = useState('X');
  const [humidity, setHumidity] = useState('X');

  function onConnect(client) {
    client.subscribe('iot-your-stack/temperature');
    client.subscribe('iot-your-stack/humidity');
  }
  
  function onMessageArrived(message) {
    switch(message.topic) {
      case 'iot-your-stack/temperature':
        setTemperature(message.payloadString);
        break;
      case 'iot-your-stack/humidity':
        setHumidity(message.payloadString);
        break;
    }
  }

  useEffect(() => {
    init({
      size: 10000,
      storageBackend: AsyncStorage,
      defaultExpires: 1000 * 3600 * 24,
      enableCache: true,
      reconnect: true,
      sync : {}
    });

    const client = new Paho.MQTT.Client('broker.hivemq.com', 8000, 'uname');
    client.onMessageArrived = onMessageArrived;
    client.connect({ onSuccess: () => onConnect(client), useSSL: false });
  }, []);

  return (
    <View style={styles.container}>
      <StatusBar style="auto" />
      <Text style={styles.text}>Temperatura atual {temperature}°C</Text>
      <Text style={styles.text}>Umidade atual {humidity}%</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  text: {
    fontSize: 24,
    marginTop: 10,
  }
});
