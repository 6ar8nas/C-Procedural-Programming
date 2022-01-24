/// The program was created by Sarunas Griskus. A linked list is created from the data in a file and the program is able to successfully discard the given element and, if there's no such element, warn the user with a message.
/// Task 4, variant 6

#include "main.h"

int main()
{
    printf("The program will create a linked list from the elements in an external file.\n");
    printf("It will be able to discard a given element or will print a message if there is no such element.\n\n");

    struct Element *head = NULL; 
    FILE *Input;

    launchUserInterface(&head);
    printf("The program has been successfully terminated.");

}
