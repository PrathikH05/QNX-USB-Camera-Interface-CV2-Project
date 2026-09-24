#include "image_storage.h"



#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>



#include <sys/stat.h>

#include <sys/types.h>



#include <opencv2/imgcodecs/imgcodecs_c.h>





/*

 * Initialize storage directory

 */

int image_storage_init(const char *directory)

{

    struct stat st;



    if (directory == NULL)

    {

        printf("[STORAGE] Error: Directory is NULL\n");

        return -1;

    }



    /*

     * Check whether directory already exists

     */

    if (stat(directory, &st) == 0)

    {

        if (S_ISDIR(st.st_mode))

        {

            printf("[STORAGE] Storage directory exists:\n");

            printf("[STORAGE] %s\n", directory);



            return 0;

        }



        printf("[STORAGE] ERROR: Path exists but is not a directory\n");



        return -1;

    }



    /*

     * Create directory

     */

    if (mkdir(directory, 0777) != 0)

    {

        printf("[STORAGE] ERROR: Cannot create directory\n");

        printf("[STORAGE] Path: %s\n", directory);



        return -1;

    }



    printf("[STORAGE] Directory created:\n");

    printf("[STORAGE] %s\n", directory);



    return 0;

}





/*

 * Generate timestamp-based filename

 */

int image_storage_generate_filename(

    const char *directory,

    char *filename,

    int filename_size)

{

    time_t current_time;

    struct tm time_info;



    if (directory == NULL ||

        filename == NULL ||

        filename_size <= 0)

    {

        return -1;

    }



    /*

     * Get current time

     */

    current_time = time(NULL);



    /*

     * QNX/POSIX-compatible localtime

     */

    if (localtime_r(&current_time, &time_info) == NULL)

    {

        printf("[STORAGE] ERROR: Unable to obtain system time\n");

        return -1;

    }



    /*

     * Example:

     *

     * /home/root/camera_images/image_20260923_144530.jpg

     */

    snprintf(

        filename,

        filename_size,

        "%s/image_%04d%02d%02d_%02d%02d%02d.jpg",



        directory,



        time_info.tm_year + 1900,

        time_info.tm_mon + 1,

        time_info.tm_mday,



        time_info.tm_hour,

        time_info.tm_min,

        time_info.tm_sec

    );



    return 0;

}





/*

 * Save image

 */

int image_storage_save(

    const char *directory,

    const IplImage *image)

{

    char filename[512];



    int compression_params[2];



    if (directory == NULL)

    {

        printf("[STORAGE] Error: Directory is NULL\n");

        return -1;

    }



    if (image == NULL)

    {

        printf("[STORAGE] Error: Image is NULL\n");

        return -1;

    }



    /*

     * Generate filename

     */

    if (image_storage_generate_filename(

            directory,

            filename,

            sizeof(filename)) != 0)

    {

        return -1;

    }



    /*

     * JPEG quality

     *

     * 95 = high quality

     */

    compression_params[0] = CV_IMWRITE_JPEG_QUALITY;

    compression_params[1] = 95;



    /*

     * Save JPEG

     */

    if (!cvSaveImage(

            filename,

            image,

            compression_params))

    {

        printf("[STORAGE] ERROR: Failed to save image\n");

        printf("[STORAGE] File: %s\n", filename);



        return -1;

    }



    printf("[STORAGE] Image saved successfully:\n");

    printf("[STORAGE] %s\n", filename);



    return 0;

}
