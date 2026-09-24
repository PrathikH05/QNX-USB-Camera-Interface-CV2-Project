#include <stdio.h>

#include <stdlib.h>

#include <signal.h>

#include <unistd.h>



#include <opencv2/core/core_c.h>



#include "camera.h"

#include "image_capture.h"

#include "image_storage.h"





/*

 * Global running flag

 */

static volatile sig_atomic_t running = 1;





/*

 * Ctrl+C signal handler

 */

static void signal_handler(int signal_number)

{

    (void)signal_number;



    printf("\n[MAIN] Shutdown signal received\n");



    running = 0;

}





/*

 * Main application

 */

int main(void)

{

    Camera camera;



    ImageCapture capture_controller;



    IplImage *frame;



    /*

     * Register Ctrl+C handler

     */

    signal(

        SIGINT,

        signal_handler

    );



    signal(

        SIGTERM,

        signal_handler

    );





    printf("\n");

    printf("========================================\n");

    printf(" QNX USB CAMERA IMAGE CAPTURE SYSTEM\n");

    printf("========================================\n");

    printf("\n");





    /*

     * -------------------------------------

     * STEP 1

     * Initialize image storage

     * -------------------------------------

     */

    printf("[MAIN] Initializing image storage...\n");



    if (image_storage_init(

            IMAGE_STORAGE_PATH) != 0)

    {

        printf(

            "[MAIN] ERROR: Storage initialization failed\n"

        );



        return EXIT_FAILURE;

    }





    /*

     * -------------------------------------

     * STEP 2

     * Initialize camera

     * -------------------------------------

     */

    printf("[MAIN] Initializing camera...\n");



    if (camera_init(&camera) != 0)

    {

        printf(

            "[MAIN] ERROR: Camera initialization failed\n"

        );



        return EXIT_FAILURE;

    }





    /*

     * -------------------------------------

     * STEP 3

     * Initialize capture controller

     * -------------------------------------

     */

    image_capture_init(

        &capture_controller

    );





    printf("\n");

    printf("----------------------------------------\n");

    printf("System ready\n");

    printf("Camera : USB\n");

    printf("Resolution : %dx%d\n",

           camera.width,

           camera.height);



    printf("Capture interval : %d seconds\n",

           IMAGE_CAPTURE_INTERVAL_SECONDS);



    printf("Storage : %s\n",

           IMAGE_STORAGE_PATH);



    printf("----------------------------------------\n");

    printf("\n");





    /*

     * -------------------------------------

     * MAIN LOOP

     * -------------------------------------

     */

    while (running)

    {

        /*

         * Check whether 10 seconds have passed

         */

        if (image_capture_is_due(

                &capture_controller))

        {

            printf("\n");

            printf("[MAIN] Capture interval reached\n");



            /*

             * Capture frame

             */

            frame =

                camera_capture_frame(

                    &camera

                );



            if (frame == NULL)

            {

                printf(

                    "[MAIN] ERROR: Frame capture failed\n"

                );



                /*

                 * Wait before retry

                 */

                sleep(1);



                continue;

            }





            printf(

                "[MAIN] Frame captured: %dx%d\n",

                frame->width,

                frame->height

            );





            /*

             * Save image

             */

            if (image_storage_save(

                    IMAGE_STORAGE_PATH,

                    frame) == 0)

            {

                /*

                 * Record successful capture

                 */

                image_capture_record(

                    &capture_controller

                );

            }

            else

            {

                printf(

                    "[MAIN] ERROR: Image storage failed\n"

                );

            }

        }





        /*

         * Small delay prevents the CPU from

         * continuously polling at 100%.

         */

        usleep(100000);

    }





    /*

     * -------------------------------------

     * SHUTDOWN

     * -------------------------------------

     */

    printf("\n");

    printf("----------------------------------------\n");

    printf("Shutting down application...\n");

    printf("----------------------------------------\n");





    camera_release(

        &camera

    );





    printf(

        "[MAIN] Total images captured: %lu\n",

        image_capture_get_count(

            &capture_controller

        )

    );





    printf("[MAIN] Application terminated\n");



    return EXIT_SUCCESS;

}
