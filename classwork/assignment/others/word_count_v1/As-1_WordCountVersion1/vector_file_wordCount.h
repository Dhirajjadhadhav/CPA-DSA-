
/*----------------------------------------------------------------------------------

    File        : header file (vector_file_wordCount.h)

    Goal        : declarations of structures, data types and functions

    Programmer  : Sugriv Arbad

----------------------------------------------------------------------------------*/

#include <stdbool.h>    // bool, true, false

// to store a single word
struct word
{
    char* p_char;
    size_t char_count;
};

// to store multiple words
struct vector
{
    struct word* p_word;
    size_t word_count;
};

// typedefs
typedef struct word word_t;
typedef struct vector vector_t;
typedef word_t vElm_t;

// functions declarations

/*-------------------------------------------------------------------------------------------------
    @Input          : none

    @Output         : address of newly allocated vector

    @description    : create a new empty vector
-------------------------------------------------------------------------------------------------*/
vector_t* create_vector(void);


/*-------------------------------------------------------------------------------------------------
    @Input-1        : address of vector to which new element(@input-2) must be added

    @Input-2        : An element to added to vector(@input-1)

    @Output         : none

    @description    : Add(append) new element to the vector
-------------------------------------------------------------------------------------------------*/
void push_back(vector_t*, vElm_t*);


/*-------------------------------------------------------------------------------------------------
    @Input          : none

    @Output         : address of newly allocated word

    @description    : create a new empty word
-------------------------------------------------------------------------------------------------*/
word_t* create_word(void);


/*-------------------------------------------------------------------------------------------------
    @Input-1        : address of word instance to which a character(@input-2) need to append

    @Input-2        : a character which must append to word(@input-1)

    @Output         : new address of word instance which is modified by appending character 

    @description    : append the particular character to word
-------------------------------------------------------------------------------------------------*/
word_t* append_character_to_word(word_t*, char);


/*-------------------------------------------------------------------------------------------------
    @Input-1        : address of vector instance to which all words from file(@input-2) shoud add

    @Input-2        : file path, add all from this file add to vector(@input-1)

    @Output         : none

    @description    : parse file given in file path(@input-2) and add all words from file to 
                      vector(@input-2)
-------------------------------------------------------------------------------------------------*/
void parse_words_from_file(vector_t*, char*);


/*-------------------------------------------------------------------------------------------------
    @Input-1        : address of word1 instance which value need to compare with another word 
                      instance(@input-2)

    @Input-2        : address of word2 instance which value need to compare with another word 
                      instance(@input-1)

    @Output         : return true or false

    @description    : compare two words(@input-1 and @input-2) and they are equal return true
                      otherwise false
-------------------------------------------------------------------------------------------------*/
bool is_word_matching(word_t*, char*);


/*-------------------------------------------------------------------------------------------------
    @Input-1        : address of vector instance in which search word(@input-2)

    @Input-2        : address of word instance which value need to seach in vector(@input-1)

    @Output         : return count of occurence of word(@input-2) in vector(@input-1)

    @description    : if word(@input-2) exitsts in vector(@input-1) then return count of occurence
                      of word in vector otherwise return 0
-------------------------------------------------------------------------------------------------*/
size_t count_occurence_of_word(vector_t*, char*);


/*-------------------------------------------------------------------------------------------------
    @Input          : address of word instance

    @Output         : none

    @description    : display value of word instance on standard output device(console)
-------------------------------------------------------------------------------------------------*/
void show_word(word_t*);


/*-------------------------------------------------------------------------------------------------
    @Input          : address of vector instance

    @Output         : none

    @description    : display each word inside the vector on standard output device(console)
-------------------------------------------------------------------------------------------------*/
void show_vector(vector_t*);


/*-------------------------------------------------------------------------------------------------
    @Input          : address of address of vector instance

    @Output         : none

    @description    : free dynamically allocated memory which is allocated for vector and words
                      words inside it
-------------------------------------------------------------------------------------------------*/
void release_vector(vector_t**);

