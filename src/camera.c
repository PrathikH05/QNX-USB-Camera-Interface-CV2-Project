#include "camera.h"



#include <stdio.h>

#include <string.h>



/*

 * Initialize USB camera

 */

int camera_init(Camera *camera)

{

    if (camera == NULL)

    {

        printf("[CAMERA] Error: Camera pointer is NULL\n");

        return -1;

    }



    memset(camera, 0, sizeof(Camera));



    camera->width  = CAMERA_WIDTH;

    camera->height = CAMERA_HEIGHT;

    camera->fps    = CAMERA_FPS;



    printf("[CAMERA] Initializing USB camera...\n");



    /*

     * Open default camera.

     *

     * Camera index 0 normally corresponds to the first

     * USB camera detected by the system.

     */

    camera->capture = cvCaptureFromCAM(CAMERA_DEVICE_INDEX);



    if (camera->capture == NULL)

    {

        printf("[CAMERA] ERROR: Unable to open USB camera\n");

        printf("[CAMERA] Check whether the camera is connected\n");

        return -1;

    }



    /*

     * Configure resolution

     */

    cvSetCaptureProperty(

        camera->capture,

        CV_CAP_PROP_FRAME_WIDTH,

        camera->width

    );



    cvSetCaptureProperty(

        camera->capture,

        CV_CAP_PROP_FRAME_HEIGHT,

        camera->height

    );



    /*

     * Configure FPS

     */

    cvSetCaptureProperty(

        camera->capture,

        CV_CAP_PROP_FPS,

        camera->fps

    );



    /*

     * Read actual camera configuration

     */

    camera->width =

        (int)cvGetCaptureProperty(

            camera->capture,

            CV_CAP_PROP_FRAME_WIDTH

        );



    camera->height =

        (int)cvGetCaptureProperty(

            camera->capture,

            CV_CAP_PROP_FRAME_HEIGHT

        );



    camera->fps =

        (int)cvGetCaptureProperty(

            camera->capture,

            CV_CAP_PROP_FPS

        );



    camera->initialized = 1;



    printf("[CAMERA] Camera initialized successfully\n");

    printf("[CAMERA] Resolution : %dx%d\n",

           camera->width,

           camera->height);



    printf("[CAMERA] FPS        : %d\n",

           camera->fps);



    return 0;

}





/*

 * Capture one frame

 */

IplImage *camera_capture_frame(Camera *camera)

{

    IplImage *frame;



    if (camera == NULL)

    {

        printf("[CAMERA] Error: Camera pointer is NULL\n");

        return NULL;

    }



    if (!camera->initialized)

    {

        printf("[CAMERA] Error: Camera is not initialized\n");

        return NULL;

    }



    frame = cvQueryFrame(camera->capture);



    if (frame == NULL)

    {

        printf("[CAMERA] ERROR: Failed to capture frame\n");

        return NULL;

    }



    return frame;

}





/*

 * Release camera

 */

void camera_release(Camera *camera)

{

    if (camera == NULL)

    {

        return;

    }



    if (camera->capture != NULL)

    {

        printf("[CAMERA] Releasing camera...\n");



        cvReleaseCapture(&camera->capture);



        camera->capture = NULL;

    }



    camera->initialized = 0;



    printf("[CAMERA] Camera released\n");

}





/*

 * Check camera status

 */

int camera_is_ready(Camera *camera)

{

    if (camera == NULL)

    {

        return 0;

    }



    return camera->initialized;

}
