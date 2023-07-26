#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "hash_queue.h"


int main(int argc, char* argv[])
{

    size_t bucket_size;
    size_t nr_elements;
    key_t* keys = NULL;
    key_t key;
    hashq_t* p_hashq = NULL;
    status_t status;
    size_t i;

    if(3!=argc)
    {
        fprintf(stderr, "UsageError: %s bucket_size nr_element\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    bucket_size = atoll(argv[1]);
    nr_elements = atoll(argv[2]);
    
    srand(time(0));
    assert(bucket_size && nr_elements);


    keys = (key_t*)xcalloc(nr_elements, sizeof(key));

    for(size_t i = 0; i<nr_elements; ++i)
        keys[i] = rand();
    
    p_hashq = create_hashq(bucket_size);

   for (size_t i = 0; i < nr_elements; ++i)
   {
        status = add_key(p_hashq, keys[i]);
        if(status !=SUCCESS)
        {
            fprintf(stderr, "unexpected error\n");
            exit(EXIT_FAILURE);
        }
   }
   
    hash_stat(p_hashq);

    puts("Searching key test : SUCCESS CASES");

    for(int i = 0; i<5; ++i)
    {
        key = keys[rand()%nr_elements];
        printf("Searching for key : %lld", key);
        status = search_key(p_hashq, key);
        if(TRUE == status)
            printf("key:%llu found\n", key);
        else
        {
            fprintf(stderr, "unexpected error\n");
            exit(EXIT_FAILURE);
        }
    }

    puts("Search key test :RANDOM CASES : SHOULD BE FALSE MOSTLY");
    for(i = 0; i<5; ++i)
    {
        key = rand();
        printf("Searching for key : %llu\n", key);
        status =  search_key(p_hashq, key);
        if(TRUE == status)
            printf("key:%llu found\n", key);
        else    
            printf("key:%llu not found\n", key);
    }

    key = keys[rand()%nr_elements];
    printf("key to be removes : %llu\n", key);
    status = remove_key(p_hashq, key);
    assert(status);

    //assert(search_key(p_hashq, key) == FALSE);
    
    status = destroy_hashq(&p_hashq);
    assert(status== SUCCESS && !p_hashq);
    free(keys);
    keys = NULL;

    exit(EXIT_SUCCESS);

} 