#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int ssize_t;

struct Word
{
    char* p_str;
    int  len;
    int line;
    int at_pos;
};

struct vector
{
    struct Word** pp_word;
    ssize_t N;
};

/*
    @input :    None 

    @output:    Address of newly allocated instance of 
                struct vector
    To allocate an instace of struct vector. 
*/
struct vector* create_vector(void);

/*
    @input-1: Pointer to vector object to which
            new element (@input-2) must be added
            
    @input-2: An element to be added 

    @output: None

    Add new_element(@inout-2) to given vector (@input-1)
*/
void push_back(struct vector* p_vector, struct Word* p_word);

/*
    @input-1 : Pointer to vector to be released

    @output: None 

    Show the elelment in the array inside the given 
    vector(@input-1); 
*/
void show_vector(struct vector* p_vector);

/*
    @input-1 : Pointer to vector to be released 

    @output : None 

    Frees the array inside the given vector(@input-1) and 
    free the vector intself.
*/
void release_vector(struct vector* p_vector);

void Seperate_word(FILE * fp, struct vector* p_vector);

void search_word(struct vector* p_vector, const char* word);

int main(int argc, char* argv[])
{

    struct vector* p_vector = NULL;
    char* word_to_searched = NULL;
    FILE* fp = NULL;
    p_vector = create_vector();

    if(argc != 3 )
    {
        fprintf(stderr, "Usage Error: %s name_of_file word_search\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if(NULL == fp)
    {
        fprintf(stderr,"Can't open file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    Seperate_word(fp, p_vector);
    search_word(p_vector, argv[2]);

    //show_vector(p_vector );

    release_vector(p_vector);

    fclose(fp);
}

struct vector* create_vector(void)
{
    struct vector* p_vector = NULL;
    p_vector = (struct vector*)malloc(sizeof(struct vector));
    if(NULL == p_vector)
    {
        fprintf(stderr , "malloc():fatal:out of memeory\n");
        exit(EXIT_FAILURE);
    }
    p_vector->pp_word = NULL;
    p_vector->N = 0;

    return(p_vector);
}


void push_back(struct vector* p_vector, struct Word* p_word)
{  
    p_vector->pp_word = (struct Word**)realloc(p_vector->pp_word, (p_vector->N + 1) * sizeof(struct Word*));
    if(NULL == p_vector->pp_word)
    {
        fprintf(stderr, "rellaoc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }
    p_vector->N = p_vector->N+1;
    p_vector->pp_word[p_vector->N-1] = p_word;
}
void show_vector(struct vector* p_vector)
{   
    ssize_t i;

    for(i = 0; i<p_vector->N; i++)
    {
        printf("p_vector->p_word[%lld]->p_str = %s\n",i, p_vector->pp_word[i]->p_str);
        printf("p_vector->p_word[%lld]->len = %d\n",i, p_vector->pp_word[i]->len);
        printf("p_vector->p_word[%lld]->line = %d\n",i, p_vector->pp_word[i]->line);
        printf("p_vector->p_word[%lld]->at_pos = %d\n",i, p_vector->pp_word[i]->at_pos);
        printf("____________________________________________________________________________\n");
    }
}
void release_vector(struct vector* p_vector)
{
    ssize_t i;
    if(p_vector != NULL)
    {
        if(p_vector->pp_word != NULL)
        {
            for(i = 0; i<p_vector->N; i++)
            {
                free(p_vector->pp_word[i]->p_str);
                free(p_vector->pp_word[i]);
            }
            free(p_vector);
        }
        free(p_vector);
        p_vector= NULL;
    }
}

void Seperate_word(FILE* fp, struct vector* p_vector)
{
    int i, line = 1, at_pos = 1;
    char word[100] = { 0 };
    char c;
    struct Word* p_word = NULL;

    while((c = fgetc(fp)))
    {
        if(c == '\n' || c == '\t' || c == ' ')
        {
            if(c == '\n')
            {
                line++;
                at_pos = 1;
            }
        }
        else
        {
            break;
        }
    }

    i = 0;
    ungetc(c, fp);
    while((c = getc(fp))!= EOF)
    {
        
        if(c == '\n' || c == '\t' || c == ' ')
        {
            word[i++] = '\0';
           
            if(i != 1)
            {
                p_word = (struct Word*)calloc(1, sizeof(struct Word));
                if(NULL == p_word)
                {
                    fprintf(stderr, "calloc():fatal:out of memory\n");
                    exit(EXIT_FAILURE);
                }
                
                p_word->p_str = (char*)calloc(i, sizeof(char));
                if(NULL == p_word->p_str)
                {
                    fprintf(stderr, "calloc():fatal:out of memory\n");
                    exit(EXIT_FAILURE);
                }

                memcpy(p_word->p_str, word, i);
                p_word->len = i-1;
                p_word->line = line;
                p_word->at_pos = at_pos;
                at_pos++;
                push_back(p_vector, p_word);  
            }
            if(c == '\n')
            {
                line++;
                at_pos = 1;
            }
            i = 0;
        }
        else
        {
            word[i++] = c;
        }
    }
}

void search_word(struct vector* p_vector, const char* word)
{
    ssize_t i;
    ssize_t cnt = 0;
    for(i = 0; i<p_vector->N; i++)
    {
        if(strcmp(word, p_vector->pp_word[i]->p_str) == 0)
        {
            cnt++;
            printf("%s ocuurred %lld time at line %i and at pos %i\n", word, cnt, 
                        p_vector->pp_word[i]->line, p_vector->pp_word[i]->at_pos);

        }
    }

    printf("word %s ocurred in this file %lld times\n", word, cnt);
}