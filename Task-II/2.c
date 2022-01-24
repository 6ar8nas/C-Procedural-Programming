/// 2110556, sgriskus2002@gmail.com, 2 uzduotis, uzduoties variantas nr. 9
#include <stdio.h>
#define MAX_SIZE 100000

void clearSymbols()
{
    while(getchar() != '\n')
        ;
}

int isExtremum (int element1, int element2, int element3)
{
    if(((element2 < element3) && (element2 < element1)) || ((element2 > element3) && (element2 > element1)))
        return 1;
    return 0;
}

int inputValid (int *target)
{
    if((scanf("%d", target) == 1) && (getchar() == '\n'))
        return 1;
    return 0;
}

void inputArraySize (int *arraySize)
{
    printf("Please enter the integer value of N.\n\n");
    while(!inputValid (arraySize))
    {
        printf("Error. Please enter a valid N value.\n");
        clearSymbols();
    }
}
void inputElements (int arraySize, int elements[])
{
    printf("%s", (arraySize > 0) ? "\nNow enter the integer type elements of the vector one by one.\n\n"
           : "\nYour N input was below or equal to 0, therefore the vector will be empty.\n");
    for(int i = 0; i < arraySize; ++i)
    {
        if(inputValid(&elements[i]))
            ;
        else
        {
            clearSymbols();
            printf("Error. Your input was faulty. You can only enter integers.\n");
            --i;
        }
    }
}

void processing(int arraySize, int elements[], int *extremumsCount, int maxLengthPos[])
{
    int extremums[arraySize-2];
    for(int i = 1; i < arraySize-1; ++i)
    {
        if(isExtremum(elements[i-1], elements[i], elements[i+1]))
        {
            extremums[*extremumsCount]=i;
            ++(*extremumsCount);
        }
        if(*extremumsCount <= 2)
        {
            maxLengthPos[*extremumsCount - 1] = extremums[*extremumsCount - 1];
        }
        else if(*extremumsCount > 2)
        {
            if((maxLengthPos[1] - maxLengthPos[0]) < (extremums[*extremumsCount - 1]-extremums[*extremumsCount - 2]))
            {
                maxLengthPos[0] = extremums[*extremumsCount - 2];
                maxLengthPos[1] = extremums[*extremumsCount - 1];
            }
        }
    }
}

void output (int extremumsCount, int maxLengthPos[])
{
    if(extremumsCount < 2)
        printf("\nThere weren't enough extremums recorded in the vector.");
    else
    {
        printf("\nThe highest distance is between extremums %d and %d. This distance is equal to %d.",
               maxLengthPos[0] + 1, maxLengthPos[1] + 1, maxLengthPos[1] - maxLengthPos[0]);
    }
}

int main()
{
    printf("Program loaded.\n");
    int n;
    inputArraySize(&n);
    int elements[n];
    inputElements(n, elements);
    int extremumsCount = 0, maxLengthPos[2];
    processing(n, elements, &extremumsCount, maxLengthPos);
    output(extremumsCount, maxLengthPos);
    printf("\nProgram terminated.");
    return 0;
}
