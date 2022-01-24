#include <cs50.h>
#include <stdio.h>

// function prototype
void mario_more();

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

    mario_more(n);

    return 0;
}

void mario_more(int n)
{
    for (int i = 0; i < n; i++)
    {
        // Loop to add spaces to the left mario
        for (int k = n - i; k > 1; k--)
        {
            printf(" ");
        }
        // loop to add  the left mario #
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // loop to add 2 spaces after the #
        for (int z = 0; z < 2; z++)
        {
            printf(" ");
        }
        // loop to print the right mario
        for (int y = 0; y <= i; y++)
        {
            printf("#");
        }
        printf("\n");
    }
}