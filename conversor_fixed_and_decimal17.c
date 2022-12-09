#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double decimal_number = 0.0;
char binary_number[] = "11111111111111111"; 

int menu()
{
    int option_selected;
    int valid = 0;
    
    while(!valid)
    {
        printf("Menu: \n");
        printf("1. Conversion decimal to fixed point 17b. \n");
        printf("2. Conversion fixed point 17b to decimal. \n");
        printf("3. Exit \n");

        printf("Select one option: ");
        scanf("%d", &option_selected);

        if (option_selected == 0 || option_selected > 3)
        {
            printf("Select a valid menu option \n");
            printf("\n");
        }
        else
        {
            printf("You selected: option %d \n", option_selected);
            printf("\n");
            valid = 1;
        }
    }

    return option_selected;
}

void info_request(int option)
{
    if (option == 1) // decimal to fixed point
    {   
        printf("Enter decimal number to convert to fixed point: ");
        scanf("%lf", &decimal_number);
        printf("Entered decimal number: %f \n", decimal_number);
    }
    else if (option == 2) // fixed point to decimal
    {
        printf("Enter fixed point number to convert to decimal: ");
        scanf("%s", &binary_number);
        printf("Entered fixed point: %s \n", binary_number);
    }
    else
    {
        // do nothing
    }
}

void conversions(int option)
{
    if (option == 1) // decimal to fixed point
    {   
        printf("Go to convert dec to bin \n");
        unsigned int fixed_number_1 = 0;

        if (decimal_number < 0.0) // first check sign
        {
            binary_number[0] = '1'; // negative
        }
        else
        {   
            binary_number[0] = '0'; // positive
        }

        fixed_number_1 = abs(round(decimal_number * (1 << 8))); // entire number
        
        int count_1 = 16;
        unsigned int remain_number = fixed_number_1;
        int modulus = 0;
        while( count_1 > 0 )
        {
            modulus = remain_number % 2;

            if (modulus != 0)
            {
                binary_number[count_1] = '1';
            }
            else
            {
                binary_number[count_1] = '0';
            }

            remain_number = round(remain_number/2); // updates number for division   
            count_1--;         
        }
    }

    else if (option == 2) // fixed point to decimal
    {
        printf("Go to convert bin to dec \n");

        unsigned int fixed_number_2 = 0;

        // pass fixed number in string to an int representation for easily operations
        int count = 16;
        while( count > 0 )
        {
            if ( binary_number[count] == '1' )
            {
                fixed_number_2 = fixed_number_2 + (1 << 16-count);
            }
            count--;
        }

        decimal_number = (double)fixed_number_2 / (double)(1 << 8);

        if (binary_number[0] == '1')
        {
            decimal_number = -decimal_number;
        }
    }
    else
    {
        // do nothing
    }
}

void main()
{
    printf("Hello, this program do conversions \n");
    int selection = menu();

    while (selection != 3)
    {
        info_request(selection);
        conversions(selection);
        
        // finally, prints results
        printf("\n");
        printf("------------------------------------------ \n");
        printf("Decimal number %f = ", decimal_number);
        printf("17'b%c_", binary_number[0]);
        for(int i = 1; i<=8; i++) 
        {
            printf("%c", binary_number[i]);
        }
        printf("_");
        for(int i = 9; i<=17; i++) 
        {
            printf("%c", binary_number[i]);
        }
        printf(" Fixed point number \n");
        printf("------------------------------------------ \n");
        printf("\n");

        selection = menu();
    }
    
    // just exit the program
}
