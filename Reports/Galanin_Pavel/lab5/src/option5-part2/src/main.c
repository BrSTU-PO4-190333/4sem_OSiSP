#include <unistd.h> //read()
#include <stdio.h>  //printf()
#include <stdlib.h> //calloc(), realloc(), free(), atoi()
#include <string.h> //strcpy(), strlen(), strtok()

// Функция копирует массив слов и возвращает новый массив. Размер строки изменяется по ссылке
char** get_words_and_len_by_split(char* str, int* length, char* split);

// Функция выделяет память для нового массива слов, его копирует, возвращает.
char** get_copy_words(char** words, int length);

// Функция очищает динамическую память. Удаляет массив слов. 
void words_destructor(char** arr, int length);

int main()
{
    const int buffer_size = 1024;   // размер строки
    char str[buffer_size];          // инициализация статической строки
    read(0, str, buffer_size);      // Читает 0-евой поток. Записывает в str. Cимволов buffer_size
    printf("\nCтрока до:\n");
    printf("%s\n", str);            // печатаем полученную строку

    // выделяем память под массив. Разбиваем строки по '\n'
    int length = 0; // размер массива. изменится ниже
    char** arrWords = get_words_and_len_by_split(str, &length, "\n");
    // копируем массив, так как другой массив повертиться после функции strtok
    char** arrWords_copy = get_copy_words(arrWords, length);   
    
    // как разбили строки по пробелам, то у нас строки, наприме, такие:
    // "2739 pts/2    00:00:00 bash"
    // эту строку разбиваем по ' ' (пробелам), чтобы под 0-евым индексом получить число
    // [ "2739", "pts/2", "00:00:00", "bash" ]
    // { 0: "2739", 1: "pts/2", 2: "00:00:00", 3: "bash" }
    printf("\nСтрока после:\n");
    for (int i = 0; i < length; i++)
    {
        // получаем массив слов и размер массива
        int len = 0;// размер массива слов. изменится ниже
        char** list_words = get_words_and_len_by_split(arrWords[i], &len, " ");

        int number = atoi(list_words[0]);                   // переводим 0-евой элемент в число
        if(number != 0 && number % 2 == 0)                  // если это число, и если число чётное
        {
            printf("%s\n", arrWords_copy[i]);               // печатем строку
        }
        words_destructor(list_words, len);                  // удаляем массив строк
    }
    words_destructor(arrWords, length);                     // удаляем массив строк

    return 0;
}

char** get_words_and_len_by_split(char* str, int* length, char* split)
{
    char** arrWords = (char**) calloc(*length, sizeof(char*));  // выделяем память под массив слов

    char* p = strtok(str, split);                               // разбиваем один раз
    while(p)                                                    // пока p не равен NULL мы в цикле
    {
        *length += 1;                                           // увеличиваем длину массива
        arrWords = realloc(arrWords, *length * sizeof(char*));  // увеличиваем массив слов
        arrWords[*length - 1] = (char*) calloc(strlen(p), sizeof(char));// память под слово
        strcpy(arrWords[*length - 1], p);                       // копируем слово
        p = strtok(NULL, split);                                // разделяем на лексему ещё 1ин раз
    }

    return arrWords;                                            // возвращаем массив слов
}

char** get_copy_words(char** words, int length)
{
    char** result = (char**) calloc(length, sizeof(char*));     // выделяем память под массив слов
    for (int i = 0; i < length; i++)                            // проходимся по массиву слов
    {
        result[i] = (char*) calloc(strlen(words[i]), sizeof(char)); // выделяем память под слово
        strcpy(result[i], words[i]);                            // копируем слово
    }
    return result;                                              // возвращаем массив слов
}

void words_destructor(char** arr, int length)
{
    for (int i = 0; i < length; i++)    // проходимся по массиву слов
    {
        free(arr[i]);                   // освобожаем память от слова
    }
    free(arr);                          // освобождаем память от массива
}