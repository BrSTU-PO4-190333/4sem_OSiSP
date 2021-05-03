#include "message_queue.h"

mqd_t get_opened_message_queue(const char message_queue_name[])
{
    printf("\t\"queue\": \"%s\" - открывается очередь\n", message_queue_name);

    struct mq_attr mqAttr;
    mqAttr.mq_maxmsg = 10;
    mqAttr.mq_msgsize = 1024;

    mqd_t sndHndl = mq_open(
        message_queue_name,
        O_RDWR | O_CREAT,
        S_IWUSR | S_IRUSR,
        &mqAttr
    );

    if (sndHndl < 0)
    {
        printf("\t\tError %d (%s) mq_open for send.\n", errno, strerror(errno));
        exit(-1);
    }

    printf("\tmqd_t %d - очередь открыта успешно\n", sndHndl);

    return sndHndl;
}

void send_message_queue(const char message[], mqd_t sndHndl)
{
    printf("\t\"message\": \"%s\" - сообщение отправляется\n", message);

    int rc = mq_send(
        sndHndl,
        message,
        strlen(message),
        1
    );

    if (rc < 0)
    {
        printf ("\t\tError %d (%s) mq_send.\n", errno, strerror(errno));
        exit (-1);
    }

    printf("\tmqd_t %d - сообщение отправлено успешно\n", sndHndl);
}

char* reveiving_message_queue(mqd_t rcHndl)
{
    char buffer[2048];

    printf("\tmqd_t %d - получаем сообщение\n", rcHndl);

    int rc = mq_receive(
        rcHndl,
        buffer,
        sizeof(buffer),
        NULL
    );

    if (rc < 0)
    {
        printf("\t\tError %d (%s) mq_receive.\n", errno, strerror(errno));
        exit(-1);
    }

    char* msg = (char*) calloc(strlen(buffer), sizeof(char));
    strcpy(msg, buffer);

    printf("\t\"message\": \"%s\" - сообщение получено успешно\n", msg);

    return msg;
}

void delete_message_queue(const char message_queue_name[])
{
    printf("\t\"queue\": \"%s\" - очередь закрывается\n", message_queue_name);
    if (mq_unlink(message_queue_name) < 0)
    {
        printf("Warning %d (%s) mq_unlink.\n", errno, strerror(errno));
    }
    printf("\t\"queue\": \"%s\" - очередь закрыта успешно\n", message_queue_name);
}
