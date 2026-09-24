#include "image_capture.h"



#include <stdio.h>

#include <string.h>

#include <time.h>





/*

 * Initialize capture controller

 */

void image_capture_init(

    ImageCapture *capture)

{

    if (capture == NULL)

    {

        return;

    }



    memset(

        capture,

        0,

        sizeof(ImageCapture)

    );



    capture->interval_seconds =

        IMAGE_CAPTURE_INTERVAL_SECONDS;



    /*

     * Set last capture time to current time.

     *

     * We subtract the interval so that the

     * first image is captured immediately.

     */

    capture->last_capture_time =

        time(NULL) -

        capture->interval_seconds;



    capture->image_count = 0;



    printf("[CAPTURE] Capture controller initialized\n");



    printf("[CAPTURE] Interval: %d seconds\n",

           capture->interval_seconds);

}





/*

 * Check whether capture is due

 */

int image_capture_is_due(

    ImageCapture *capture)

{

    time_t current_time;



    if (capture == NULL)

    {

        return 0;

    }



    current_time = time(NULL);



    /*

     * Check elapsed time

     */

    if ((current_time -

         capture->last_capture_time)

        >= capture->interval_seconds)

    {

        return 1;

    }



    return 0;

}





/*

 * Record successful capture

 */

void image_capture_record(

    ImageCapture *capture)

{

    if (capture == NULL)

    {

        return;

    }



    capture->last_capture_time = time(NULL);



    capture->image_count++;



    printf(

        "[CAPTURE] Capture #%lu completed\n",

        capture->image_count

    );

}





/*

 * Get capture count

 */

unsigned long image_capture_get_count(

    ImageCapture *capture)

{

    if (capture == NULL)

    {

        return 0;

    }



    return capture->image_count;

}
