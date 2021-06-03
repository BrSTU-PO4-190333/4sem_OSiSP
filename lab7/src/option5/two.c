#include <unistd.h>
#include <stdio.h>      //printf()
#include <stdlib.h>     //rand()
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>       //time(), localetime()

int get_random(int x1, int x2);
void print_real_time();

int main() {
    char symbols[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtVvUuWwXxYyZz";    //символы
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

    (void)umask(0);
    while (1)                                   //бесконечный цикл
    {
        sem_wait(get);
        pthread_mutex_lock(&mutex);
        int fd = open(                          //открываем файл
            "file.bin",                         //*.bin - бинарный файл
            O_RDWR,
            0777                                //- rwx rwx rwx (0 111 111 111)
        );
        
        char str[1024];                         //строку, которую возьмем из файла
        read(fd, &str, sizeof(str));            //записали данные в строку

        print_real_time();
        printf(
            "Process %d get message: %s\n",     //форматная строка
            getpid(),                           //PID - номер процесса
            str                                 //строка
        );

        print_real_time();
        int length = atoi(str);                 //длина строки (длины цифры)
        for(int i = 0; i < length; i++)         //выводим (length - 1) рандомную букву
        {
            int random_number = get_random(0, sizeof(symbols)); //рандом число из массива букв
            char random_character = symbols[random_number];     //получаем символ
            printf("%c", random_character);     //печатаем символ
        }
        printf("\n\n");

        close(fd);                              //закрываем файл
        pthread_mutex_unlock(&mutex);
        sem_post(put);
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