#include <windows.h>
#include <stdio.h>

using namespace std;

//***********************************************************************************************************
class word
{
    char* m_pchWord;
    unsigned int m_uiLineNum;
    unsigned int m_uiWordNum;

    public:
        word();
        BOOLEAN setWord(char* chWord);
        void setWordNum(unsigned int iWordnum);
        void setLineNumber(unsigned int iLineNum);
        
        char* getWord();
        unsigned int getWordNum();
        unsigned int getLineNumber();
};

word::word()
{
    m_pchWord = NULL;
    m_uiLineNum = 0;
    m_uiWordNum = 0;
}

BOOLEAN word::setWord(char* pWord)
{
    int i = 0;
    unsigned int iWordSize = 0;

    if (NULL == pWord)
    {
        printf("setWord:Parameter validation failed.");
        return FALSE;
    }

    for(iWordSize=0; pWord[iWordSize] != '\0'; iWordSize++);

    m_pchWord = (char*) malloc(sizeof(char) * (iWordSize + 1));
    if (NULL == m_pchWord)
    {
        printf("Failed to allocate word");
        return FALSE;
    }

    i = 0;
    while(pWord[i] != '\0')
    {
        m_pchWord[i] = pWord[i];
        i++;
    }

    m_pchWord[iWordSize] = '\0';

    return TRUE;
}

void word::setLineNumber(unsigned int iLineNum)
{
    this->m_uiLineNum = iLineNum;
}

void word::setWordNum(unsigned int iWordnum)
{
    this->m_uiWordNum = iWordnum;
}

unsigned int word::getLineNumber ()
{
    return this->m_uiLineNum;
}

unsigned int word::getWordNum()
{
    return this->m_uiWordNum;
}

char* word::getWord()
{
    return this->m_pchWord;
}

//************************************************************************************************************

template <typename T> class vector
{
    T** m_ppElements;
    unsigned int m_TotElements;

public:
    vector();
    BOOLEAN push_back(T*);
    void Show();
    unsigned int Size();
    T* at(unsigned int iPos);
    void release_vector();
};

template <typename T> unsigned int vector<T>::Size()
{
    return m_TotElements;
}

template <typename T> T* vector<T>::at(unsigned int iPos)
{
    return m_ppElements[iPos];
}

template <typename T> vector<T>::vector()
{
    m_ppElements = NULL;
    m_TotElements = 0;
}

template <typename T> BOOLEAN vector<T>::push_back(T* Val)
{
    if (NULL == Val)
    {
        printf("Error: Parameter validation failed");
        return FALSE;
    }

    m_ppElements = (T**) realloc(m_ppElements, (m_TotElements+1) * sizeof(T*));
    if (NULL == m_ppElements)
    {
        printf("push_back: Failed to allocat memory");
        return FALSE;
    }

    m_ppElements[m_TotElements] = Val;
    m_TotElements = m_TotElements + 1;

    return TRUE;
}

template <typename T> void vector<T>::Show()
{
    int itr;
    for(itr=0; itr < m_TotElements; itr++)
    {
        printf("%s\n", m_ppElements[itr]->getWord());
    }
}

/* 
    @input-1: Pointer to a vector to be released 
    
    @output: None   
    
    Frees the array inside the given vector(@input-1) and 
    free the vector itself.  
*/
template <typename T> void vector<T>::release_vector()
{
    int i = 0;
    if(m_ppElements == NULL)
    {
        return;
    }

    for(i=0; i < m_TotElements; i++)
    {
        if(m_ppElements[i] != NULL)
            free(m_ppElements[i]);
    }

    free(m_ppElements); 
}

//******************************************************************************************************

BOOLEAN Tokenizer(char* FileName, vector<word>* Notepad)
{
    char cChar;
    HANDLE hFile;
    int iSize = 0;
    TCHAR szBuffer[11];
    DWORD dwByteRead=0;
    char* pcWord = NULL;
    BOOLEAN bFlag = FALSE;
    word* cCurWord = NULL;
    unsigned int iLineNum = 1;
    unsigned int iWordNum = 1;

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
    
    while(TRUE)
    {
        bFlag = ReadFile(hFile, &cChar, 1, &dwByteRead, NULL);
        if (FALSE == bFlag)
        {
            printf("Error: Failed to read file");
            CloseHandle(hFile);
            return FALSE;
        }

        if (0 == dwByteRead && pcWord == NULL)
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
                CloseHandle(hFile);
                return FALSE;
            }

            pcWord[iSize-1] = cChar;
            pcWord[iSize] = '\0';
        }
        else
        {
            if(cChar == '\n')
            {
              iLineNum += 1;
              iWordNum = 1;  
            }

           cChar = ' ';
        }

        if(cChar == ' ' && pcWord != NULL)
        {
            cCurWord = new word();
            
            cCurWord->setLineNumber(iLineNum);
            cCurWord->setWord(pcWord);
            cCurWord->setWordNum(iWordNum++);
            bFlag = Notepad->push_back(cCurWord);
            if (FALSE == bFlag)
            {
                printf("Error: Failed to push data");
                free(pcWord);
                CloseHandle(hFile);
                return FALSE;
            }
            
            free(pcWord);
            pcWord = NULL;
            iSize = 0;
        }

    }

    if(pcWord != NULL)
    {
        free(pcWord);
    }

    CloseHandle(hFile);
    return TRUE;
}

void SearchWord(vector<word>* Notepad, char* pcWordToSearch)
{
    int iItr = 0;
    int iWordSize = 0;
    BOOLEAN bFlag = FALSE;
    int iCounter = 0;
    char* pcWord = NULL;
    int iTotWord = 0;
    word* cCurWord = NULL;

    for(iWordSize=0; pcWordToSearch[iWordSize] != '\0'; iWordSize++);

    iTotWord = Notepad->Size();
    for (iItr = 0; iItr < iTotWord; iItr++)
    {
        cCurWord = Notepad->at(iItr);
        pcWord = cCurWord->getWord();

        if (strncmp(pcWord, pcWordToSearch, iWordSize) == 0)
        {
            iCounter++;
            printf("\nWord: '%s' \nLine Number: %d \nPosition: %d\n", pcWord, cCurWord->getLineNumber(), cCurWord->getWordNum());
        }
    }

    if (iCounter == 0)
    {
        printf("\nWord: '%s' \nLine Number: Not found \nPosition: Not found \n", pcWordToSearch);
    }
}

int main(int argc, char* argv[])
{
    BOOLEAN bRet;
    char szWord[20];
    vector<word>* Notepad = new vector<word>();

    if(argc != 2)
    {
        printf("Error: File name not provided");
        exit(EXIT_FAILURE);
    }

    bRet = Tokenizer(argv[1], Notepad);
    if (FALSE == bRet)
    {
        printf("\nError: Failed to Tokenize the file \n");
        exit(EXIT_FAILURE);
    }

    Notepad->Show();
    printf("\nEnter a word to search:");
    scanf("%s", szWord);
    SearchWord(Notepad, szWord);

    Notepad->release_vector();
    delete(Notepad);
    
    exit(EXIT_SUCCESS);
}

