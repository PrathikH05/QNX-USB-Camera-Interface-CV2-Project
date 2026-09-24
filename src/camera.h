#ifndef CAMERA_H

#define CAMERA_H



#include <opencv2/core/core_c.h>

#include <opencv2/videoio/videoio_c.h>



/*

 * Camera configuration

 */

#define CAMERA_DEVICE_INDEX       0

#define CAMERA_WIDTH              640

#define CAMERA_HEIGHT             480

#define CAMERA_FPS                30



/*

 * Camera structure

 */

typedef struct

{

    CvCapture *capture;



    int width;

    int height;

    int fps;



    int initialized;



} Camera;



/*

 * Initialize USB camera

 *

 * Returns:

 *   0  -> success

 *  -1  -> failure

 */

int camera_init(Camera *camera);



/*

 * Capture one frame from camera

 *

 * Returns:

 *   IplImage* -> captured frame

 *   NULL      -> failure

 *

 * The returned image belongs to OpenCV.

 * Do not release it manually.

 */

IplImage *camera_capture_frame(Camera *camera);



/*

 * Release camera resources

 */

void camera_release(Camera *camera);



/*

 * Check whether camera is initialized

 */

int camera_is_ready(Camera *camera);



#endif
