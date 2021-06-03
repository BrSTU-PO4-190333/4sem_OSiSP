#include "message_queue.h"

mqd_t get_opened_message_queue(const char message_queue_name[])
{
    printf("\"queue\": \"%s\" - открывается очередь\n", message_queue_name);

    struct mq_attr mqAttr;                                  // создаем структуру
    mqAttr.mq_maxmsg = 10;                                  // максимальное количество сообщений
    mqAttr.mq_msgsize = 1024;                               // максимальная длина сообщения в байт

    mqd_t handler = mq_open(
        message_queue_name,                                 // название очереди
        O_RDWR | O_CREAT,                                   // int флаги
        S_IWUSR | S_IRUSR,                                  // флаги
        &mqAttr                                             // ссылка на структуру
    );

    if (handler < 0)                                        // если очередь не открылась
    {
        printf("Error %d (%s) mq_open for send.\n", errno, strerror(errno));
        exit(-1);
    }

    printf("mqd_t %d - очередь открыта успешно\n", handler);

    return handler;                                         // возвращаем номер очереди
}

void send_message_queue(const char message[], mqd_t handler)
{
    printf("\"message\": \"%s\" - сообщение отправляется\n", message);

    int rc = mq_send(
        handler,                                            // номер очереди
        message,                                            // сообщение
        strlen(message),                                    // длина сообщения
        1                                                   // приоритет
    );

    if (rc < 0)                                             // если сообщение не отправилось
    {
        printf("Error %d (%s) mq_send.\n", errno, strerror(errno));
        exit(-1);
    }

    printf("mqd_t %d - сообщение отправлено успешно\n", handler);
}

char* reveiving_message_queue(mqd_t handler)
{
    char buffer[2048];                                      // сюда запишется сообщение
    printf("mqd_t %d - получаем сообщение\n", handler);

    int rc = mq_receive(
        handler,                                            // номер очереди
        buffer,                                             // строка в которую запишется сообщение
        sizeof(buffer),                                     // длина строки
        NULL                                                // приоритет
    );

    if (rc < 0)
    {
        printf("Error %d (%s) mq_receive.\n", errno, strerror(errno));
        exit(-1);
    }

    char* msg = (char*) calloc(strlen(buffer), sizeof(char));// выделяем память (не 2048)
    strcpy(msg, buffer);                                    // msg = buffer

    printf("\"message\": \"%s\" - сообщение получено успешно\n", msg);

    return msg;                                             // возвращаем строку (её нужно очищать)
}

void delete_message_queue(const char message_queue_name[])
{
    printf("\"queue\": \"%s\" - очередь закрывается\n", message_queue_name);
    if (mq_unlink(message_queue_name) < 0)
    {
        printf("Warning %d (%s) mq_unlink.\n", errno, strerror(errno));
    }
    printf("\"queue\": \"%s\" - очередь закрыта успешно\n", message_queue_name);
}
