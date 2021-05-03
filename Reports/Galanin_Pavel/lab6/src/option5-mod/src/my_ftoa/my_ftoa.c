#include "my_ftoa.h"

char* my_ftoa(float number)
{
    char* str = (char*) calloc(100, sizeof(char));
    if (str == NULL)
    {
        printf("Память не выделилась\n");
        return NULL;
    }

    sprintf(str, "%lf", number);

    char* result = (char*) calloc(strlen(str), sizeof(char));
    if (str == NULL)
    {
        printf("Память не выделилась\n");
        return NULL;
    }

    strcpy(result, str);
    free(str);

    return result;
}