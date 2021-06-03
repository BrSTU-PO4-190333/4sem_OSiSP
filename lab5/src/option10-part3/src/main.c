#include <stdio.h>  //printf()
#include <stdlib.h> //calloc(), free()
#include <string.h> //strcpy()

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        printf("\nАргументы не переданы\n");
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        char* word = (char*) calloc(strlen(argv[i]), sizeof(char));
        strcpy(word, argv[i]);
        
        int a = 1;
        int b = strlen(word) - 2;
        for (int ii = a; ii < b; ii++)
        {
            int r = rand() % (b - a + 1) + a;
            char temp = word[ii];
            word[ii] = word[r];
            word[r] = temp;
        }

        printf("| %-16s | %-16s |\n", argv[i], word);
        free(word);
    }

    return 0;
}
