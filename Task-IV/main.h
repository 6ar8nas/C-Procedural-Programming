/// All the documentation for the functions is provided in the ReadMe.txt file in the folder.
/// Author: Šarūnas Griškus

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Element
{
    int data;
    struct Element *next;
};

void launchUserInterface(struct Element **head);
void printMenuText();
void validateMenuInput(FILE *Input, int *continueFlag, int *value);
void fillListFunc(struct Element **headPtr);
int fileEmptyCheck(FILE *Input);
void inputCheck(FILE *Stream, FILE **Input, char fileName[]);
void readFromFile(FILE **Input, int *value, int *breakFlag, int *errorFlag, int *eofFlag);
void pushElement(struct Element **headPtr, int elementToAdd);
void printElements(struct Element *startingElement);
void deleteProcess(struct Element **headPtr);
void deleteInput(FILE *Stream, int *valueToDelete);
void deleteElement(struct Element **head, int elementToDelete);
void deleteWholeList(struct Element **headPtr);
int fillList(FILE **Input, struct Element **headPtr);

#endif
