#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    printf("Порождение процесса 1 PID = %d PPID = %d\n", getppid(), getppid());

    // Порождение второго процесса
    if ( (pid = fork()) == -1 )
        printf("Ошибка!\n");
    else if (pid == 0) {
        printf("Порождение процесса 2 PID = %d PPID = %d\n", getpid(), getppid());
    
        // Порождение четвертого процесса
        if ( (pid = fork()) == -1 )
            printf("Ошибка!\n");
        else if (pid == 0) {
            printf("Порождение процесса 4 PID = %d PPID = %d\n", getpid(), getppid());
            printf("Завершился процесс 4 PID = %d PPID = %d\n", getpid(), getppid());
            execl("/bin/ls", "ls", NULL);
        }
        printf("Завершился процесс 2 PID = %d PPID = %d\n", getpid(), getppid());
        exit(0);
    } else sleep(1); //задержка родительского процесса

    // Порождение третьего процесса
    if ( (pid = fork()) == -1 )
        printf("Ошибка!\n");
    else if (pid == 0) {
        printf("Порождение 3 PID = %d PPID = %d\n", getpid(), getppid());
        printf("Завершился процесс 3: PID = %d, PPID = %d\n", getpid(), getppid());
        exit(0);
    } else sleep(1);
    printf("Завершился процесс 1: PID = %d, PPID = %d\n", getpid(), getppid());
    exit(0);
    return 1;
}
