# QNX USB Camera Interface

Modular USB camera image-capture application for QNX Neutrino RTOS using the
OpenCV C API.

## Features
- USB camera index `0`
- Requested `640 × 480`, `30 FPS`
- Reads actual camera configuration
- Storage directory `/home/root/camera_images`
- Immediate first capture
- Subsequent capture every 10 seconds
- Timestamp-based JPEG filenames
- JPEG quality `95`
- Capture counter
- SIGINT/SIGTERM graceful shutdown

## Source

```text
src/
├── camera.c
├── camera.h
├── image_capture.c
├── image_capture.h
├── image_storage.c
├── image_storage.h
└── main.c
```

| Module | Role |
|---|---|
| `camera.c/.h` | Camera initialization, configuration, capture and release |
| `image_capture.c/.h` | 10-second scheduling and capture count |
| `image_storage.c/.h` | Directory handling, filename generation and JPEG storage |
| `main.c` | Application orchestration and shutdown |

## Runtime flow

```text
Start → Storage Init → Camera Init → Capture Controller Init
                                      ↓
                              Main Loop
                           ↙              ↘
                    10 sec due?          No
                         ↓                ↓
                    Capture frame     100 ms delay
                         ↓                ↖
                    Save JPEG
                         ↓
                  Increment count
                         ↓
                  SIGINT / SIGTERM
                         ↓
                   Release camera
                         ↓
                         Exit
```

## Output

Images are stored in:

```text
/home/root/camera_images
```

Example:

```text
image_20260923_144530.jpg
```

## Development context

QNX Neutrino RTOS, QNX SDP 8.0, QNX Momentics IDE, Raspberry Pi 4 and USB
webcam.

## Source-of-truth note

This repository is extracted from the supplied `QNX_Project_CODES.md`. The
supplied source contains the seven modules above. It does **not** contain a
QNX Screen implementation, so no Screen source files have been invented.

## Documentation

See `docs/` for architecture, QNX setup, deployment, testing,
troubleshooting and project-report material.
