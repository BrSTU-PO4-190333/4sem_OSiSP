#include "my_ftoa.h"

char* my_ftoa(float number)
{
    char* str = (char*) calloc(100, sizeof(char));      // выделяем память под строку
    if (str == NULL)                                    // выделилась память?
    {
        printf("Память не выделилась\n");
        return NULL;
    }

    sprintf(str, "%f", number);                         // копируем float в строку

    char* result = (char*) calloc(strlen(str), sizeof(char));   // строка уже не длинны 100
    if (str == NULL)                                    // память выделилась
    {
        printf("Память не выделилась\n");
        return NULL;
    }

    strcpy(result, str);                                // result = str
    free(str);                                          // очищаем память

    return result;                                      // возвращем строку (её надо очищать!)
}