#ifndef __MESSAGE_QUEUE_H__
    #define __MESSAGE_QUEUE_H__

    #include <stdio.h>  //printf()
    #include <stdlib.h> //exit()
    #include <string.h>
    #include <errno.h>
    #include <mqueue.h>

    mqd_t get_opened_message_queue(const char message_queue_name[]);
    void send_message_queue(const char message[], mqd_t sndHndl);
    char* reveiving_message_queue(mqd_t rcHndl);
    void delete_message_queue(const char message_queue_name[]);
#endif