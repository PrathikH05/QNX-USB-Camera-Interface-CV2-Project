# QNX Setup

Target context:
- QNX Neutrino RTOS
- QNX SDP 8.0
- QNX Momentics IDE
- Raspberry Pi 4
- USB webcam

General workflow:
1. Boot the intended QNX image.
2. Connect the USB webcam.
3. Establish the host/target connection.
4. Ensure required OpenCV components are present.
5. Build for the target.
6. Transfer and run the executable.

The supplied source does not include a BSP buildfile or IFS configuration, so
those settings must match the QNX image actually used.
