#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd;
    size_t sizeRead, sizeWrite;
    char string[255];

    /* Считываем данные из стандартного потока ввода */
    sizeRead = read(0, string, 255);
    if (sizeRead <= 0) {
        printf("Can\'t read.\n");
        return(-1);
    }

    (void) umask(0);
    if ((fd = open("myfile", O_WRONLY | O_CREAT, 0666)) < 0)
    {
        printf("Can\'t open file\n");
        return(-1);
    }
    
    /* Запись в файл */
    sizeWrite = write(fd, string, sizeRead);

    /* Вывод на экран */
    //sizeWrite = write(1, string, sizeRead);
    if (sizeWrite != sizeRead)
    {
        printf("Can\'t write all string\n");
        return(-1);
    }
    
    if (close(fd) < 0)
    {
        printf("Can\'t close file\n");
    }

    return 0;
}