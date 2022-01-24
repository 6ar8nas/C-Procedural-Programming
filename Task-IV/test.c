#include "main.h"
#include <assert.h>
#include <string.h>

void removeAllElementsTest(char *msg);
int countElements(struct Element *head);
void deleteElementTest(char *msg);
void fillListTest(char *msg);
void pushElementTest();
void deleteInputTest(FILE *InputStream);
void inputCheckTest(FILE *InputStream);
void validateMenuInputTest(FILE *InputStream1, FILE *InputStream2);
void fileEmptyCheckTest(FILE *EmptyFile, FILE *NotEmptyFile);

int main()
{
    /// Linked-list
    removeAllElementsTest("input/test1.txt");
    removeAllElementsTest("input/test2.txt");
    deleteElementTest("input/test1.txt");
    deleteElementTest("input/test2.txt");
    pushElementTest();
    fillListTest("input/test1.txt");
    fillListTest("input/test2.txt");


    /// Input
    FILE *InputInt;
    InputInt = fopen("input/testinput1.txt", "r");
    assert(InputInt != NULL);
    
    FILE *InputStr;
    InputStr = fopen("input/testinput2.txt", "r");
    assert(InputStr != NULL);

    FILE *InputEmpty;
    InputEmpty = fopen("input/testinput3.txt", "r");
    assert(InputEmpty != NULL);

    FILE *InputInt2;
    InputInt2 = fopen("input/testinput4.txt", "r");
    assert(InputInt2 != NULL);

    FILE *InputInt3;
    InputInt3 = fopen("input/testinput5.txt", "r");
    assert(InputInt3 != NULL);

    deleteInputTest(InputInt);
    inputCheckTest(InputStr);
    validateMenuInputTest(InputInt2, InputInt3);
    fileEmptyCheckTest(InputEmpty, InputInt);


    system("clear");
    printf("All tests have passed successfully.\n");
    fclose(InputInt);
    fclose(InputStr);
    fclose(InputEmpty);
    fclose(InputInt2);
    fclose(InputInt3);
    return 0;
}

void removeAllElementsTest(char *msg)
{
    struct Element *head = NULL;
    FILE *Input;
    Input = fopen(msg, "r");
    assert(Input != NULL);
    int emptyCheck = fillList(&Input, &head);
    if(emptyCheck == 0)
    {
        assert(head == NULL);
        deleteWholeList(&head);
        assert(head == NULL);
    }
    else
    {
        assert(head != NULL);
        deleteWholeList(&head);
        assert(head == NULL);
    }
    assert(countElements(head) == 0);
    fclose(Input);
}

void deleteElementTest(char *msg)
{
    struct Element *head = NULL;
    struct Element *prevHead = NULL;
    FILE *Input;
    Input = fopen(msg, "r");
    assert(Input != NULL);
    int emptyCheck = fillList(&Input, &head);
    prevHead = head;
    int elementCount = countElements(head);
    if(emptyCheck == 0)
    {
        assert(head == NULL);
        deleteElement(&head, 1);
        assert(head == NULL);
    }
    else
    {
        assert(head != NULL);
        deleteElement(&head, 3);
        deleteElement(&head, 5);
        assert(elementCount - 2 == countElements(head));
        assert(head != prevHead);
    }
    fclose(Input);

}

void fillListTest(char *msg)
{
    struct Element *head = NULL;
    struct Element *prevHead = head;
    FILE *Input;
    Input = fopen(msg, "r");
    assert(Input != NULL);
    int emptyCheck = fillList(&Input, &head);
    if(emptyCheck == 0)
    {
        assert(head == NULL);
        assert(countElements(head) == 0);
        assert(head == prevHead);
    }
    else
    {
        assert(head != NULL);
        assert(countElements(head) == 5);
        assert(head != prevHead);
    }
}

void pushElementTest()
{
    struct Element *head = NULL;
    struct Element *prevHead = NULL;
    pushElement(&head, 3);
    prevHead = head;
    assert(head != NULL);
    assert(head->data == 3);
    pushElement(&head, 2);
    assert(head != prevHead);
    assert(head->data == 2);
    assert(countElements(head) == 2);
}

int countElements(struct Element *head)
{
    if(head != NULL)
    {
        return 1 + countElements(head->next);
    }
    return 0;
}  

void deleteInputTest(FILE *InputStream)
{
    int value = 1;
    deleteInput(InputStream, &value);
    assert(value != 1 && value == -123);
}

void inputCheckTest(FILE *InputStream)
{
    FILE *Result = NULL;
    char fileName [200];
    inputCheck(InputStream, &Result, fileName);
    assert(Result != NULL);
    assert(strcmp(fileName, "input/duom.txt") == 0);
}

void validateMenuInputTest(FILE *InputStream1, FILE *InputStream2)
{
    int continueFlag = 0, value = 0;
    validateMenuInput(InputStream1, &continueFlag, &value);
    assert(continueFlag == 1);

    continueFlag = 0, value = 0;
    validateMenuInput(InputStream2, &continueFlag, &value);
    assert(value == 3 && continueFlag == 0);
}

void fileEmptyCheckTest(FILE *EmptyFile, FILE *NotEmptyFile)
{
    assert(fileEmptyCheck(EmptyFile) == 1);
    assert(fileEmptyCheck(NotEmptyFile) == 0);
}

void readFromFileTest()
{
    FILE *Input1, *Input2;
    Input1 = fopen("testfileinput1.txt", "r");
    Input2 = fopen("testfileinput2.txt", "r");
    assert(Input1 != NULL && Input2 != NULL);

    int value = 0;
    int breakFlag = 0;
    int errorFlag = 0;
    int eofFlag = 0;

    readFromFile(&Input1, &value, &breakFlag, &errorFlag, &eofFlag);
    assert(breakFlag == 0 && errorFlag == 0 && eofFlag == 0);

    value = 0, breakFlag = 0, errorFlag = 0, eofFlag = 0;
    readFromFile(&Input2, &value, &breakFlag, &errorFlag, &eofFlag);
    assert(eofFlag == 0 && errorFlag == 1 && breakFlag == 0);

    fclose(Input1);
    fclose(Input2);
}