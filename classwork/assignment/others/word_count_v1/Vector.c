#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef long long int ssize_t;

struct vector
{
    char** m_ppList;
    ssize_t m_iSize;
};


/*  
    @input:     None

    @output:    Address of newly allocated instance of 
                struct vector 

    To allocate an instance of struct vector
*/
struct vector* CreateVector(void)
{
    struct vector* vNotes = (struct vector*) malloc (sizeof(struct vector));
    if (NULL == vNotes)
    {
        printf("Error: failed to create Vector.");
        return NULL;
    }

    vNotes->m_ppList = NULL;
    vNotes->m_iSize = 0;

    return vNotes;
}

/* 
    @input-1: Pointer to a vector to be released 
    
    @output: None   
    
    Frees the array inside the given vector(@input-1) and 
    free the vector itself.  
*/
void release_vector(struct vector* p_vector)
{
    int i = 0;
    if(p_vector == NULL)
    {
        return;
    }

    for(i=0; i < p_vector->m_iSize; i++)
    {
        if(p_vector->m_ppList[i] != NULL)
            free(p_vector->m_ppList[i]);
    }

    if(p_vector->m_ppList != NULL)
        free(p_vector->m_ppList); 
    
    free(p_vector);
}


/*
BOOLEAN push_back(struct vector* vNotes, char* pcWord); 
*/
BOOLEAN push_back(struct vector* vNotes, char* pcWord)
{
    int itr = 0;
    int iWordSize = 0;
    char* pTemp = NULL;

    if(NULL == vNotes || NULL == pcWord)
    {
        printf("Error: Parameter validation failed.");
        return FALSE; 
    }

    /*
        Get size of word to insert
    */
    for(iWordSize=0; pcWord[iWordSize] != '\0'; iWordSize++);

    pTemp = (char*) malloc(sizeof(char) * (iWordSize + 1));
    if(NULL == pTemp)
    {
        printf("malloc(): out of memory.");
        return FALSE;
    }

    for(itr=0; itr < iWordSize; itr++)
    {
        pTemp[itr] = pcWord[itr]; 
    }
    pTemp[iWordSize] = '\0';

    vNotes->m_ppList = (char **) realloc(vNotes->m_ppList, (vNotes->m_iSize+1) * sizeof(char *));
    if(NULL == vNotes->m_ppList)
    {
        printf("realloc():fatal:out of memory\n"); 
        return FALSE;
    }

    vNotes->m_ppList[vNotes->m_iSize] = pTemp;
    vNotes->m_iSize = vNotes->m_iSize + 1;
    pTemp = NULL;
    return TRUE;
}


/* 
    @input-1: Pointer to a vetor to be shown. 
    
    @output: BOOLEAN 

    Show the elements in the array inside the given 
    vector(@input-1)
*/
BOOLEAN show_vector(struct vector* vNotes)
{
    int iItr = 0;
    int iSize = 0;
    
    if (NULL == vNotes)
    {
        printf("show_vector: Parameter validation failed.");
        return FALSE;
    }

    iSize = vNotes->m_iSize;
    for(iItr = 0; iItr < iSize; iItr++)
    {
        printf("%s ", vNotes->m_ppList[iItr]);
    }

    return TRUE;
}


/* 
    @input-1: Pointer to file path
    @input-2: Pointer to a vector to be released 
    
    @output: BOOLEAN
    
    Reads the content of file and stores each word in vector.  
*/
BOOLEAN Tokenizer(char *FileName, struct vector* vNotes)
{
    char cChar;
    HANDLE hFile;
    int iSize = 0;
    TCHAR szBuffer[11];
    DWORD dwByteRead=0;
    char* pcWord = NULL;
    BOOLEAN bFlag = FALSE;

    hFile = CreateFile(FileName, 
                        GENERIC_READ, 
                        FILE_SHARE_READ, 
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL, 
                        NULL
                        );
            if (hFile == INVALID_HANDLE_VALUE)
            {
                printf("Error: Failed to open File.");
                return FALSE;
            }
    
    while (TRUE)
    {
        bFlag = ReadFile(hFile, &cChar, 1, &dwByteRead, NULL);
        if (bFlag == FALSE)
        {
            printf("Error: Failed to read file %ld.", GetLastError());
            return FALSE;
        }

        if(dwByteRead == 0 && pcWord == NULL)
        {
            break;
        }

        if (cChar >= 'A' && cChar <= 'Z' || cChar >= 'a' && cChar <= 'z' || cChar >= '1' && cChar <= '9')
        {
            iSize = dwByteRead + iSize;
            pcWord = (char*) realloc(pcWord, (iSize+1) * sizeof(char));
            if(pcWord == NULL)
            {
                printf("realloc: failed to allocate.");
                return FALSE;
            }

            pcWord[iSize-1] = cChar;
            pcWord[iSize] = '\0';
        }
        else
        {
           cChar = ' ';
        }

        if(cChar == ' ' && pcWord != NULL)
        {
            push_back(vNotes, pcWord);
            free(pcWord);
            pcWord = NULL;
            iSize = 0;
        }
    }

    free(pcWord);
    CloseHandle(hFile);

    return TRUE;
}


int CountWord(struct vector *vNotepad, char* pcWordToSearch)
{
    int iItr = 0;
    int iInner = 0;
    int iCount = 0;
    int iWordSize = 0;
    char* pcWord = NULL;
    char** ppList = vNotepad->m_ppList;

    for(iWordSize=0; pcWordToSearch[iWordSize] != '\0'; iWordSize++);

    for (iItr=0; iItr<vNotepad->m_iSize; iItr++)
    {
        pcWord = ppList[iItr];
        iInner = 0;
        while(pcWord[iInner] == pcWordToSearch[iInner] && pcWord[iInner] != '\0' && pcWordToSearch[iInner] != '\0')
        {
            iInner++;
        }

        if(iInner == iWordSize)
            iCount++;
    }

    return iCount;
}

int main(int argc, TCHAR *argv[])
{
    int iCnt = 0;
    BOOLEAN bFlag;
    char szWord[20];
    struct vector* vNotes;
   
    if(argc != 2)
    {
        printf("Error: File name not provided");
        exit(EXIT_FAILURE);
    }

    vNotes = CreateVector();
    if (NULL == vNotes)
    {
        printf("Error: failed to create Vector.");
        exit(EXIT_FAILURE);
    }

    bFlag = Tokenizer(argv[1], vNotes);
    if(FALSE == bFlag)
    {
        printf("Error: failed to read file.");
        exit(EXIT_FAILURE);
    }

    //show_vector(vNotes);

    printf("\n Enter a word to search:");
    scanf("%s", szWord);
    iCnt = CountWord(vNotes, szWord);

    printf("\nWORD APPEARS: %d times \n", iCnt);
    release_vector(vNotes);

    exit(EXIT_SUCCESS);
}