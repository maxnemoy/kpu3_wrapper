#include <Arduino.h>
#include <sensor.h>

Sensor sensor(4, 2);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("mm:\t");
  Serial.println(sensor.getMillimetersOfMercury() , 2);
  Serial.print("psi:\t");
  Serial.println(sensor.getPsi() , 2);
}