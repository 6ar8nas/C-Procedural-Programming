#include "main.h"

void validateMenuInput(FILE *Stream, int *continueFlag, int *value)
{
    char c; /// a character used for validating purposes
    int inputValidateCheck = fscanf(Stream, " %d%c", value, &c);
    if(inputValidateCheck != 2)
    {
        printf("Your input was invalid. Please re-enter.\n");
        *continueFlag = 1;
        while ((getc(Stream)) != '\n')
            ;
        return;
    }
    if(c != '\n')
    {
        printf("Your input was followed by invalid characters. Please enter only the integer of the menu.\n");
        *continueFlag = 1;
        while ((getc(Stream)) != '\n')
            ;
        return;
    }
    if(*value > 4 || *value < 0) /// the menu only provides options 0-4
    {
        printf("The menu contains choices from 0 to 4. Please enter a valid number.\n");
        *continueFlag = 1;
        return;
    }
    printf("\n");
}

void inputCheck(FILE *Stream, FILE **Input, char fileName[])
{
    char c; /// for data validating purposes

    while(1)
    {
        printf("\nPlease enter the file name with its extension (e.g. input.txt), where the data is stored in the working directory.\n");

        int inputValidateCheck = fscanf(Stream, " %s%c", fileName, &c); 

        if(inputValidateCheck != 2)
        {
            printf("There were not enough elements in the given input. Please try again.\n");
            while ((getc(Stream)) != '\n')
                ;
            continue;
        }

        if(c != '\n')
        {
            printf("There were invalid elements entered after the input file name. Please try again.\n");
            while ((getc(Stream)) != '\n')
                ;
            continue;
        }

        *Input = fopen(fileName, "r");

        if(*Input == NULL) /// if there is no access to the given file.
        {
            printf("There has been an error trying to access the file by the name of %s. Please check whether such file exists and try again.\n", fileName);
            continue;
        }

        break;
    }

    printf("\n");
}

int fileEmptyCheck(FILE *Input)
{
    char nextSymbolCheck = getc(Input);

    if(nextSymbolCheck == EOF)
    {
        fclose(Input);
        return 1;
    }

    ungetc(nextSymbolCheck, Input); /// if c != EOF the character is put back to the stream.
    return 0;
}

void readFromFile(FILE **Input, int *value, int *breakFlag, int *errorFlag, int *eofFlag)
{
    char c; /// used for validating

    int inputValidateCheck = fscanf(*Input, " %d", value);
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

void deleteInput(FILE *Stream, int *valueToDelete)
{
    char c; /// used for validating purposes
    while(1)
    {
        printf("Please enter the value of the list element to be deleted.\n");

        int inputValidateCheck = fscanf(Stream, " %d%c", valueToDelete, &c);

        if(inputValidateCheck != 2)
        {
            printf("The value was of invalid format. Please try again.\n");
            while ((getc(Stream)) != '\n')
                ;
            continue;
        }

        if(c != '\n')
        {
            printf("The value was followed by non-digit characters. Please try again.\n");
            while ((getc(Stream)) != '\n')
                ;
            continue;
        }

        return;
    }
}
