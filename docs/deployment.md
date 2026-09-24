# Deployment

```text
Momentics / Host
      ↓ build
Application executable
      ↓ transfer
Raspberry Pi 4 + QNX
      ↓
USB webcam
      ↓
/home/root/camera_images/
```

At runtime the application initializes storage and camera, starts the
10-second controller, captures/saves images, and exits on SIGINT or SIGTERM.

Use console messages prefixed `[MAIN]`, `[CAMERA]`, `[STORAGE]` and `[CAPTURE]`
to verify operation.
