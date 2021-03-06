#include "main.h"


void fillListFunc(struct Element **headPtr)
{
    FILE *Input;

    char fileName[200];
    inputCheck(stdin, &Input, fileName);
    
    printf("The input file name is valid and has been accessed successfully.\n");

    fillList(&Input, headPtr);

    fclose(Input);
}

int fillList(FILE **Input, struct Element **headPtr)
{
    int fileEmptyFlag = fileEmptyCheck(*Input);

    if(fileEmptyFlag == 1) /// if after the previous function the value of fileEmptyFlag is changed, the list won't be appended.
    {
        printf("The provided data file is empty.\n");
        return 0;
    }

    while(!feof(*Input))
    {
        int value = 0;
        int breakFlag = 0;
        int errorFlag = 0;
        int eofFlag = 0;

        readFromFile(Input, &value, &breakFlag, &errorFlag, &eofFlag);

        /// processing flags
        if(errorFlag)
        {
            printf("\nOne of the entities in the file had invalid data. While all of the elements before that entity have been read, the input has been stopped upon reaching the wrong format data.\nPlease make sure every number is separated with spaces or enter symbols.\n");
            return 1;
        }

        if(eofFlag)
        {
            printf("The list has been successfully read from the file.\n");
            return 1;
        }

        pushElement(headPtr, value);

        if(breakFlag) 
        {
            printf("The list has been successfully read from the file.\n");
            break;
        }
    }
    return 1;
}

void pushElement(struct Element **headPtr, int elementToAdd)
{
    struct Element *newElement = (struct Element*)malloc(sizeof(struct Element)); /// new memory allocation is used for the new element of the list.

    newElement->data = elementToAdd;
    newElement->next = *headPtr;

    *headPtr = newElement; /// the element is pushed to the front and the previous head element becomes its next.
}

void printElements(struct Element *startingElement)
{
    if(startingElement == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    printf("Currently the list is as follows:\n");

    while(startingElement != NULL) /// printing all the elements from the starting element.
    {
        printf("%d ", startingElement->data);
        startingElement = startingElement->next;
    }
}

void deleteProcess(struct Element **headPtr)
{
    int valueToDelete;

    deleteInput(stdin, &valueToDelete);

    deleteElement(headPtr, valueToDelete);

}

void deleteElement(struct Element **headPtr, int elementToDelete)
{
    struct Element *currentElement = *headPtr;
    struct Element *previousElement;

    if(currentElement != NULL && currentElement->data == elementToDelete) /// checking if the head element is the one to be deleted to determine if change of the argument is necessary
    {
        *headPtr = currentElement->next; 
        free(currentElement);
        printf("The element %d was deleted from the list.\n", elementToDelete);
        return;
    }

    while(currentElement != NULL && currentElement->data != elementToDelete) /// iterating through the elements to find if their data matches the value to delete. 
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
    }

    if(currentElement == NULL)
    {
        printf("The element was not found in the linked list.\n");
        return;
    }

    previousElement->next = currentElement->next;

    free(currentElement);

    printf("The element %d was deleted from the list.\n", elementToDelete);
}

void deleteWholeList(struct Element **headPtr)
{
    if(*headPtr == NULL)
    {
        printf("The list is already empty.\n");
        return;
    }

    struct Element *currentElement = *headPtr;
    struct Element *temp;

    while(currentElement != NULL)
    {
        temp = currentElement->next;
        free(currentElement);
        currentElement = temp;
    }

    *headPtr = NULL; /// changing the head value to NULL - the primary state.
    printf("The whole list has been successfully deleted.\n");
}