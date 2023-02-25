#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define GREATER 1
#define EQUAL   0
#define LESSER  -1

typedef long long int ssize_t;

void show_student_array(struct student* pa, ssize_t N, const char* msg);
int compare_with_roll_number(struct student* ps1, struct student* ps2);
int compare_with_marks(struct student* ps1, struct student* ps2);
int compare_with_attnd(struct student* ps1, struct student* ps2);


void generic_insertion_sort(void * a,
                            ssize_t N, 
                            ssize_t mem_size, 
                            int (*p_cmpfn)(void* , void*)
                        );
struct student  
{
    int roll_number;
    float marks;
    float attendance;  
};

struct student s_arr[5] = {
    {1, 80.12, 89.54},
    {10, 65.23, 98.43},
    {7, 99.3, 88.12 },
    {3, 75.1, 88.12},
    {2, 88.2, 99.2}
};


int main(void)
{
    show_student_array(s_arr, 5, "Before sorting:");
    generic_insertion_sort(s_arr, 5, sizeof(struct student),compare_with_roll_number);
    show_student_array(s_arr, 5, "Sorting according to mark:");
    generic_insertion_sort(s_arr, 5, sizeof(struct student), compare_with_marks);
    show_student_array(s_arr, 5, "Sorting according to mark");
    generic_insertion_sort(s_arr, 5, sizeof(struct student), compare_with_attnd);
    show_student_array(s_arr, 5, "Sorting according to attendace");
    exit(EXIT_SUCCESS);
}

void generic_insertion_sort(void * a,
                            ssize_t N, 
                            ssize_t mem_size, 
                            int (*p_cmpfn)(void* , void*)
                        )
{
    ssize_t i, j;
    void* key = NULL;

    key = malloc(mem_size);
    if(NULL == key)
    {
        fprintf(stderr, "malloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }

    memset(key, 0, mem_size);
    for(int j = 1; j<N; ++j)
    {   
        memcpy(key, (char*)a+j*mem_size, mem_size); 
        i = j-1;
        while(i>-1&& p_cmpfn((char*)a + i * mem_size, key) == GREATER)
        {
            memcpy((char*)a + (i+1) * mem_size, 
                    (char*)a + i * mem_size, 
                        mem_size);
            i = i-1;
        }

        memcpy((char*)a + (i+1) * mem_size, key, mem_size);

    }    
    free(key);
    key = NULL;
}
void show_student_array(struct student* pa, ssize_t N, const char* msg)
{
    ssize_t i;

    if(msg)
        puts(msg);
    
    for(i = 0; i<N; i++)
    {
        printf("STUDENT #%lld\n", i+1);
        printf("Roll Number : %d\n", pa[i].roll_number);
        printf("Marks: %.2f\n", pa[i].marks);
        printf("Attedence:%.2f\n", pa[i].attendance);
    }
    puts("----------------------------------------------");
}

int compare_with_roll_number(struct student* ps1, struct student* ps2)
{
    if(ps1->roll_number > ps2->roll_number)
        return (GREATER);
    else if(ps1->roll_number == ps2->roll_number)
        return (EQUAL);
    else
        return (LESSER);
}

int compare_with_marks(struct student* ps1, struct student* ps2)
{
    if(ps1->marks > ps2->marks)
        return (GREATER);
    else if(ps1->marks == ps2->marks)
        return (EQUAL);
    else
        return (LESSER);
}
int compare_with_attnd(struct student* ps1, struct student* ps2)
{
    if(ps1->attendance > ps2->attendance)
        return (GREATER);
    else if(ps1->attendance == ps2->attendance)
        return (EQUAL);
    else
        return (LESSER);
}

