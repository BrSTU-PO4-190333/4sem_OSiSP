#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <string.h>
#include <errno.h>
#include <mqueue.h>

mqd_t get_opened_message_queue(const char message_queue_name[]);
void reveiving_message_queue(mqd_t rcHndl);
void delete_message_queue(const char message_queue_name[]);

int main(void)
{
    printf("Receive some mesage.\n");

    //открываем очередь
    mqd_t bbb = get_opened_message_queue("/message");

    //принимаем сообщение из очереди
    reveiving_message_queue(bbb);
    reveiving_message_queue(bbb);
    reveiving_message_queue(bbb);

    //удаляем очередь
    delete_message_queue("/message");

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
        printf("\t\tError %d (%s) mq_open for send.\n", errno, strerror(errno));
        exit(-1);
    }

    printf("\tOpened mqd_t of %d.\n", sndHndl);

    return sndHndl;
}

void reveiving_message_queue(mqd_t rcHndl)
{
    char buffer[2048];

    printf("\tReceiving mqd_t %d.\n", rcHndl);
    //принимаем сообщение из очереди
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

    printf("\tReceived: [%s].\n", buffer);
}

void delete_message_queue(const char message_queue_name[])
{
    if (mq_unlink(message_queue_name) < 0)
    {
        printf("Warning %d (%s) mq_unlink.\n", errno, strerror(errno));
    }
}
