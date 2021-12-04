#ifndef MAIN_H /// including a library
#define MAIN_H

#include "main.h"

#endif



void launchUserInterface(struct Element **head)
{
    int value, printMenu = 0; 

    while(1)
    {
        printMenu = (printMenu + 1) % 5; /// to not spam the menu, every fifth wrong request will have the menu printed.
        if(printMenu == 1)
        {
            printMenuText();
        }

        int continueFlag = 0;
        validateMenuInput(&continueFlag, &value);

        if(continueFlag == 0) /// if a right value is found, the validating process ends.
            break; 
    }

    switch(value) /// menu logical execution
    {
    case 0:
    {
        fillList(head);
        break;
    }
    case 1:
    {
        printElements(*head);
        break;
    }
    case 2:
    {
        deleteProcess(head);
        break;
    }
    case 3:
    {
        deleteWholeList(head);
        break;
    }
    case 4:
    {
        printf("The program has been successfully terminated.");
        exit(0);
    }
    default:
    {
        assert(0); /// if the values were correct, there program should not receive any other value than described above.
    }
    }

    launchUserInterface(head); /// the function is recursive
    assert(0);
}

void printMenuText() /// prints the user interface menu.
{
    puts("");
    puts("***********************************************************************");
    puts("|                         User interface menu                         |");
    puts("***********************************************************************");
    puts("| 0. Enter the file name and append the list with data from that file.|");
    puts("| 1. Print the linked-list in the computer memory.                    |");
    puts("| 2. Delete an element by value. The value is entered by the user.    |");
    puts("| 3. Delete the whole linked-list completely.                         |");
    puts("| 4. Exit the program.                                                |");
    puts("|                        Enter the number only!                       |");
    puts("***********************************************************************");
    printf("Your input: ");
}
