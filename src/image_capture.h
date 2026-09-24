#ifndef IMAGE_CAPTURE_H

#define IMAGE_CAPTURE_H



#include "camera.h"



/*

 * Capture interval

 *

 * Image will be captured every 10 seconds.

 */

#define IMAGE_CAPTURE_INTERVAL_SECONDS 10



/*

 * Capture controller structure

 */

typedef struct

{

    time_t last_capture_time;



    int interval_seconds;



    unsigned long image_count;



} ImageCapture;





/*

 * Initialize image capture controller

 */

void image_capture_init(

    ImageCapture *capture

);





/*

 * Determine whether it is time to capture

 *

 * Returns:

 *   1 -> capture required

 *   0 -> wait

 */

int image_capture_is_due(

    ImageCapture *capture

);





/*

 * Record successful capture

 */

void image_capture_record(

    ImageCapture *capture

);





/*

 * Get number of captured images

 */

unsigned long image_capture_get_count(

    ImageCapture *capture

);



#endif
