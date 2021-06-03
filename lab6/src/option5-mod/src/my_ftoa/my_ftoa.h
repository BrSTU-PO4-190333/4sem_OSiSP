#ifndef __MY_FTOA_H__
    #define __MY_FTOA_H__

    #include <stdio.h>  //sprintf() printf()
    #include <stdlib.h> //calloc() free()
    #include <string.h> //strlen() strcpy()

    // функция преобразует float в строку и возвращает её (её надо очищать)
    char* my_ftoa(float number);
#endif