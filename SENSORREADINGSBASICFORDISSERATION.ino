#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// DHT Sensor
#define DHTPIN 27
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// MQ-7 Sensor
#define MQ7_AO 34
#define MQ7_DO 13

// MQ-135 Sensor
#define MQ135_AO 35
#define MQ135_DO 15

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  pinMode(MQ7_DO, INPUT);
  pinMode(MQ135_DO, INPUT);

  // Initialize BME280
  if (!bme.begin(0x76)) {
    Serial.println("BME280 not found!");
    while (1);
  }

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  int coAnalog = analogRead(MQ7_AO);
  float coVoltage = coAnalog * (3.3 / 4095.0);

  int coDigital = digitalRead(MQ7_DO);

  int smoke135Analog = analogRead(MQ135_AO);
  float smoke135Voltage = smoke135Analog * (3.3 / 4095.0);

  int smoke135Digital = digitalRead(MQ135_DO);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(5000);
    return;
  }

  Serial.println("Sensor Data:");
  Serial.print("  Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" °C");

  Serial.print("  Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  Serial.print("  Pressure: ");
  Serial.print(pressure, 1);
  Serial.println(" hPa");

  Serial.print("  CO Voltage: ");
  Serial.print(coVoltage, 2);
  Serial.println(" V");

  Serial.print("  CO Alarm (Digital): ");
  Serial.println(coDigital);

  Serial.print("  Smoke135 Voltage: ");
  Serial.print(smoke135Voltage, 2);
  Serial.println(" V");

  Serial.print("  Smoke135 Alarm (Digital): ");
  Serial.println(smoke135Digital);

  Serial.println("-----------------------------");

  delay(5000);
}
