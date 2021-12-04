#ifndef MAIN_H /// including a library
#define MAIN_H

#include "main.h"

#endif

void validateMenuInput(int *continueFlag, int *value)
{
    assert(*continueFlag == 0); /// checks if the continueFlag before the function is equal to 0.
    char c; /// a character used for validating purposes
    int inputValidateCheck = scanf("%d%c", value, &c);
    if(inputValidateCheck != 2)
    {
        printf("Your input was invalid. Please re-enter.\n");
        *continueFlag = 1;
        fflush(stdin);
        return;
    }
    if(c != '\n')
    {
        printf("Your input was followed by invalid characters. Please enter only the integer of the menu.\n");
        *continueFlag = 1;
        fflush(stdin);
        return;
    }
    if(*value > 4 || *value < 0) /// the menu only provides options 0-4
    {
        printf("The menu contains choices from 0 to 3. Please enter a valid number.\n");
        *continueFlag = 1;
        fflush(stdin);
        return;
    }
    printf("\n");
    assert(*value <=4 && *value >= 0);
    assert(*continueFlag == 0); /// the function has to pass without the continueFlag value changing to 1.
}

void inputCheck(FILE **Input)
{

    char inputFileName[257] = {}; /// for opening of the file.
    char c; /// for data validating purposes

    while(1)
    {
        printf("\nPlease enter the file name with its extension (e.g. input.txt), where the data is stored in the working directory.\n");

        int inputValidateCheck = scanf("%s%c", inputFileName, &c); 

        if(inputValidateCheck != 2)
        {
            printf("There were not enough elements in the given input. Please try again.\n");
            fflush(stdin);
            continue;
        }

        if(c != '\n')
        {
            printf("There were invalid elements entered after the input file name. Please try again.\n");
            fflush(stdin);
            continue;
        }

        *Input = fopen(inputFileName, "r");

        if(*Input == NULL) /// if there is no access to the given file.
        {
            printf("There has been an error trying to access the file by the name of %s. Please check whether such file exists and try again.\n", inputFileName);
            continue;
        }

        break;
    }

    printf("\n");
    assert(*Input != NULL); /// the function may only end after having its Input stream set.
}

void fileEmptyCheck(FILE *Input, int *fileEmptyFlag)
{
    assert(*fileEmptyFlag == 0); /// checks if the condition of the flag being set to 0 is fulfilled.
    char nextSymbolCheck = getc(Input);

    if(nextSymbolCheck == EOF)
    {
        *fileEmptyFlag = 1;
        fclose(Input);
        return;
    }

    ungetc(nextSymbolCheck, Input); /// if c != EOF the character is put back to the stream.
}

void readFromFile(FILE **Input, int *value, int *breakFlag, int *errorFlag, int *eofFlag)
{
    assert(*Input != NULL);
    assert(*breakFlag == 0);
    assert(*errorFlag == 0);
    assert(*eofFlag == 0);
    /// asserts the arguments to the function are correct.

    char c; /// used for validating

    int inputValidateCheck = fscanf(*Input, "%d", value);
    if(inputValidateCheck != 1)
    {
        if(!feof(*Input))
        {
            *errorFlag = 1;
            return;
        }
        *eofFlag = 1;
        return;
    }

    inputValidateCheck = fscanf(*Input, "%c", &c);
    if(inputValidateCheck != 1) /// if a char cannot be read, it is EOF.
    {
        *breakFlag = 1;
        return;
    }

    if(c != ' ' && c != '\n') /// if a char right after the integer has been read, it has to be a whitespace
    {
        *errorFlag = 1;
        return;
    }
}

void deleteInput(int *valueToDelete)
{
    char c; /// used for validating purposes
    while(1)
    {
        printf("Please enter the value of the list element to be deleted.\n");

        int inputValidateCheck = scanf("%d%c", valueToDelete, &c);

        if(inputValidateCheck != 2)
        {
            printf("The value was of invalid format. Please try again.\n");
            fflush(stdin);
            continue;
        }

        if(c != '\n')
        {
            printf("The value was followed by non-digit characters. Please try again.\n");
            fflush(stdin);
            continue;
        }

        assert(valueToDelete != NULL); /// if this point in function is reached, there should be a value to this destination.
        return;
    }
}
