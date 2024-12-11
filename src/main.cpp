#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "trikappa";
char pass[] = "bowenishandsome";

char auth[] = "86O738A-JolOEfo4p25h0PkjLsZuEsxS";

const int soilSensorPin = 36; 
const int relayPin = 27;      

BlynkTimer timer;

bool pumpState = false; 

void updatePumpState(bool state) {
  if (pumpState != state) { 
    pumpState = state;
    if (pumpState) {
      Serial.println("Pump is ON");
    } else {
      Serial.println("Pump is OFF");
    }
  }
}

void sendSoilMoisture() {
  int sensorValue = analogRead(soilSensorPin); 
  int moisturePercentage = map(sensorValue, 0, 4095, 0, 100); 
  moisturePercentage = 100 - moisturePercentage;             

  Blynk.virtualWrite(V0, moisturePercentage);

  // Print soil moisture level
  Serial.print("Soil Moisture Level: ");
  Serial.print(moisturePercentage);
  Serial.println(" %");
}

BLYNK_WRITE(V1) { 
  bool buttonState = param.asInt(); 
  if (buttonState) {
    digitalWrite(relayPin, HIGH);  
    Serial.println("Manual Control: Pump is ON");
    updatePumpState(true);
  } else {
    digitalWrite(relayPin, LOW);  
    Serial.println("Manual Control: Pump is OFF");
    updatePumpState(false);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  if (Blynk.connected()) {
    Serial.println("Connected to Blynk");
  } else {
    Serial.println("Failed to connect to Blynk");
  }

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); 

  timer.setInterval(1000L, sendSoilMoisture);
}

void loop() {
  Blynk.run(); 
  timer.run(); 
}