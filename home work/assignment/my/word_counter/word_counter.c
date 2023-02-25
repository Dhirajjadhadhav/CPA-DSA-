#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef long long int   ssize_t;

struct word
{
    char* p_word;
    ssize_t len;
};

struct vector
{
    struct word* p_word_arr;
    ssize_t count; 
};

struct vector* create_vector(void);
void push_back(struct vector* p_vector, struct word new_word);
void show_vector(struct vector* p_vector);
void release_vector(struct vector* p_vector);
int count_number_of_occurance_of_string(struct vector* p_vector, char* word);
int IsStringIdentical(char* str1,char* str2);
void sepearte_word_from_file(FILE *fp,  struct vector* p_vector);

int main(int argc, char* argv[])
{
    FILE* fp;
    struct vector* p_vector = NULL;
    int count;
    p_vector = create_vector();

    if(argc != 3)
    {
        printf("invalid command line arguments!!\n\n");
        printf("help:\nword_counter.exe file_name word\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        fprintf(stderr, "file is not available\n");
        exit(EXIT_FAILURE);
    }

    sepearte_word_from_file(fp,  p_vector);
    
    count = count_number_of_occurance_of_string(p_vector,  argv[2]);
    printf("WORD APPEARS %d\n", count);

    fclose(fp);
}

struct vector* create_vector(void)
{
    struct vector* p_vector = NULL;
            
    p_vector = (struct vector*)(malloc(sizeof(struct vector)));  
    if(p_vector == NULL)
    {
        fprintf(stderr,"malloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }

    p_vector->p_word_arr = NULL;
    p_vector->count = 0;
    return (p_vector);
}

void push_back(struct vector* p_vector, struct word new_word)
{
    p_vector->p_word_arr = (struct word*)realloc(p_vector->p_word_arr, 
                                    (p_vector->count + 1) * sizeof(struct word));
    if(p_vector->p_word_arr == NULL)
    {
        fprintf(stderr, "mallco():fatal:out of memory");
        exit(EXIT_FAILURE);
    }

    p_vector->count = p_vector->count + 1;
    p_vector->p_word_arr[p_vector->count - 1] = new_word;
}
void show_vector(struct vector* p_vector)
{
    int i;
    for(i = 0; i<p_vector->count; i++)
        printf("p_vetctor->p_word_arr[%d]: %s, size = %llu\n", i, p_vector->p_word_arr[i].p_word,
                                                          p_vector->p_word_arr[i].len);
}

int count_number_of_occurance_of_string(struct vector* p_vector, char* word)
{
    int i = 0;
    int count = 0;
    int len = strlen(word);
    for(int i = 0; i<p_vector->count; i++)
    {
        
        if(IsStringIdentical(p_vector->p_word_arr[i].p_word, word))
        {
            count++;
        }         
    }
    return(count);
}

void release_vector(struct vector* p_vector)
{   
    int i;
    if(p_vector!= NULL)
    {
        if(p_vector->p_word_arr != NULL)
        {
            for(i = 0; i<p_vector->count; i++)
            {
                    free(p_vector->p_word_arr[i].p_word);
            }
            free(p_vector->p_word_arr);
        }
        free(p_vector);
        p_vector = NULL;
    }   
}

int IsStringIdentical(char* str1,char* str2)
{
    int i = 0;
    int flag = 1;

    while(str1[i] != '\0' || str2[i] !='\0')
    {
        if(str1[i]  != str2[i])
        {

            flag = 0;
            break;
        }
        
        i++;
    }
   return (flag == 1);
}

void sepearte_word_from_file(FILE *fp,  struct vector* p_vector)
{
    int i;
    char c;
    char word[50] = { 0 };
    struct word w = { 0 };

    while((c = getc(fp)))
    {
        if(c == ' '|| c == '\n' || c == '\t')
            continue;
        else 
            break;
    }
    
    i = 0;
    ungetc(c, fp);
    while((c = getc(fp)) != EOF)
    {
            
        if(c == ' ' || c == '\t' ||  c == '\n')
        {
            word[i++] = '\0';
            if(i != 1)
            {
                w.p_word = (char*)malloc(i * sizeof(char));
                w.len = i-1;
                memcpy(w.p_word, word, i);
                memset(word, 0, sizeof(word));
                push_back(p_vector, w);
            }
            memset(&w, 0, sizeof(struct  word));
            i = 0; 
                
        }
        else
        {
            word[i++] = c;
        }
    }

    word[i++] = '\0';
    w.p_word = (char*)malloc(i * sizeof(char));
    w.len = i-1;
    strcpy(w.p_word, word);
    push_back(p_vector, w);
    memset(&w, 0, sizeof(struct word));
}