#define BLYNK_TEMPLATE_ID "TMPL3_BBu1C8T"
#define BLYNK_TEMPLATE_NAME "Temp Humidity Sensing"
#define BLYNK_AUTH_TOKEN "jGEFZEnrIQ5juD-JMJRbTq9XDZKz1ype"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = "RadheShyam";
char pass[] = "RadheShyam";

// DHT setup
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// RGB + Buzzer pins
const int redPin = 25;
const int greenPin = 26;
const int bluePin = 27;
const int buzzerPin = 13;

BlynkTimer timer;

// Control LED + buzzer based on temperature
void controlOutputs(float temp) {
  if (temp < 25) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
  else if (temp >= 25 && temp <= 30) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    digitalWrite(buzzerPin, LOW);
  }
  else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzerPin, HIGH);
  }
}

// Read sensor and send to Blynk
void sendSensor() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Sensor error");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.println(humidity);

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);

  controlOutputs(temperature);
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}