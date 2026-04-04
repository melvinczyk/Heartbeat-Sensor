#include <Adafruit_LSM6DS3TRC.h>

Adafruit_LSM6DS3TRC lsm6ds3trc;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Looking for LSM6DS3TR-C...");

  if (!lsm6ds3trc.begin_I2C()) {
    Serial.println("ERROR: Could not find the sensor! Check your wiring.");
    while (1) delay(10);
  }

  Serial.println("Sensor found and connected!");
}

void loop() {
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;

  lsm6ds3trc.getEvent(&accel, &gyro, &temp);

  Serial.println("-- Accelerometer (m/s²) --");
  Serial.print("X: "); Serial.println(accel.acceleration.x, 4);
  Serial.print("Y: "); Serial.println(accel.acceleration.y, 4);
  Serial.print("Z: "); Serial.println(accel.acceleration.z, 4);

  Serial.println("-- Gyroscope (radians/sec) --");
  Serial.print("X: "); Serial.println(gyro.gyro.x, 4);
  Serial.print("Y: "); Serial.println(gyro.gyro.y, 4);
  Serial.print("Z: "); Serial.println(gyro.gyro.z, 4);

  Serial.print("-- Temperature (C): ");
  Serial.println(temp.temperature, 2);

  Serial.println("");
  delay(500);
}