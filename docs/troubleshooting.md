# Troubleshooting

## Camera initialization failure
Check USB connection, camera availability, device index `0`, OpenCV
availability and target permissions.

## Image storage failure
Check `/home/root/camera_images`, permissions, free storage and JPEG codec
support. Review `[STORAGE]` messages.

## Resolution/FPS differs
The application requests 640×480 at 30 FPS but reads back the values reported
by the camera, so driver/device capability can affect the final values.

## QNX Screen
The supplied source does not contain QNX Screen API implementation. Any
future display/UI should be documented as a separate module after its actual
source is available.
