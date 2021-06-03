#include <unistd.h>
#include <stdio.h>      //printf()
#include <stdlib.h>     //rand()
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>       //time(), localtime

int get_random(int a, int b);
void print_real_time();

int main()
{
    sem_t* get = sem_open(
        "sem_one",                              //const char* name
        O_CREAT,                                //int oflag
        0777,                                   //mode_t mode
        0                                       //unsigned int value
    );
    sem_t* put = sem_open(
        "sem_two",                              //const char* name
        O_CREAT,                                //int oflag
        0777,                                   //mode_t mode
        0                                       //unsigned int value
    );
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    sem_post(put);
    (void)umask(0);

    while (1)
    {
        sem_wait(put);
        print_real_time();                      //печать реального времени
        printf("Enter the symbol: ");
        pthread_mutex_lock(&mutex);
        int fd = open(                          //открываем файл
            "file.bin",                         //*.bin - бинарный файл
            O_CREAT | O_WRONLY,
            0777                                //- rwx rwx rwx (0 111 111 111)
        );
        
        //Если вводить по одному символу,
        //то сообщение может отправляться несколько раз,
        //при вводе нескольких символов (а не одного).
        //Эту проблему решает строка.
        char str[1024];                         //инициализировали строку
        scanf("%s", str);                       //вводим строку
        char character = str[0];                //взяли первый символ со строки

        int rand_number = get_random(1, 35);    //рандомное число [1; 35]
        print_real_time();                      //печать реального времени
        printf(                                 //печать сообщения об отправке
            "Process %d send random_number: %d\n\n",
            getpid(),                           //PID - номер процесса
            rand_number                         //рандомное число
        );

        char msg[1024];                         //инициализация строки для сообщения
        sprintf(msg, "%d", rand_number);        //в сообщение записали рандомное число
        write(fd, msg, sizeof(msg));            //записали сообщение в файл

        close(fd);                              //закрываем файл
        pthread_mutex_unlock(&mutex);
        sem_post(get);
    }

    pthread_mutex_destroy(&mutex);
    sem_close(put);
    sem_close(get);

    return 0;
}

int get_random(int x1, int x2)
{
    int a = x1 < x2 ? x1 : x2;                  //a = min(a, b)
    int b = x1 > x2 ? x1 : x2;                  //b = max(a, b)
    return rand() % (b - a + 1) + a;            //random [a; b]
}

void print_real_time()
{
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    printf(
        "%02d:%02d:%02d : ",
        1 + ltm->tm_hour,                       // часы
        1 + ltm->tm_min,                        // минуты
        1 + ltm->tm_sec                         // секунды
    );
}