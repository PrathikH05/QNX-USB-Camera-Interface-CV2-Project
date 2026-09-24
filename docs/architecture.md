# Architecture

The implementation is divided into camera, capture-control, storage and
application layers.

### Camera
`camera.c/.h` owns the OpenCV `CvCapture` handle and provides initialization,
frame acquisition, readiness and release.

### Capture control
`image_capture.c/.h` uses `time()` to determine whether the 10-second interval
has elapsed and counts successful captures.

### Storage
`image_storage.c/.h` checks/creates the storage directory, generates a
timestamp filename and writes a JPEG.

### Application
`main.c` coordinates initialization, the main loop and shutdown.

```text
USB Webcam → OpenCV CvCapture → IplImage → JPEG storage
                                      ↓
                            /home/root/camera_images/
```
