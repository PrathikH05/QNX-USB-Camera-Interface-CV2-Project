# Testing

| Test | Expected result |
|---|---|
| Storage directory absent | Created |
| Storage directory exists | Accepted |
| Camera connected | Initializes |
| Camera unavailable | Initialization fails with message |
| 10-second interval reached | Capture attempted |
| Capture succeeds | JPEG saved and count incremented |
| Capture fails | Error reported and retry continues |
| SIGINT/SIGTERM | Loop exits and camera is released |

Verify filenames use:

```text
image_YYYYMMDD_HHMMSS.jpg
```

The first capture is eligible immediately because the initial capture time is
set one interval in the past.
