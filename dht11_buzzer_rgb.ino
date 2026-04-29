#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const int redPin = 25;
const int greenPin = 26;
const int bluePin = 27;
const int buzzerPin = 13;

DHT dht(DHTPIN, DHTTYPE);

// PWM setup
const int freq = 5000;
const int resolution = 8;

float lastTemp = -100;  // to track change

void setup() {
  Serial.begin(115200);
  dht.begin();

  ledcSetup(0, freq, resolution);
  ledcAttachPin(redPin, 0);

  ledcSetup(1, freq, resolution);
  ledcAttachPin(greenPin, 1);

  ledcSetup(2, freq, resolution);
  ledcAttachPin(bluePin, 2);

  pinMode(buzzerPin, OUTPUT);

  Serial.println("System Initializing...");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT Error!");
    delay(2000);
    return;
  }

  // Only react if temperature changes significantly
  if (abs(temperature - lastTemp) > 1) {

    if (temperature > 30) {
      setColor(255, 0, 0);

      // short beep (not continuous)
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(buzzerPin, LOW);

    } 
    else if (temperature < 20) {
      setColor(0, 0, 255);
      digitalWrite(buzzerPin, LOW);
    } 
    else {
      setColor(0, 255, 0);
      digitalWrite(buzzerPin, LOW);
    }

    lastTemp = temperature;
  }

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" | Humidity: ");
  Serial.println(humidity);

  delay(2000);  // slow down updates
}

void setColor(int r, int g, int b) {
  ledcWrite(0, r);
  ledcWrite(1, g);
  ledcWrite(2, b);
}