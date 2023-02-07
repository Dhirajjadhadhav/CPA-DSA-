#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

typedef long long ssize_t;

struct vector
{
	char** p_wordArray;
	ssize_t ssVectorNo;
};

struct vector* create_vector(void);
bool push_back(struct vector*, const char*);
void show_vector(struct vector* p_vector); 
bool release_vector(struct vector* p_vector);

void parse_file(struct vector* p_vector, const char t_szFilePath[]);
int search_word(struct vector* p_vector, const char t_Word[]);

void print_help(void);

int main(int argc, char* argv[])
{
	char szFilePath[_MAX_PATH] = { 0 };
	char* p_wordInCmd = NULL;

	if (0 == _strcmpi(argv[1], "--help"))
	{
		print_help();
		getchar();
		return 0;
	}

	if (argc == 3)
	{
		p_wordInCmd = argv[1];
		strcpy_s(szFilePath, _MAX_PATH, argv[2]);
		 
	}
	else
	{
		print_help();
		getchar();
		return 0;
	}

	
	
	struct vector* p_vector = NULL;

	p_vector = create_vector();

	parse_file(p_vector, szFilePath);
	 
	int iWordFndCnt =  search_word(p_vector, p_wordInCmd);

	printf("Word %s found %d times in file.\n", p_wordInCmd, iWordFndCnt);
	//show_vector(p_vector);

	release_vector(p_vector);

	free(p_vector);
	p_vector =NULL;

	getchar();
	return 0;
}

/*
	@input: None

	@output: return pointer to a struct vector 

	@purpose : To create vector pointer 
*/
struct vector* create_vector(void)
{
	struct vector* p_vector = NULL;

	p_vector = malloc(sizeof(struct vector));

	if (NULL == p_vector)
	{
		printf("malloc():fatal:out of memory\n");
		exit(EXIT_FAILURE);
	}

	p_vector->p_wordArray = NULL;
	p_vector->ssVectorNo = 0;

	return (p_vector);
}

/*
	@input-1: Pointer to a vector object to which
			  new element (@input-2) must be added

	@input-2: An element to be added

	@output: return true if sucesss

	@purpose :  Add new_element(@input-2) to a given vector(@input-1)
*/
bool push_back(struct vector* p_vector, const char* szWord)
{
	bool b_IsOpSuccess = false;
	size_t i_size_of_word = strlen(szWord);

	p_vector->p_wordArray = (char**)realloc(p_vector->p_wordArray, (p_vector->ssVectorNo + 1) * sizeof(char*));

	if (NULL != p_vector->p_wordArray)
	{
		p_vector->p_wordArray[p_vector->ssVectorNo] = (char*)malloc(i_size_of_word * sizeof(char)+1);
		if (NULL != p_vector->p_wordArray[p_vector->ssVectorNo])
		{
			memset(p_vector->p_wordArray[p_vector->ssVectorNo], 0, i_size_of_word * sizeof(char) + 1);
			strcpy_s(p_vector->p_wordArray[p_vector->ssVectorNo], i_size_of_word * sizeof(char) + 1,szWord);
			p_vector->ssVectorNo++;
		}
		else
		{
			printf("Fatal : Out of memory while malloc\n");
			b_IsOpSuccess = false;
		}
	}
	else
	{
		printf("Fatal : Out of memory while realloc\n");
		b_IsOpSuccess = false;
	}
	return b_IsOpSuccess;
}


/*
	@input-1: Pointer to a vector object to which
			  new element (@input-2) must be added

	@output: None

	@purpose : to print vector on console one by one
*/
void show_vector(struct vector* p_vector)
{
	int iPrintedVectCnt = 0;

	for (iPrintedVectCnt = 0; iPrintedVectCnt < p_vector->ssVectorNo; iPrintedVectCnt++)
	{
		printf("[%d] => [%s]\n", iPrintedVectCnt+1,p_vector->p_wordArray[iPrintedVectCnt]);
	}
}




/*
	@input-1: Pointer to a vector object to which
			  new element (@input-2) must be added

	@output: return true/false 
				true if sucess  and false if fail

	@purpose : to print vector on console one by one
*/
bool release_vector(struct vector* p_vector)
{
	int iPrintedVectCnt = 0;

	for (iPrintedVectCnt = 0; iPrintedVectCnt < p_vector->ssVectorNo; iPrintedVectCnt++)
	{
		free(p_vector->p_wordArray[iPrintedVectCnt]);
		p_vector->p_wordArray[iPrintedVectCnt] = NULL;
	}

	free(p_vector->p_wordArray);
	p_vector->p_wordArray = NULL;
	if (NULL != p_vector->p_wordArray)
		return false;

	return true;
}

/*
	@input: Pointer to a vector object to which
			   word from file (@input-2) must be added

	@output: None

	@purpose : read  (@input-2) file and read words one by one and add to vector
*/
void parse_file(struct vector* p_vector ,const char t_szFilePath[])
{
	FILE* p_file = NULL;
	size_t iSizeofFile = 0,iNoOfByteRead = 0;
	char* p_file_contents = NULL;

	char* p_szWord = NULL;
	char* p_NextToken = NULL;

	char* p_szLine = NULL;
	char* p_LineNextToken = NULL;
	
	if (PathFileExists(t_szFilePath))
	{
		fopen_s(&p_file, t_szFilePath, "r");
		if (NULL != p_file)
		{
			fseek(p_file, 0L, SEEK_END);
			iSizeofFile = ftell(p_file);
			fseek(p_file, 0L, SEEK_SET);

			p_file_contents = (char*)malloc(iSizeofFile * sizeof(char) + 1);

			if (NULL != p_file_contents)
			{
				memset(p_file_contents, 0x00, iSizeofFile * sizeof(char) + 1);

				iNoOfByteRead = fread(p_file_contents, sizeof(char), iSizeofFile, p_file);
				if (iNoOfByteRead > 1)
				{
					p_szLine = strtok_s(p_file_contents, "\n", &p_LineNextToken);
					while (NULL != p_szLine)
					{
						p_szWord  = strtok_s(p_szLine, " ", &p_NextToken);

						while (NULL != p_szWord)
						{
							push_back(p_vector, p_szWord);
							p_szWord = strtok_s(NULL, " ", &p_NextToken);
						}

						p_szLine = strtok_s(NULL, "\n", &p_LineNextToken);
					}
				}
			}
			fclose(p_file);
		}
	}
}


/*
	@input: Pointer to a vector object to which
			   word from file (@input-2) must be added

	@output: Number of word occurence in file

	@purpose : To search given no in vector
*/
int search_word(struct vector* p_vector, const char t_Word[])
{
	size_t st_TotalNoOfWords= p_vector->ssVectorNo;
	size_t i_wordCounter = 0;
	size_t i_FoundwordCnt = 0;

	for (i_wordCounter = 0; i_wordCounter < st_TotalNoOfWords; i_wordCounter++)
	{
		if (0 == _strcmpi(p_vector->p_wordArray[i_wordCounter], t_Word))
		{
			i_FoundwordCnt++;
		}
	}
	return i_FoundwordCnt;
}

/*
	@input: None
	@output: None
	@purpose : print help 
*/
void print_help(void)
{
	printf("cmd should be like [word][FILE_PATH]\n");
}