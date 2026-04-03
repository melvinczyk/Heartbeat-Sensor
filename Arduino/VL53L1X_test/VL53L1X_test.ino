#include <Adafruit_VL53L1X.h>

// Create the sensor object
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

  // Start ranging (this tells the sensor to begin taking measurements)
  if (!vl53.startRanging()) {
    Serial.println("ERROR: Could not start ranging!");
    while (1) delay(10);
  }

  // Faster timing budget = faster readings but slightly less accurate
  // 50ms is a good balance for most uses
  vl53.setTimingBudget(50);

  Serial.println("Ranging started! Waiting for readings...");
  Serial.println("");

  pinMode(23, OUTPUT);
}

void loop() {
  // Only read when new data is ready
  if (vl53.dataReady()) {

    int16_t distance = vl53.distance(); // Distance in millimeters

    if (distance == -1) {
      // -1 means the reading failed (object too close, too far, or no object)
      Serial.println("Out of range or no object detected!");
    } else {
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(" mm  (");
      Serial.print(distance / 10.0, 1); // Convert to cm
      Serial.print(" cm  /  ");
      Serial.print(distance / 1000.0, 3); // Convert to meters
      Serial.println(" m)");
      if (distance / 10.0 < 50) {
        digitalWrite(23, HIGH);
      }
      else {
        digitalWrite(23, LOW);
      }
    }

    // Clear the interrupt so the sensor can take the next reading
    vl53.clearInterrupt();
  }
}