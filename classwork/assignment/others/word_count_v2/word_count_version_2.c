#include<stdio.h>
#include<stdlib.h>

#define MAX_LINES 100
#define MAX_LEN 1000

#define VECTOR_INIT_CAPACITY 4

struct vector {
	void** items;
	int capacity;
	int total;
};

void vector_init(struct vector*);
int vector_total(struct vector*);
static void vector_resize(struct vector*, int);
void vector_add(struct vector*, void*);
void vector_set(struct vector*, int, void*);
void* vector_get(struct vector*, int);
void vector_delete(struct vector*, int);
void vector_free(struct vector*);

int my_strcmp(char* str1, char* str2);

void vector_init(struct vector* v)
{
	v->capacity = VECTOR_INIT_CAPACITY;
	v->total = 0;
	v->items = malloc(sizeof(void*) * v->capacity);
}

int vector_total(struct vector* v)
{
	return v->total;
}

static void vector_resize(struct vector* v, int capacity)
{
	void** items = realloc(v->items, sizeof(void*) * capacity);
	if (items) {
		v->items = items;
		v->capacity = capacity;
	}
}

void vector_add(struct vector* v, void* item)
{
	if (v->capacity == v->total)
		vector_resize(v, v->capacity * 2);
	v->items[v->total++] = item;
}

void vector_set(struct vector* v, int index, void* item)
{
	if (index >= 0 && index < v->total)
		v->items[index] = item;
}

void* vector_get(struct vector* v, int index)
{
	if (index >= 0 && index < v->total)
		return v->items[index];
	return NULL;
}

void vector_delete(struct vector* v, int index)
{
	if (index < 0 || index >= v->total)
		return;

	v->items[index] = NULL;

	for (int i = index; i < v->total - 1; i++) {
		v->items[i] = v->items[i + 1];
		v->items[i + 1] = NULL;
	}

	v->total--;

	if (v->total > 0 && v->total == v->capacity / 4)
		vector_resize(v, v->capacity / 2);
}

void vector_free(struct vector* v)
{
	free(v->items);
}

int my_strcmp(char* string1, char* string2)
{
	int flag = 0;
	int i = 0;

	while (string1[i] != '\0' && string2[i] != '\0') {
		if (string1[i] != string2[i]) {
			flag = 1;
			break;
		}
		i++;
	}

	if (flag == 0)
		return 0;

	return 1;
}

int main(void) {
	char data[MAX_LINES][MAX_LEN];
	char search[MAX_LEN];
	int found = 0;
	int count = 0;

	struct vector v;
	vector_init(&v);

	//create a file pointer variable to allow us to access the file
	FILE* file;

	//Open the file in read mode; fopen will return null if it fails to
	file = fopen("words.txt", "r");

	//If that file doesnot exist return an error message
	if (file == NULL) {
		printf("Error opening file\n");
		return 1;
	}

	//line variable will keep the track of the number of lines read so far.
	int line = 0;

	//So long we have not reached the end of the file and while reading we did not came across any error
	while (!feof(file) && !ferror(file)) {
		if (fgets(data[line], MAX_LEN, file) != NULL) //fgets(kashamadhe write karaycha ahe, kiti write karaycha ahe, kuthun write karaycha ahe)
			line++;
	}

	fclose(file);

	for (int i = 0; i < line; i++) {
		vector_add(&v, data[i]);
	}

	for (int i = 0; i < line; i++) {
		printf("%s", (char*)vector_get(&v, i));
	}

	/*
	for (int i = 0; i < line; i++) {
		printf("%s", data[i]);
	}
	*/

	printf("\nEnter the word to search:");
	scanf("%s", search);

	for (int i = 0; i < line; i++) {
		found = my_strcmp(search, (char*)vector_get(&v, i));
		if (found == 0) {
			printf("found in line: %d\n", i + 1);
			count++;
		}
	}

	printf("\n");
	printf("The respective word is repeated %d number of times in text document", count);
	printf("\n");

	return 0;
}


