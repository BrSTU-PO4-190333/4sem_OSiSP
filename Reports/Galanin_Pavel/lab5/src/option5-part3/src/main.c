//библиотеки

#include <unistd.h> //read()
#include <stdio.h>  //printf()
#include <stdlib.h> //calloc(), realloc(), free()
#include <string.h> //strcpy(), strlen(), strcat()

//прототипы

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
struct WordNode* WordNode__get_by_index(struct WordNode* object, int index);
void WordNode__set_word(struct WordNode* object, char* word);
struct WordNode* get_words_file_list(const char path[]);
char* copy_strg1_to_strg2(char* string1, char* string2);

//главная функция

int main()
{
    struct WordNode* list_file_words = get_words_file_list("../lorem100.html");
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

    printf(" ~ ~ ~ ~ ~ file descriptor = 0 ~ ~ ~ ~ ~\n");
    for (struct WordNode* temp = WordNode__get_bottom(string_list); temp != NULL; temp = temp->right)
    {
        printf("%s\n", temp->word);
    }

    int index_file_word = 0;
    for (struct WordNode* temp = WordNode__get_bottom(string_list); temp != NULL; temp = temp->right)
    {
        char* string1 = temp->word;
        char* string2 = WordNode__get_by_index(list_file_words, index_file_word)->word;
        char* strng = copy_strg1_to_strg2(string1, string2);

        WordNode__set_word(temp, strng);
        free(strng);

        index_file_word += 1;
    }

    for (struct WordNode* temp = WordNode__get_bottom(string_list); temp != NULL; temp = temp->right)
    {
        str_size = 0;
        str = (char*) calloc(str_size, sizeof(char));
        if (str == NULL) printf("Память не выделилась\n");

        struct WordNode* words_list = NULL;
        for (int i = 0; ; i++)
        {
            char ch = temp->word[i]; 
            if (ch == '\0') break;
                      
            if (ch == ' ')
            {
                words_list = WordNode__add_top(words_list, str);
                str_size = 0;
                str = (char*) realloc(str, str_size * sizeof(char));
                continue;
            }
            str_size += 1;
            str = (char*) realloc(str, str_size * sizeof(char));
            if (str == NULL) printf("Память не выделилась\n");
            str[str_size - 1] = ch;
        }

        int number = atoi( WordNode__get_bottom(words_list)->word );
        if( number != 0 && number % 2 == 0 )
        {
            result = WordNode__add_top(result, temp->word);
        }
        words_list = WordNode__Destructor(words_list);
        free(str);
    }

    string_list = WordNode__Destructor(string_list);

    printf(" ~ ~ ~ ~ ~ file descriptor = 1 ~ ~ ~ ~ ~\n");
    for(struct WordNode* temp = WordNode__get_bottom(result); temp != NULL ; temp = temp->right)
    {
        int file_descriptor = 1;
        char* buf = temp->word;
        int buf_size = strlen(buf);
        write(file_descriptor, buf, buf_size);
        write(file_descriptor, "\n", 1);
    }
    result = WordNode__Destructor(result);

    list_file_words = WordNode__Destructor(list_file_words);

    return 0;
}

//реализация прототипов

struct WordNode* WordNode__Constructor(struct WordNode* object, char* word)
{
    object = (struct WordNode*) malloc(sizeof(struct WordNode));
    if (object == NULL) printf("Память не выделилась\n");
    //printf("%p Constructor\n", object);

    object->left = NULL;
    object->right = NULL;

    object->word = (char*) calloc(strlen(word), sizeof(char));
    if (object->word == NULL) printf("Память не выделилась\n");
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

struct WordNode* WordNode__get_by_index(struct WordNode* object, int index)
{
    struct WordNode* temp = WordNode__get_bottom(object);
    for(int i = 0; temp != NULL && i != index; temp = temp->right, i += 1)
    {

    }
    return temp;
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

struct WordNode* get_words_file_list(const char path[])
{
    FILE* file_pointer = fopen(path, "r");
    if (file_pointer == NULL)
    {
        printf("File %s not opened\n", path);
        return 0;
    }

    int word_size = 0;
    char* word = (char*) calloc(word_size, sizeof(char));
    if (word == NULL) printf("Память не выделилась\n");
    struct WordNode* list_file_words = NULL;

    while(!feof(file_pointer))
    {
        char character = fgetc(file_pointer);
        if(
            character == ' '
            || character == ','
            || character == '.'
            || character == '!'
        )
        {
            if (word_size == 0)
            {
                continue;
            }
            list_file_words = WordNode__add_top(list_file_words, word);
            word_size = 0;
            word = (char*) realloc(word, word_size * sizeof(char));
            continue;
        }
        word_size += 1;
        word = (char*) realloc(word, word_size * sizeof(char));
        word[word_size - 1] = character;
    }

    if (word != NULL)
    {
        free(word);
    }
    fclose(file_pointer);

    return list_file_words;
}

char* copy_strg1_to_strg2(char* string1, char* string2)
{
    int string1_size = strlen(string1);
    int string2_size = strlen(string2);

    int result_string_size = string1_size + string2_size;
    char* result_string = (char*) calloc(result_string_size, sizeof(char));
    if (result_string == NULL) printf("Память не выделилась\n");
    strcpy(result_string, string1);
    strcat(result_string, string2);

    return result_string;
}
