/// The program was created by Sarunas Griskus. Its purpose is checking the input file for words satisfying the condition of matching second and third last characters and printing it to a output file.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findSatisfyingWords(char line[], FILE *Output)
{
    if(strlen(line) < 3)
        return;
    char **words = NULL, wordAmount = 0;
    int howManySymbolsRead = 0;
    char word[256] = {};
    for(int pos = 0; sscanf(line + pos, " %s%n", word, &howManySymbolsRead) != EOF; pos += howManySymbolsRead)
    {
        if(strlen(word) < 3)
            continue;
        words = realloc (words, (++wordAmount)*sizeof(char *));
        words[wordAmount - 1] = calloc(strlen(word)+1, sizeof(char));
        strcpy(words[wordAmount - 1], word);
    }
    for(int i = 0; i < wordAmount; ++i)
    {
        if(words[i][1] == words[i][strlen(words[i])-3])
            fprintf(Output, "%s ", words[i]);
    }
    fprintf(Output, "\n");
    free(words);
}

int main()
{
    printf("The program will read 2 lines from the standard input stream, representing input and output file names respectively.\n");
    printf("It will then read the symbols separated by whitespaces from the input file and output them if a condition\nof their second character matching the third symbol from the back is satisfied.\nFor example: 12341234, ABBA, etc..\n\n");

    FILE *Input;
    FILE *Output;

    char inputFile[256] = {}, outputFile[256] = {};

    printf("Please enter the input file name. This file should be located in the working directory.\n");
    scanf("%s", inputFile); /// strcpy(inputFile, "duom1.txt");

    Input = fopen(inputFile, "r");
    if(Input == NULL)
    {
        perror("There has been an error accessing the input file. Make sure it is created and try again: ");
        return -1;
    }

    printf("Please enter the desired output file name.\n");
    scanf("%s", outputFile); /// strcpy(outputFile,"rez.txt");

    Output = fopen(outputFile, "w");
    if(Output == NULL)
    {
        perror("There has been an error creating the output file: ");
        return -1;
    }

    char line[256];
    while(fgets(line, 256, Input) != NULL)
    {
        findSatisfyingWords(line, Output);
    }

    fclose(Output);
    fclose(Input);

    printf("\nThe program has successfully completed its task. The results are located in the working directory file, named %s.\n", outputFile);
    return 0;
}
