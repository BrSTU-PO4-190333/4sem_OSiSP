#include <unistd.h>     //fork()
#include <sys/types.h>
#include <stdio.h>      //printf()
#include <signal.h>     //SIGUSR1
#include <math.h>       //sqrt()

#include "message_queue/message_queue.h"
#include "my_ftoa/my_ftoa.h"

void my_handler(int nsig);
void input_a_b_c(double* a, double* b, double* c);
void send_a_b_c(double a, double b, double c);
void get_S();
void get_a_b_c();

int main()
{
    pid_t pid;

    // print 0
    printf("::::: start [process 0] PID = %d PPID = %d :::::\n", getpid(), getppid());

    signal(SIGUSR1, my_handler);

    double a,b,c;
    input_a_b_c(&a, &b, &c);

    if ((pid = fork()) == -1)                               //процесс не создался
    {
        printf("Err\n");
    }
    else if (pid > 0)                                       //в родительском процессе
    {
        printf("\t= = = = = start part 1 = = = = =\n");
        printf("\t::::: start [parent process] PID = %d PPID = %d :::::\n", getpid(), getppid());
        send_a_b_c(a, b, c);
        printf("\t::::: kill [parent process] PID = %d PPID = %d :::::\n", getpid(), getppid());
        printf("\t= = = = = end part 1 = = = = =\n");

        kill(pid, SIGUSR1);
        sleep(2);

        printf("\t= = = = = start part 3 = = = = =\n");
        printf("\t::::: respawn [parent process] PID = %d PPID = %d :::::\n", getpid(), getppid());
        get_S();
        printf("\t::::: end [parent process] PID = %d PPID = %d :::::\n", getpid(), getppid());
        printf("\t= = = = = end part 3 = = = = =\n");
        exit(0);
    }
    else if (pid == 0)                                      //в дочернем процессе
    {
        printf("\t= = = = = start part 2 = = = = =\n");
        printf("\t::::: start [child process] PID = %d PPID = %d :::::\n", getpid(), getppid());
        get_a_b_c();
        printf("\t::::: kill [child process] PID = %d PPID = %d :::::\n", getpid(), getppid());
        printf("\t= = = = = end part 2 = = = = =\n");

        kill(getppid(), SIGUSR1);

        printf("\t= = = = = start part 4 = = = = =\n");
        printf("\t::::: respawn [child process] PID = %d PPID = %d :::::\n", getpid(), getppid());
        printf("\t::::: end [child process] PID = %d PPID = %d :::::\n", getpid(), getppid());
        printf("\t= = = = = end part 4 = = = = =\n");
        //exit(0);
    }
    printf("::::: end [process 0] PID = %d PPID = %d :::::\n", getpid(), getppid());

    return 0;
}

void my_handler(int nsig)
{
    printf("\t= = = = = my_handler = = = = =\n");
}

void input_a_b_c(double* a, double* b, double* c)
{
    printf("a = ");
    scanf("%lf", a);                                        // ввод стороны треугольника A

    printf("b = ");
    scanf("%lf", b);                                        // ввод стороны треугольника B

    printf("c = ");
    scanf("%lf", c);                                        // ввод стороны треугольника С

    if (!(*a + *b > *c))                                    // условие существование треугольника
    {
        printf("Not triangle\n");
        printf("%lf * %lf not > %lf\n", *a, *b, *c);
        printf("%lf not > %lf\n", *a + *b, *c);
        printf("\n");

        input_a_b_c(a, b, c);
        return;
    }
    else
    {
        printf("Is triagle\n");
        printf("%lf * %lf > %lf\n", *a, *b, *c);
        printf("%lf > %lf\n", *a + *b, *c);
        printf("\n");
    }
}

void send_a_b_c(double a, double b, double c)
{
    char* string_a = my_ftoa(a);                            // double to char*
    char* string_b = my_ftoa(b);                            // double to char*
    char* string_c = my_ftoa(c);                            // double to char*

    mqd_t queue_send_a_b_c = get_opened_message_queue("/abc");// открытие очереди /abc

    send_message_queue(string_a, queue_send_a_b_c);         // отправка сообщения в очередь /abc
    free(string_a);                                         // очистка памяти

    send_message_queue(string_b, queue_send_a_b_c);         // отправка сообщения в очередь /abc
    free(string_b);                                         // очистка памяти

    send_message_queue(string_c, queue_send_a_b_c);         // отправка сообщения в очередь /abc
    free(string_c);                                         // очистка памяти
}

void get_S()
{
    mqd_t queue_get_s = get_opened_message_queue("/s");     // открытие очереди /s

    reveiving_message_queue(queue_get_s);                   // принятие сообщения из очереди /s

    delete_message_queue("/s");                             // удаление очереди /s
}

void get_a_b_c()
{
    mqd_t bbb = get_opened_message_queue("/abc");           // открываю очередь /abc

    char* msg_a = reveiving_message_queue(bbb);             // получаю сообщение с очереди /abc

    char* msg_b = reveiving_message_queue(bbb);             // получаю сообщение с очереди /abc

    char* msg_c = reveiving_message_queue(bbb);             // получаю сообщение с очереди /abc

    delete_message_queue("/abc");                           // удаляем очередь /abc

    float a = atof(msg_a);                                  // char* to float
    free(msg_a);                                            // очистка памяти

    float b = atof(msg_b);                                  // char* to float
    free(msg_b);                                            // очистка памяти

    float c = atof(msg_c);                                  // char* to float
    free(msg_c);                                            // очистка памяти

    float p = (a + b + c) / 2;                              // полупериметр
    float S = sqrt( p * (p - a) * (p - b) * (p - c) );      // площадь через теорему Герона
    printf(
        "\nS = sqrt(\n\t%f *\n\t* (%f - %f) *\n\t* (%f - %f) *\n\t* (%f - %f)\n) = %f\n\n",
        p, p, a, p, b, p, c, S
    );

    char* message_S = my_ftoa(S);                           // double to char*

    mqd_t queue_s = get_opened_message_queue("/s");         // открытие очереди /s

    send_message_queue(message_S, queue_s);                 // отправка сообщения в очередь /s

    free(message_S);                                        // очистка памяти
}