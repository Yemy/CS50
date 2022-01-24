#include <cs50.h>
#include <stdio.h>

// main
int main()
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while
    (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        // Loop to add spaces  mario
        for (int k = n - i; k > 1; k--)
        {
            printf(" ");
        }
        // loop to add  the  mario #
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}

