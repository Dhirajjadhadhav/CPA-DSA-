#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

struct word
{
	char* p_sz_word;
	int i_line_no;
};

struct vector
{
	struct word** p_wordStrct;
	int i_vector_index;
};

struct vector* create_vector(void);
int push_back(struct vector*,struct word*);
void parse_file(struct vector* , const char*);
void print_vector(struct vector*);
void free_resourse(struct vector*);
void search_word(struct vector*, const char*);



int main(int argc,char *argv[])
{
	char szFilePath[_MAX_PATH] = { 0 };
	char* p_wordInCmd = NULL;
	
	if (argc > 1)
	{
		p_wordInCmd = argv[1];
		strcpy_s(szFilePath, _MAX_PATH, argv[2]);
	}
	else
	{
		printf("cmd line must be <word><file path>");
		exit(EXIT_FAILURE);
	}
	
	struct vector* p_vector = NULL;
	p_vector = create_vector();

	parse_file(p_vector, szFilePath);

	//print_vector(p_vector);

	search_word(p_vector, p_wordInCmd);

	free_resourse(p_vector);

	getchar();

	return 0;
}

struct vector* create_vector(void)
{
	struct vector* p_vector = NULL;

	p_vector = (struct vector*)malloc(sizeof(struct vector));

	if (NULL == p_vector)
	{
		printf("fatal : malloc failed to allocate memory");
		exit(EXIT_FAILURE);
	}

	p_vector->p_wordStrct = NULL;
	p_vector->i_vector_index = 0;

	return(p_vector);
}


int push_back(struct vector* p_vector, struct word* p_wordStruct)
{
	int iSuccessFlag = FALSE;

	p_vector->p_wordStrct = (struct word**)realloc(p_vector->p_wordStrct, (p_vector->i_vector_index + 1) * sizeof(struct word*));

	if (NULL != p_vector->p_wordStrct)
	{
		p_vector->p_wordStrct[p_vector->i_vector_index] = p_wordStruct;
		p_vector->i_vector_index++;
		iSuccessFlag = TRUE;
	
	}
	else
	{
		printf("fatal : malloc memory allocation failed");
		iSuccessFlag = FALSE;
	}
	return TRUE;
	
}

//	@input1: Pointer to a vector object to which
//			   word from file and line number(@input-2) must be added
//  
//  @input2: file path
//
//	@output: no output
//
//	@purpose : To parse file(@input1)

void parse_file(struct vector* p_vector,const char* p_file_path)
{

	struct word* p_local_word= NULL;

	FILE* p_file_to_parse = NULL;
	size_t i_file_size = 0;
	size_t i_file_size_read = 0;
	size_t i_size_word = 0;
	char* p_file_content = NULL;

	int i_Line_Cnt = 0;


	char* p_line = NULL;
	char* p_next_token_line = NULL;
	
	char* p_word = NULL;
	char* p_next_token_word = NULL;

	fopen_s(&p_file_to_parse, p_file_path, "r");

	if (NULL != p_file_to_parse)
	{
		fseek(p_file_to_parse, 0, SEEK_END);
		i_file_size = ftell(p_file_to_parse);
		fseek(p_file_to_parse, 0, SEEK_SET);

		if (i_file_size > 0)
		{
			p_file_content = (char*)malloc(i_file_size * sizeof(char));

			if (NULL != p_file_content)
			{
				memset(p_file_content, 0x00, i_file_size * sizeof(char));

				i_file_size_read = fread(p_file_content, sizeof(char), i_file_size, p_file_to_parse);

				if (0 < i_file_size_read)
				{
					p_line = strtok_s(p_file_content, "\n", &p_next_token_line);
					while (NULL != p_line)
					{
						i_Line_Cnt++;

						p_word = strtok_s(p_line, " ", &p_next_token_word);
						while(NULL != p_word)
						{
							i_size_word = strlen(p_word);

							p_local_word = (struct word*)malloc(sizeof(struct word));

							if (NULL != p_local_word)
							{
								memset(p_local_word, 0x00,  sizeof(struct word));

								p_local_word->p_sz_word = (char*)malloc(i_size_word * sizeof(char) + 1);

								memset(p_local_word->p_sz_word, 0x00, i_size_word * sizeof(char) + 1);

								strcpy_s(p_local_word->p_sz_word, i_size_word+1 , p_word);

								//memcpy_s(p_local_word->p_sz_word, i_size_word * sizeof(char) + 1, p_word, i_size_word);
								p_local_word->i_line_no = i_Line_Cnt;

								push_back(p_vector, p_local_word);
							}
							p_word = strtok_s(NULL, " ", &p_next_token_word);
						}
						p_line = strtok_s(NULL, "\n", &p_next_token_line);
					}
				}
			}
			if (NULL != p_file_content)
			{
				free(p_file_content);
				p_file_content = NULL;
			}
		}
		fclose(p_file_to_parse);
		p_file_to_parse = NULL;
	}
}

//	@input1: Pointer to a vector object to which
//			 contain word from file and line number of that word
// 
//	@output: no output
//
//	@purpose : to print data from vector
void print_vector(struct vector* p_vector)
{
	size_t i_cnt_index = 0;
	for (i_cnt_index = 0; i_cnt_index < p_vector->i_vector_index; i_cnt_index++)
	{
		printf("word '%s' present at line no '%d' \n", p_vector->p_wordStrct[i_cnt_index]->p_sz_word, p_vector->p_wordStrct[i_cnt_index]->i_line_no);
	}
}

//	@input1: Pointer to a vector object to which
//			 contain word from file and line number of that word
//
//	@output: no output
//
//	@purpose : to print data from vector
void free_resourse(struct vector* p_vector)
{
	size_t i_cnt_index = 0;
	for (i_cnt_index = 0; i_cnt_index < p_vector->i_vector_index; i_cnt_index++)
	{
		free(p_vector->p_wordStrct[i_cnt_index]->p_sz_word);
		p_vector->p_wordStrct[i_cnt_index]->p_sz_word = NULL;
		free(p_vector->p_wordStrct[i_cnt_index]);
		p_vector->p_wordStrct[i_cnt_index] = NULL;
	}

	free(p_vector);
	p_vector = NULL;
}


//	@input1: Pointer to a vector object to which
//			 contain word from file and line number of that word
// 
//	@input2: word that search in vector  
//
//	@output: no output
//
//	@purpose : to search word and print word
void search_word(struct vector* p_vector, const char* p_word_to_search)
{
	size_t i_cnt_index = 0;
	size_t i_cnt_word = 0;

	size_t i_prev_lineno = -1;


	printf("word '%s' present at line no ", p_vector->p_wordStrct[i_cnt_index]->p_sz_word);

	for (i_cnt_index = 0; i_cnt_index < p_vector->i_vector_index; i_cnt_index++)
	{
		if (_strcmpi(p_vector->p_wordStrct[i_cnt_index]->p_sz_word, p_word_to_search) == 0)
		{
			if(i_prev_lineno != p_vector->p_wordStrct[i_cnt_index]->i_line_no)
			{
				printf("%d ",p_vector->p_wordStrct[i_cnt_index]->i_line_no);
				i_prev_lineno = p_vector->p_wordStrct[i_cnt_index]->i_line_no;
			}
			
			++i_cnt_word;
		}
	}

	printf("and total count is %d.", i_cnt_word);
}