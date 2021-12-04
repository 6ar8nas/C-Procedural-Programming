Author, contacts: 
Šarūnas Griškus, Software Engineering, Vilnius University, Class of 2025.
github.com/6ar8nas, sgriskus2002@gmail.com

Version history:
v1.0 - 2021.12.05 - the whole program has been created.

Purpose:
The program has been created as a Software Engineering course part, completing Task 4 | Variant 6.

Content:
A linked list is created from the data in a file and the program is able to successfully discard the given element and, if there's no such element, warn the user with a message.

Technical limits:
Unknown. Recursion is used in the program, therefore memory may be limited.

Data-types used:

    For the individual elements of the linked list:

        Struct Element
        {
            int data;                       - used for storing the data for the element
            struct Element *next;           - used for the reference of the following element of the linked-list. Should be NULL if no further element is in the program. 
        }
    
Functions used (all located in main.h):
    Note:
        All of the flags should have its value set to 0 before the function is used. If after the function it returns a value of 1, a proper effect should be imposed.

    workWithIO.o:

        void validateMenuInput(int *continueFlag, int *value) - the function validates the input from stdin stream at the Menu level of the program.
            Parameters: 
                continueFlag - This integer is used as a flag to determine if the input should be repeated (set to 1 if the input was invalid).
                value - a value that is the main focus of this function. It can only be an integer from 0 to 4 and is used as a part of the user interface/menu.
        
        void inputCheck(FILE **Input) - the function asks the user for input and then tries to open the Input file according to the given user input. 
            Parameters:
                Input - This is the pointer to a FILE object that identifies the stream where characters are read from.

        void fileEmptyCheck(FILE *Input, int *fileEmptyFlag) - checks if the Input stream is empty and changes a fileEmpty flag if it is true.
            Parameters:
                Input - This is the pointer to a FILE object that identifies the stream where characters are read from.
                fileEmptyFlag - a value that is used as a flag to determine if the stream is empty.
        
        void readFromFile(FILE **Input, int *value, int *breakFlag, int *errorFlag, int *eofFlag) - reads an element from the Input stream and sets flags according to its findings.
            Parameters:
                Input - This is the pointer to a FILE object that identifies the stream where characters are read from. Cannot be NULL.
                value - an integer value that is read from the Input stream. 
                breakFlag - a value that is used to determine if no more elements should be read after this one (therefore the received value should be also pushed to the list). 
                errorFlag - a value that is used to determine if an error has occured and any further reading should be stopped.
                eofFlag - a value that is used to determine if the file has ended.
            Note:
                The values may be only integers separated with whitespace symbols.
        
        void deleteInput(int *valueToDelete) - reads and validates an integer from stdin stream for the purpose of finding an element to be deleted.
            Parameters:
                valueToDelete - a value that the user enters to be deleted.
    
    workWithMenu.o:
        
        void launchUserInterface(struct Element **head) - launches the main User interface part of the program and uses logic to call other functions according to the user input.
            Parameters:
                head - a pointer to the head element of the linked list.

        void printMenuText() - prints the menu.

    workWithList.o:

        void fillList(struct Element **headPtr) - fills the list from the file that the user has entered. The data in the file should contain integers only separated by whitespace symbols.
            Parameters:
                headPtr - a pointer to the head element of the linked-list.

        void pushElement(struct Element **headPtr, int elementToAdd) - adds a value to the front of the linked-list.
            Parameters:
                headPtr - a pointer to the head element of the linked-list.
                elementToAdd - a value that should be added to the front of the linked-list.

        void printElements(struct Element *startingElement) - prints all of the elements of the linked-list starting with the given.
            Parameters:
                startingElement - a destination of the pointer to the first element that should be printed from the linked-list until the reference to the next element is NULL.

        void deleteProcess(struct Element **headPtr) - starts the deletion process of one of the values of the list involving the input of the element and its deletion.
            Parameters:
                headPtr - a pointer to the head element of the linked-list.

        void deleteElement(struct Element **headPtr, int elementToDelete) - deletes an element with the given value from the linked-list. If such value is not found, a message is printed.
            Parameters:
                headPtr - a pointer to the head element of the linked-list.

        void deleteWholeList(struct Element **headPtr) - deletes the whole linked-list from the memory.
            Parameters:
                headPtr - a pointer to the head element of the linked-list.



        

        


        







