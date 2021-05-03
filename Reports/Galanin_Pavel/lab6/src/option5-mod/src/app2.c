#include <math.h>
#include "message_queue/message_queue.h"
#include "my_ftoa/my_ftoa.h"
#include "print_real_time/print_real_time.h"

int main(void)
{
    print_real_time();
    mqd_t bbb = get_opened_message_queue("/abc");       // открываю очередь /abc

    print_real_time();
    char* msg_a = reveiving_message_queue(bbb);         // получаю сообщение с очереди /abc

    print_real_time();
    char* msg_b = reveiving_message_queue(bbb);         // получаю сообщение с очереди /abc

    print_real_time();
    char* msg_c = reveiving_message_queue(bbb);         // получаю сообщение с очереди /abc

    print_real_time();
    delete_message_queue("/abc");                       // удаляем очередь /abc

    float a = atof(msg_a);                              // char* to float
    free(msg_a);                                        // очистка памяти

    float b = atof(msg_b);                              // char* to float
    free(msg_b);                                        // очистка памяти

    float c = atof(msg_c);                              // char* to float
    free(msg_c);                                        // очистка памяти

    float p = (a + b + c) / 2;                          // полупериметр
    float S = sqrt( p * (p - a) * (p - b) * (p - c) );  // площадь через теорему Герона
    printf(
        "\nS = sqrt(\n\t%f *\n\t* (%f - %f) *\n\t* (%f - %f) *\n\t* (%f - %f)\n) = %f\n\n",
        p, p, a, p, b, p, c, S
    );

    char* message_S = my_ftoa(S);    // double to char*

    print_real_time();
    mqd_t queue_s = get_opened_message_queue("/s");     // открытие очереди /s

    print_real_time();
    send_message_queue(message_S, queue_s);             // отправка сообщения в очередь /s

    free(message_S);                                    // очистка памяти

    return 0;
}
