# Plant Care System

This project is aimed at automating the care of plants by monitoring soil moisture, temperature, humidity, and water level, and controlling a water pump accordingly. The data is logged to Firebase for remote monitoring and analysis.

## Components

- ESP8266 NodeMCU
- DHT22 (AM2302) temperature and humidity sensor
- Soil moisture sensor
- Water level sensor
- Water pump

## Dependencies

- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) for DHT22 sensor
- [ESP8266WiFi library](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi) for ESP8266 Wi-Fi support
- [NTPClient library](https://github.com/arduino-libraries/NTPClient) for obtaining time from NTP servers
- [Firebase ESP8266 library](https://github.com/mobizt/Firebase-ESP8266) for interfacing with Firebase Realtime Database

## Installation

1. Install the necessary libraries:
   - DHT sensor library
   - ESP8266WiFi library
   - NTPClient library
   - Firebase ESP8266 library
2. Connect the components as per the circuit diagram.
3. Update the Wi-Fi credentials, Firebase API key, and database URL in the code.
4. Upload the code to your ESP8266 board.

## Usage

1. Ensure the circuit is powered on and connected to the Wi-Fi network.
2. Open the serial monitor to view sensor readings and system status.
3. Monitor the Firebase Realtime Database for remote access to sensor data.

## Circuit Diagram

![image](https://github.com/KajalBhammar/Plant-Monitoring-Using-IOT/assets/93076200/05dd19b6-feae-4dfa-838c-ed55476c4b65)

## Physical connections between the components and the NodeMCU

![image](https://github.com/KajalBhammar/Plant-Monitoring-Using-IOT/assets/93076200/ddc8fa1a-4e67-466b-889f-4640413ca2f3)


## Contributing

Contributions are welcome! Feel free to submit issues or pull requests.

## License

This project is licensed under the [MIT License](LICENSE).
