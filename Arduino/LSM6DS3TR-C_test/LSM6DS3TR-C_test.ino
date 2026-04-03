#include <Adafruit_LSM6DS3TRC.h>

// Create the sensor object
Adafruit_LSM6DS3TRC lsm6ds3trc;

void setup() {
  Serial.begin(115200);
  delay(1000); // Give serial monitor time to open

  Serial.println("Looking for LSM6DS3TR-C...");

  // Try to connect to the sensor
  if (!lsm6ds3trc.begin_I2C()) {
    Serial.println("ERROR: Could not find the sensor! Check your wiring.");
    while (1) delay(10); // Stop and do nothing if sensor not found
  }

  Serial.println("Sensor found and connected!");
}

void loop() {
  // These variables will hold the sensor readings
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;

  // Ask the sensor to fill those variables with fresh data
  lsm6ds3trc.getEvent(&accel, &gyro, &temp);

  // Print accelerometer (how fast you're moving/tilting, in m/s²)
  Serial.println("-- Accelerometer (m/s²) --");
  Serial.print("X: "); Serial.println(accel.acceleration.x, 4);
  Serial.print("Y: "); Serial.println(accel.acceleration.y, 4);
  Serial.print("Z: "); Serial.println(accel.acceleration.z, 4);

  // Print gyroscope (how fast you're rotating, in radians/sec)
  Serial.println("-- Gyroscope (radians/sec) --");
  Serial.print("X: "); Serial.println(gyro.gyro.x, 4);
  Serial.print("Y: "); Serial.println(gyro.gyro.y, 4);
  Serial.print("Z: "); Serial.println(gyro.gyro.z, 4);

  // Print temperature
  Serial.print("-- Temperature (C): ");
  Serial.println(temp.temperature, 2);

  Serial.println(""); // Blank line between readings
  delay(500); // Wait half a second
}