// библиотеки

#include <stdio.h>  //printf()
#include <unistd.h> //read()
#include <stdlib.h> //calloc(), free(), realloc(), rand()
#include <string.h> //strcmp(), strlen(), atoi(), strcat()

// прототипы

struct WordNode
{
    char* word;
    struct WordNode* left;
    struct WordNode* right;
};
struct WordNode* WordNode__Constructor(struct WordNode* object, char* word);
struct WordNode* WordNode__Destructor(struct WordNode* object);
struct WordNode* WordNode__add_top(struct WordNode* object, char* word);
struct WordNode* WordNode__get_bottom(struct WordNode* object);
void WordNode__print(struct WordNode* object);
void WordNode__print_word(struct WordNode* object);
void WordNode__print_down_to_top(
    struct WordNode* object, 
    void (*func)(struct WordNode* object)
);
void WordNode__print_top_to_down(
    struct WordNode* object,
    void (*func)(struct WordNode* object)
);
void WordNode__set_word(struct WordNode* object, char* word);
int get_depth_long_int(long int N);
char* get_string_with_number_hash(char* str, long int number);

// главная программа

int main()
{
    struct WordNode* string_list = NULL;
    struct WordNode* result = NULL;

    const int buffer_size = 1;
    char buffer[buffer_size];

    int str_size = 0;
    char* str = (char*) calloc(str_size, sizeof(char*));
    while(read(0, buffer, buffer_size))
    {
        char character = buffer[0];
        if (character == '\n')
        {

            int a = 0, b = 1234567890;
            int rand_number = rand() % (b - a + 1) + a;
            str = get_string_with_number_hash(str, rand_number);

            string_list = WordNode__add_top(string_list, str);

            str_size = 0;
            str = (char*) realloc(str, str_size * sizeof(char));

            continue;
        }
        str_size += 1;
        str = (char*) realloc(str, str_size * sizeof(char));
        str[str_size - 1] = character;
    }
    free(str);

    printf(" = = = = = Input = = = = =\n");
    WordNode__print_down_to_top(string_list, WordNode__print_word);

    //WordNode__print_down_to_top(string_list, WordNode__print);

    for (struct WordNode* temp = WordNode__get_bottom(string_list); temp != NULL; temp = temp->right)
    {
        str_size = 0;
        str = (char*) calloc(str_size, sizeof(char));
        if (str == NULL)
        {
            printf("Память не выделилась\n");
        }
        //printf("word = %s\n", temp->word);

        struct WordNode* words_list = NULL;
        for (int i = 0; ; i++)
        {
            char ch = temp->word[i];
            //printf("ch = %c\n", ch);  
            if (ch == '\0') break;
                      
            if (ch == ' ')
            {
                //printf("Добавляется слово %s\n", str);
                words_list = WordNode__add_top(words_list, str);
                str_size = 0;
                str = (char*) realloc(str, str_size * sizeof(char));
                continue;
            }
            str_size += 1;
            str = (char*) realloc(str, str_size * sizeof(char));
            str[str_size - 1] = ch;
        }
        //WordNode__print_down_to_top(words_list, WordNode__print);
        int number = atoi( WordNode__get_bottom(words_list)->word );
        if( number != 0 && number % 2 == 0 )
        {
            result = WordNode__add_top(result, temp->word);
            //printf(" = = = = = = = = = = %d\n", number);
        }
        words_list = WordNode__Destructor(words_list);
        free(str);
    }

    string_list = WordNode__Destructor(string_list);

    printf(" = = = = = Output = = = = =\n");
    WordNode__print_down_to_top(result, WordNode__print_word);
    result = WordNode__Destructor(result);

    return 0;
}

// реализация прототипов

struct WordNode* WordNode__Constructor(struct WordNode* object, char* word)
{
    object = (struct WordNode*) malloc(sizeof(struct WordNode));
    //printf("%p Constructor\n", object);
    if (object == NULL)
    {
        printf("Не выделилась память\n");
    }

    object->left = NULL;
    object->right = NULL;

    object->word = (char*) calloc(strlen(word), sizeof(char));
    if (object->word == NULL)
    {
        printf("Не выделилась память\n");
    }
    strcpy(object->word, word);

    return object;
}

struct WordNode* WordNode__Destructor(struct WordNode* object)
{
    for (struct WordNode* temp = object; temp != NULL; )
    {
        free(temp->word);
        object = temp;
        //printf("%p Destructor\n", object);
        temp = temp->left;
        free(object);
    }
    return NULL;
}

struct WordNode* WordNode__add_top(struct WordNode* object, char* word)
{
    if (word == NULL)
    {
        return object;
    }

    if (word[0] == '\0')
    {
        return object;
    }

    struct WordNode* new_node = WordNode__Constructor(new_node, word);
    new_node->left = object;
    if (object == NULL)
    {
        return new_node;
    }
    
    object->right = new_node;
    return new_node;
}

struct WordNode* WordNode__get_bottom(struct WordNode* object)
{
    if (object == NULL)
    {
        return NULL;
    }
    struct WordNode* temp = object;
    while(temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

void WordNode__print(struct WordNode* object)
{
    printf("\t{\n");
    printf("\t\t\"left\": \"%p\",\n", object->left);
    printf("\t\t\"right\": \"%p\",\n", object->right);
    printf("\t\t\"word\": \"%s\",\n", object->word);
    printf("\t},\n");
}

void WordNode__print_word(struct WordNode* object)
{
    printf("%s\n", object->word);
}

void WordNode__print_top_to_down(struct WordNode* object, void (*func)(struct WordNode* object))
{
    printf("[\n");
    for(struct WordNode* temp = object; temp != NULL; temp = temp->left)
    {
        func(temp);
    }
    printf("]\n");
}

void WordNode__print_down_to_top(struct WordNode* object, void (*func)(struct WordNode* object))
{
    printf("[\n");
    for(struct WordNode* temp = WordNode__get_bottom(object); temp != NULL ; temp = temp->right)
    {
        func(temp);
    }
    printf("]\n");
}

void WordNode__set_word(struct WordNode* object, char* word)
{
    free(object->word);
    object->word = (char*) calloc(strlen(word), sizeof(char));
    if ( object->word == NULL )
    {
        printf("Память не выделилась\n");
        return;
    }
    strcpy(object->word, word);
}

int get_depth_long_int(long int N)
{
    int i = 0;
    for( ; N>0; N = N / 10)
    {
        ++i;
    }
    return i;
}

char* get_string_with_number_hash(char* str, long int number)
{
    int len = get_depth_long_int(number);
    char* substr = (char*) calloc(len, sizeof(char));
    long int N = number;
    for (int i = 0; i < len; i += 1)
    {
        char ch;
        switch(N % 10)
        {
            case 0: ch = '0'; break;
            case 1: ch = '1'; break;
            case 2: ch = '2'; break;
            case 3: ch = '3'; break;
            case 4: ch = '4'; break;
            case 5: ch = '5'; break;
            case 6: ch = '6'; break;
            case 7: ch = '7'; break;
            case 8: ch = '8'; break;
            case 9: ch = '9'; break;
            default: ch = '_';
        }
        N = N / 10;
        substr[i] = ch;
    }
    
    char* result = (char*) calloc(len, sizeof(char));
    for (int i = 0; i < len; i++)
    {
        result[i] = substr[(len - 1) - i];
    }
    free(substr);
    
    str = (char*) realloc(str, (5 + len) * sizeof(char));
    strcat(str, result);
    free(result);

    return str;
}