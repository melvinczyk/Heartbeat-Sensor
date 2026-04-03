# Heartbeat Sensor

A handheld sensor device based on the heartbeat sensors from Call of Duty and Pulse's gadget from Rainbow Six Siege, built out on real hardware with extra features on top.

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
