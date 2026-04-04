#include <Adafruit_VL53L1X.h>

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X();

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Looking for VL53L1X distance sensor...");

  if (!vl53.begin(0x29, &Wire)) {
    Serial.println("ERROR: Could not find sensor! Check wiring.");
    while (1) delay(10);
  }

  Serial.println("Sensor found!");

  if (!vl53.startRanging()) {
    Serial.println("ERROR: Could not start ranging!");
    while (1) delay(10);
  }

  vl53.setTimingBudget(50);

  Serial.println("Ranging started! Waiting for readings...");
  Serial.println("");

  pinMode(23, OUTPUT);
}

void loop() {
  if (vl53.dataReady()) {

    int16_t distance = vl53.distance();

    if (distance == -1) {
      Serial.println("Out of range or no object detected!");
    } else {
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(" mm  (");
      Serial.print(distance / 10.0, 1); 
      Serial.print(" cm  /  ");
      Serial.print(distance / 1000.0, 3);
      Serial.println(" m)");
      if (distance / 10.0 < 50) {
        digitalWrite(23, HIGH);
      }
      else {
        digitalWrite(23, LOW);
      }
    }

    vl53.clearInterrupt();
  }
}