/// The program was created by Sarunas Griskus. A linked list is created from the data in a file and the program is able to successfully discard the given element and, if there's no such element, warn the user with a message.
/// Task 4, variant 6

#ifndef MAIN_H /// including a library

#define MAIN_H
#include "main.h"

#endif


int main()
{
    printf("The program will create a linked list from the elements in an external file.\n");
    printf("It will be able to discard a given element or will print a message if there is no such element.\n\n");

    struct Element *head = NULL; 

    launchUserInterface(&head);

    assert(0);  /// the program should never reach this point, as the function above only ends by reaching exit() command.
}
