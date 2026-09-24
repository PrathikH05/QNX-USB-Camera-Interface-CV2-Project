#ifndef IMAGE_STORAGE_H

#define IMAGE_STORAGE_H



#include <opencv2/core/core_c.h>



/*

 * Default image directory

 */

#define IMAGE_STORAGE_PATH "/home/root/camera_images"



/*

 * Create image storage directory

 *

 * Returns:

 *   0  -> success

 *  -1  -> failure

 */

int image_storage_init(const char *directory);



/*

 * Save an image with automatically generated filename.

 *

 * Example:

 *

 * /home/root/camera_images/image_20260923_144530.jpg

 *

 * Returns:

 *   0  -> success

 *  -1  -> failure

 */

int image_storage_save(

    const char *directory,

    const IplImage *image

);



/*

 * Generate image filename

 */

int image_storage_generate_filename(

    const char *directory,

    char *filename,

    int filename_size

);



#endif
