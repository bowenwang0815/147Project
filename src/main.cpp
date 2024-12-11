#include <Arduino.h>

// Define the analog pin for the soil moisture sensor
const int soilSensorPin = 36; // Replace 34 with the GPIO pin you connected to

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  Serial.println("Soil Moisture Sensor Test");
}

void loop() {
  int sensorValue = analogRead(soilSensorPin); // Read the analog value
  Serial.print("Soil Moisture Level currently is: ");
  Serial.println(sensorValue);

  delay(1000); // Wait for 1 second
}
