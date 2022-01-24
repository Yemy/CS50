#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    int n = get_int("Height: ");
    draw(n);
}

void draw(int n)
{
    if (n <= 0)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
    draw(n-1);

}