# QNX USB Camera Interface — Project Report

## Abstract
This project implements a modular USB camera image-capture application for a
QNX Neutrino RTOS target. It uses the OpenCV C API to initialize a USB camera,
capture frames periodically, generate timestamp-based filenames and store JPEG
images.

## Objectives
- Interface a USB webcam with a QNX embedded target.
- Configure camera parameters.
- Capture images at a fixed interval.
- Store timestamped JPEG images.
- Separate camera, scheduling and storage responsibilities.
- Release resources cleanly.

## Implementation
The supplied implementation contains seven files:
`camera.h`, `camera.c`, `image_storage.h`, `image_storage.c`,
`image_capture.h`, `image_capture.c`, and `main.c`.

## Future development
Potential extensions include configurable intervals, camera hot-plug recovery,
persistent configuration, additional formats, a user interface and
project-specific QNX BSP/IFS configuration.
