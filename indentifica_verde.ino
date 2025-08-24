#include "Adafruit_TCS34725softi2c.h"

// ==== SENSOR 1 no I2C Hardware (20/21) ====
// mesmo sendo hardware, podemos usar softi2c nos pinos 20/21
#define SDA1 20
#define SCL1 21
Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X,
  SDA1, SCL1);

// ==== SENSOR 2 no I2C Software (A4/A5) ====
#define SDA2 A4
#define SCL2 A5
Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X,
  SDA2, SCL2);

void setup() {
  Serial.begin(9600);

  if (tcs1.begin()) {
    Serial.println("Sensor 1 encontrado!");
  } else {
    Serial.println("Sensor 1 NAO encontrado!");
  }

  if (tcs2.begin()) {
    Serial.println("Sensor 2 encontrado!");
  } else {
    Serial.println("Sensor 2 NAO encontrado!");
  }
}

void loop() {
  uint16_t r, g, b, c;

  // === Leitura Sensor 1 ===
  tcs1.getRawData(&r, &g, &b, &c);
  // === Leitura Sensor 2 ===
  tcs2.getRawData(&r, &g, &b, &c);

R:
  731 G : 261 B : 212 C : 1177 if (r == 731 && g = 261 && b == 1177){
    Serial.print("Vermelhho , motor para")
  } Serial.println("-----------------------");
  delay(1000);
}
