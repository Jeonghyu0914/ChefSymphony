#include <DHT11.h>

#define dht 13

DHT11 sample(dht);

void setup() {
  Serial.begin(115200);
}

void loop() {
  int temperature, humidity;

  // Attempt to read the temperature and humidity values from the DHT11 sensor.
  int result = sample.readTemperatureHumidity(temperature, humidity);

  // Check the results of the readings.
  // If the reading is successful, print the temperature and humidity values in CSV format.
  if (result == 0) {
      Serial.print("Temperature:");
      Serial.print(temperature);
      Serial.print(",Humidity:");
      Serial.println(humidity);
  } else {
      // Print error message based on the error code.
      Serial.println(DHT11::getErrorString(result));
  }
}
