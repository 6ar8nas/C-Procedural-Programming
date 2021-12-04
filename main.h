/// All the documentation for the functions is provided in the ReadMe.txt file in the folder.
/// Author: Šarūnas Griškus

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

struct Element
{
    int data;
    struct Element *next;
};

void launchUserInterface(struct Element **head);
void printMenuText();
void validateMenuInput(int *continueFlag, int *value);
void fillList(struct Element **headPtr);
void fileEmptyCheck(FILE *Input, int *fileEmptyFlag);
void inputCheck(FILE **Input);
void readFromFile(FILE **Input, int *value, int *breakFlag, int *errorFlag, int *eofFlag);
void pushElement(struct Element **headPtr, int elementToAdd);
void printElements(struct Element *startingElement);
void deleteProcess(struct Element **headPtr);
void deleteInput(int *valueToDelete);
void deleteElement(struct Element **head, int elementToDelete);
void deleteWholeList(struct Element **headPtr);