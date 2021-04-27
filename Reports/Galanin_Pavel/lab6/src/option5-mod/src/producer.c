#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <string.h>
#include <errno.h>
#include <mqueue.h>

mqd_t get_opened_message_queue(const char message_queue_name[]);
void send_message_queue(const char message[], mqd_t sndHndl);

int main(void)
{
    printf("Send some mesage.\n");

    //Открываем очередь
    mqd_t aaa = get_opened_message_queue("/message");

    //посылаем сообщение в очередь
    send_message_queue("123", aaa);
    send_message_queue("456", aaa);
    send_message_queue("789", aaa);

    return 0;
}

mqd_t get_opened_message_queue(const char message_queue_name[])
{
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
        printf("\t\tError %d (%s) mq_open for send.\n", errno, strerror (errno));
        exit(-1);
    }

    printf("\tOpened mqd_t of %d.\n", sndHndl);

    return sndHndl;
}

void send_message_queue(const char message[], mqd_t sndHndl)
{
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

    printf("\tSend mqd_t of %d.\n", sndHndl);
}
