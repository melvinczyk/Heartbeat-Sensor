# Heartbeat Sensor

A handheld sensor device based on the heartbeat sensors from Call of Duty and Pulse's gadget from Rainbow Six Siege, built out on real hardware with extra features on top.

<img width="250" height="143" alt="image" src="https://github.com/user-attachments/assets/87f828cc-af1e-4397-bb24-91671b7b178f" />

<img width="250" height="316" alt="image" src="https://github.com/user-attachments/assets/5b5d219f-aba3-48db-bb30-d0c294b3c9b5" />

<img width="250" height="316" alt="image" src="https://www.elecrow.com/media/catalog/product/e/s/esp32_advance_hmi_5inch_display.jpg" />


## Hardware

- **Display & Processor**: 5" CrowPanel Advance (ESP32-S3)
- **mmWave Radar**: Detects presence and movement of multiple targets
- **IMU**: Tracks orientation and motion
- **ToF Sensor**: Measures distance and point cloud

## What It Does

Unlike the ones it's based on, this goes beyond just showing blips on a screen. It pulls data from all three sensors to:

- Detect and track people nearby using the mmWave radar
- Track which way the device is pointing using the IMU
- Measure how far away things are with the ToF sensor
- Build a live 3D point cloud of the in front around the user
- Show it all on a 5" touchscreen

## How It Differs from the Games

The in-game versions are basically just 2D radar pings. This one actually maps out the space around you in 3D instead of just telling you something is nearby.
