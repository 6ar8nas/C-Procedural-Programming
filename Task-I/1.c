#include <stdio.h>
int main()
{
    int current_number = 1, sum_odd_total = 0;
    printf("Program loaded.\n");
    printf("The program will take a sequence of integers and output the amount of numbers with odd number of digits. To end the the input, please enter a 0.\n");
    printf("Please start entering the integers of the sequence until specified differently.\n\n");
    do
    {
        if((scanf("%d", &current_number) == 1) && (getchar() == '\n'))
        {
            int how_many_digits = 0, temp_number_holder = current_number;
            do
            {
                ++how_many_digits;
                temp_number_holder /= 10;
            }
            while (temp_number_holder);

            if(how_many_digits % 2)
                ++sum_odd_total;
        }
        else
        {
            while(getchar() != '\n')
                ;
            printf("Error. Your input was faulty. The sequence can only consist of integers. Enter a valid argument.\n");
        }
    }
    while (current_number);

    printf ("\nThere is a total of %d %s with an odd sum of digits in the sequence.\nProgram execution is complete.\n",
            sum_odd_total, (sum_odd_total == 1) ? "integer" : "integers");
    return 0;
}
