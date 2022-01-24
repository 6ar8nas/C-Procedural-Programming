#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

clock_t start, end;

typedef struct coordinate
{
    int x, y;
} coordinate;

typedef struct slot
{
    int size, direction; // 0 - horizontally, 1 - vertically
    int intersectionsCount, intersectionPos[256];
    coordinate intersection[256];
    coordinate start;
    int occupied;
} slot;

typedef struct word
{
    char word[256];
    int taken;
    int size;
} word;

int copyMap(char fileName[], char **array, int *matrixLength, int *matrixWidth);
void mapUI(int check);

int copyDictionary(char fileName[], word words[], int longestWord, int *wordCount);
int partition(word words[], int arrayStart, int arrayEnd);
void quickSort(word words[], int arrayStart, int arrayEnd);
void dictionaryUI(int check);

void fillContainers(slot container[], int *slots, char *array, int matrixLength, int matrixWidth);
void bubbleSort(slot array[], int arraySize);

int findIntersections(char *str1, char *str2);
void countIntersections(word words[], int **intersections, int wordCount);

int putWord(char *word, char **mapArray, int matrixLength, int matrixWidth, coordinate start, int mode);
int completeCrossword(word words[], int wordCount, char **mapArray, int matrixLength, int matrixWidth, slot container[], int containerCount);
void completionUI(int check);

void printMap(char *array, int matrixLength, int matrixWidth);
void printDictionary(word words[], int wordCount);
void printContainers(slot container[], int containerCount);
void printIntersections(int *array, int wordCount);

int checkIfUnchanged(char *word, char *mapArray, int matrixLength, int matrixWidth, coordinate start, int mode);
int checkIfCorrect(char *mapArray, int matrixLength, int matrixWidth);
int delWord(word *word, char **mapArray, int matrixLength, int matrixWidth, int index, slot containers[], int containerCount);
void resetMap(char **mapArray, int matrixLength, int matrixWidth, word words[], int wordCount);
int main()
{
    int userInterfaceVar = 0;

    char *mapArray = NULL;
    int matrixLength = 0, matrixWidth = 0;

    userInterfaceVar = copyMap("src/map.txt", &mapArray, &matrixLength, &matrixWidth);
    mapUI(userInterfaceVar);

    word words[matrixLength*matrixWidth/2];
    int wordCount = 0;
    userInterfaceVar = copyDictionary("src/dictionary.txt", words, (matrixLength >= matrixWidth) ? (matrixLength) : (matrixWidth), &wordCount);
    dictionaryUI(userInterfaceVar);

    quickSort(words, 0, wordCount-1);
    slot container[wordCount];
    int containerCount = 0;

    fillContainers(container, &containerCount, mapArray, matrixLength, matrixWidth);

    bubbleSort(container, containerCount);

    int *intersections = calloc(wordCount*wordCount, sizeof(int));

    countIntersections(words, &intersections, wordCount);

    printDictionary(words, wordCount); // TO COMMENT WHEN LAUNCHING
    printIntersections(intersections, wordCount);// TO COMMENT WHEN LAUNCHING
    printContainers(container, containerCount);// TO COMMENT WHEN LAUNCHING
    printMap(mapArray, matrixLength, matrixWidth);// TO COMMENT WHEN LAUNCHING

    srand(time(NULL));

    userInterfaceVar = completeCrossword(words, wordCount, &mapArray, matrixLength, matrixWidth, container, containerCount); // FAULTY
    completionUI(userInterfaceVar);
    
    // TO UNCOMMENT WHEN LAUNCHING printMap(mapArray, matrixLength, matrixWidth);

    free(mapArray);
    free(intersections);
}

int copyMap(char fileName[], char **array, int *matrixLength, int *matrixWidth)
{
    FILE *Input;

    Input = fopen(fileName, "r");
    if(Input == NULL)
    {
        return -1;
    }

    char buffer[256];
    int arrayPosition = 0;

    while (fscanf(Input, "%s", buffer) == 1)
    {
        if((*matrixLength) == 0)
            (*matrixLength) = strlen(buffer);
        ++(*matrixWidth);

        *array = realloc(*array, (*matrixLength) * (*matrixWidth) * sizeof(char));
        if(!array)
        {
            return -2;
        }

        arrayPosition = (*matrixLength) * ((*matrixWidth)-1);
        for(int i = arrayPosition; i < arrayPosition + (*matrixLength); ++i)
        {
            (*array)[i] = buffer[i-arrayPosition];
        }
    }

    fclose(Input);
    return 1;
}

void mapUI(int check)
{
    switch(check)
    {
    case 1:
    {
        printf("The crossword layout has been successfully obtained.\n");
        break;
    }
    case -1:
    {
        printf("The input name for the file has been incorrect. Please make sure your file is map.txt and it is located in the /src/ folder of the working directory.\n");
        exit(-1);
    }
    case -2:
    {
        printf("The processor could not allocate the necessary resources for the crossword layout.\n");
        exit(-2);
    }
    }
}

int copyDictionary(char fileName[], word words[], int longestWord, int *wordCount)
{
    FILE *Input;

    Input = fopen(fileName, "r");
    if(Input == NULL)
    {
        return -1;
    }

    char buffer[256];

    while (fscanf(Input, "%s", buffer) == 1)
    {
        int length = strlen(buffer);
        if(length > longestWord || length < 2)
            continue;
        words[*wordCount].size = length;
        words[*wordCount].taken = 0;
        strcpy(words[*wordCount].word, (const char*)buffer);
        ++(*wordCount);
    }
    fclose(Input);
    return 1;
}

void dictionaryUI(int check)
{
    switch(check)
    {
    case 1:
    {
        printf("The dictionary has been successfully obtained.\n");
        break;
    }
    case -1:
    {
        printf("The input name for the file has been incorrect. Please make sure your file is dictionary.txt and it is located in the /src/ folder of the working directory.\n");
        exit(-1);
    }
    case -2:
    {
        printf("The processor could not allocate the necessary resources for the dictionary.\n");
        exit(-2);
    }
    }
}

int partition(word words[], int arrayStart, int arrayEnd)
{
    int pivot = words[arrayEnd].size;
    int i = arrayStart - 1;
    for (int j = arrayStart; j < arrayEnd; ++j)
    {
        if(words[j].size > pivot)
        {
            ++i;
            word temp = words[j];
            words[j] = words[i];
            words[i] = temp;
        }
    }
    ++i;
    word temp = words[arrayEnd];
    words[arrayEnd] = words[i];
    words[i] = temp;
    return i;
}

void quickSort(word words[], int arrayStart, int arrayEnd) 
{
    if(arrayStart >= arrayEnd || arrayStart < 0)
    {
        return;
    }

    int p = partition(words, arrayStart, arrayEnd);
    quickSort(words, arrayStart, p - 1);
    quickSort(words, p + 1, arrayEnd);
}

void bubbleSort(slot array[], int arraySize)
{
    int swapped = 1;
    while(swapped)
    {
        swapped = 0;
        for(int i = 0; i < arraySize; ++i)
        {
            if(array[i-1].size > array[i].size)
            {
                slot temp = array[i-1];
                array[i-1] = array[i];
                array[i] = temp;
                swapped = 1;
            }
        }
        --arraySize;
    }
    return;
}

void fillContainers(slot container[], int *slots, char *array, int matrixLength, int matrixWidth)
{
    for(int i = 0; i < matrixWidth; ++i)
    {
        for(int j = 0; j < matrixLength-1; ++j)
        {
            if(array[matrixLength*i+j] == '0' && array[matrixLength*i+(j+1)] == '0')
            {
                int temp = j;
                container[*slots].direction = 0;
                container[*slots].intersectionsCount = 0;
                container[*slots].start.x = j;
                container[*slots].start.y = i;
                container[*slots].occupied = 0;
                if((array[matrixLength*(i+1)+j] == '0') || (i != 0 && array[matrixLength*(i-1)+j] == '0'))
                {
                    container[*slots].intersectionPos[container[*slots].intersectionsCount] = j-container[*slots].start.x;
                    container[*slots].intersection[container[*slots].intersectionsCount].x = container[*slots].start.x + container[*slots].intersectionPos[container[*slots].intersectionsCount];
                    container[*slots].intersection[container[*slots].intersectionsCount].y = container[*slots].start.y;
                    ++(container[*slots].intersectionsCount);
                }                
                while(array[matrixLength*i+(j+1)] != '1' && ((j+1) % matrixLength != 0))
                {
                    ++j;
                    if((array[matrixLength*(i+1)+j] == '0') || (i != 0 && array[matrixLength*(i-1)+j] == '0'))
                    {
                        container[*slots].intersectionPos[container[*slots].intersectionsCount] = j-container[*slots].start.x;
                        container[*slots].intersection[container[*slots].intersectionsCount].x = container[*slots].start.x + container[*slots].intersectionPos[container[*slots].intersectionsCount];
                        container[*slots].intersection[container[*slots].intersectionsCount].y = container[*slots].start.y;
                        ++(container[*slots].intersectionsCount);
                    }
                }
                container[*slots].size = j - temp + 1;

                ++(*slots);
            }
        }
    }
    for(int i = 0; i < matrixLength; ++i)
    {
        for(int j = 0; j < matrixWidth-1; ++j)
        {
            if(array[matrixLength*j+i] == '0' && array[matrixLength*(j+1)+i] == '0')
            {
                int temp = j;
                container[*slots].direction = 1;
                container[*slots].intersectionsCount = 0;
                container[*slots].start.x = i;
                container[*slots].start.y = j;

                if((array[matrixLength*j+(i+1)] == '0') || (i != 0 && array[matrixLength*j+(i-1)] == '0'))
                {
                    container[*slots].intersectionPos[container[*slots].intersectionsCount] = j-container[*slots].start.y;
                    container[*slots].intersection[container[*slots].intersectionsCount].x = container[*slots].start.x;
                    container[*slots].intersection[container[*slots].intersectionsCount].y = container[*slots].start.y + container[*slots].intersectionPos[container[*slots].intersectionsCount];
                    ++(container[*slots].intersectionsCount);
                }
                while(array[matrixLength*(j+1)+i] != '1' && ((j+1) % matrixWidth != 0))
                {
                    ++j;
                    if((array[matrixLength*j+(i+1)] == '0') || (i != 0 && array[matrixLength*j+(i-1)] == '0'))
                    {
                        container[*slots].intersectionPos[container[*slots].intersectionsCount] = j-container[*slots].start.y;
                        container[*slots].intersection[container[*slots].intersectionsCount].x = container[*slots].start.x;
                        container[*slots].intersection[container[*slots].intersectionsCount].y = container[*slots].start.y + container[*slots].intersectionPos[container[*slots].intersectionsCount];
                        ++(container[*slots].intersectionsCount);
                    }
                }
                container[*slots].size = j - temp + 1;

                ++(*slots);
            }
        }
    }
}

int findIntersections(char *str1, char *str2)
{
    int sizeStr1 = strlen(str1);
    int sizeStr2 = strlen(str2);

    int counter = 0;

    for(int i = 0; i < sizeStr1; ++i)
    {
        for(int j = 0; j < sizeStr2; ++j)
        {
            if(str1[i] == str2[j])
            {
                ++counter;
                break;
            }
        }
    }

    return counter;
}

void countIntersections(word words[], int **intersections, int wordCount)
{
    for(int i = 0; i < wordCount; ++i)
    {
        for(int j = 0; j < wordCount; ++j)
        {
            (*intersections)[wordCount*i+j] = (i == j) ? 0 : findIntersections(words[j].word,words[i].word);
        }
    }
}

int putWord(char *word, char **mapArray, int matrixLength, int matrixWidth, coordinate start, int mode) // mode: 0 - horizontally, 1 - vertically
{
    int i = start.y;
    int j = start.x;
    if(mode == 0) 
    {
        for(int wordPos = 0; j <= strlen(word); ++j, ++wordPos)
        {
            if((*mapArray)[i*matrixLength+j] != '1')
            {
                (*mapArray)[i*matrixLength+j] = word[wordPos];
            }
            else
                return -1;
        }
        return 0;
    }
    else if(mode == 1)
    {
        for(int wordPos = 0; i <= strlen(word); ++i, ++wordPos)
        {
            if((*mapArray)[i*matrixLength+j] != '1')
            {
                (*mapArray)[i*matrixLength+j] = word[wordPos];
            }
            else
                return -1;
        }
        return 0;
    }
}

int completeCrossword(word words[], int wordCount, char **mapArray, int matrixLength, int matrixWidth, slot container[], int containerCount) // TO FIX
{
    start = clock();
    while(!checkIfCorrect(*mapArray, matrixLength, matrixWidth))
    {
        for(int i = containerCount-1; i >= 0; --i)
        {
            for(int j = rand() % wordCount, index = 0; index < wordCount; j = (j + 1) % wordCount, ++index)
            {
                if(words[j].size == container[i].size && words[j].taken != 1)
                {
                    putWord(words[j].word,mapArray,matrixLength,matrixWidth,container[i].start,container[i].direction);
                    words[j].taken = 1;
                    printMap(*mapArray,matrixLength,matrixWidth); // TO COMMENT WHEN LAUNCHING
                    completeCrossword(words,wordCount,mapArray,matrixLength,matrixWidth,container,containerCount-1);
                    if(!checkIfUnchanged(words[j].word,*mapArray,matrixLength,matrixWidth,container[i].start,container[i].direction))
                    {
                        putWord(words[j].word,mapArray,matrixLength,matrixWidth,container[i].start,container[i].direction);
                        if(!completeCrossword(words,wordCount,mapArray,matrixLength,matrixWidth,container,containerCount-1))
                        {
                            delWord(&words[j], mapArray, matrixLength, matrixWidth, i, container, containerCount);
                            return -1;
                        }
                        continue;
                    }
                }
            }
        }
        end = clock();
        float duration = (float)(end - start) / (float) CLOCKS_PER_SEC;
        if(duration > 1)
        {
            resetMap(mapArray, matrixLength, matrixWidth, words, wordCount);
            return -1;
        }
    }
    return 1;
}

void completionUI(int check)
{
    switch(check)
    {
    case 1:
    {
        printf("The crossword has been successfully created.\n");
        break;
    }
    case -1:
    {
        printf("No possible combination of the words has been found that would match the requirements.\n");
        exit(-1);
    }
    }
}

void printMap(char *array, int matrixLength, int matrixWidth)
{
    for(int i = 0; i < matrixLength * matrixWidth; ++i)
    {
        if(i % matrixLength == 0 && i != 0)
            printf("\n");
        printf("%c ", array[i]);
    }
    printf("\n\n");
}

void printDictionary(word words[], int wordCount)
{
    for(int i = 0; i < wordCount; ++i)
    {
        printf("%d. %s\n", i, words[i].word);
    }
}

void printContainers(slot container[], int containerCount)
{
    for(int i = 0; i < containerCount; ++i)
    {
        printf("%d. dir: %d, size: %d, start x: %d, start y: %d\n", i, container[i].direction, container[i].size, container[i].start.x, container[i].start.y);
        printf("intersects in:\n");
        for(int j = 0; j < container[i].intersectionsCount; ++j)
        {
            printf("x: %d y: %d\n", container[i].intersection[j].x, container[i].intersection[j].y);
        }
        printf("\n");
    }
}

void printIntersections(int *array, int wordCount)
{
    for(int i = 0; i < wordCount; ++i)
    {
        for(int j = 0; j < wordCount; ++j)
        {
            printf("%d ", array[wordCount*i+j]);
        }
        printf("\n");
    }
}

int checkIfUnchanged(char *word, char *mapArray, int matrixLength, int matrixWidth, coordinate start, int mode) // mode: 0 - horizontally, 1 - vertically
{
    int i = start.y, j = start.x;
    if(mode == 0)
    {
        for(int index = 0; index < strlen(word); ++index)
            if(word[index] != mapArray[i*matrixLength+j+index])
            {
                return 0;
            }
        return 1;
    }
    if(mode == 1)
    {
        for(int index = 0; index < strlen(word); ++index)
            if(word[index] != mapArray[(i+index)*matrixLength+j])
            {
                return 0;
            }
        return 1;
    }
}

int checkIfCorrect(char *mapArray, int matrixLength, int matrixWidth)
{
    for(int i = 0; i < matrixLength * matrixWidth; ++i)
    {
        if(mapArray[i] == '0')
            return 0;
    }
    return 1;
}

int delWord(word *word, char **mapArray, int matrixLength, int matrixWidth, int index, slot containers[], int containerCount) // mode: 0 - horizontally, 1 - vertically
{
    int i = containers[index].start.y;
    int j = containers[index].start.x;
    if(containers[index].direction == 0) 
    {
        for(int wordPos = 0; j <= word->size; ++j, ++wordPos)
        {
            for(int k = 0; k < containerCount; ++k)
            {
                for(int l = 0; l < containers[k].intersectionsCount; ++l)
                {
                    if(containers[k].intersection[l].x == j && containers[k].intersection[l].y == i)
                    {
                        ++j;
                        ++wordPos;
                        k = containerCount;
                        break;                        
                    }
                }
            }
            if((*mapArray)[i*matrixLength+j] != '1')
            {
                (*mapArray)[i*matrixLength+j] = '0';
            }
            else
                return -1;
        }
        return 0;
    }
    else if(containers[index].direction == 1)
    {
        for(int wordPos = 0; i <= word->size; ++i, ++wordPos)
        {
            for(int k = 0; k < containerCount; ++k)
            {
                for(int l = 0; l < containers[k].intersectionsCount; ++l)
                {
                    if(containers[k].intersection[l].x == j && containers[k].intersection[l].y == i)
                    {
                        ++i;
                        ++wordPos;
                        k = containerCount;
                        break;                        
                    }
                }
            }
            if((*mapArray)[i*matrixLength+j] != '1')
            {
                (*mapArray)[i*matrixLength+j] = '0';
            }
            else
                return -1;
        }
        word->taken = 0;
        return 0;
    }
}

void resetMap(char **mapArray, int matrixLength, int matrixWidth, word words[], int wordCount) 
{
    for(int i = 0; i < matrixLength * matrixWidth; ++i)
    {
        if((*mapArray)[i] != '1')
            (*mapArray)[i] = '0';
    }
    for(int i = 0; i < wordCount; ++i)
    {
        words[i].taken = 0;
    }
}
