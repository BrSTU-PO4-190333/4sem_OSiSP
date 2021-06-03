#ifndef __MESSAGE_QUEUE_H__
    #define __MESSAGE_QUEUE_H__

    #include <stdio.h>  // printf()
    #include <stdlib.h> // exit()
    #include <string.h> // strlen()
    #include <errno.h>  // strerror() errno
    #include <mqueue.h> // mq_open() mq_send() mq_receive() mq_unlink()

    // функция открывает очередь по строке и возвращает номер очереди
    mqd_t get_opened_message_queue(const char message_queue_name[]);
    // функция отправляет сообзение в очередь
    void send_message_queue(const char message[], mqd_t sndHndl);
    // функция принимает сообщение из очереди и возвращает строку (её нужно очищать!)
    char* reveiving_message_queue(mqd_t rcHndl);
    // функция удаляет очередь
    void delete_message_queue(const char message_queue_name[]);
#endif