#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // prompts the user to enter his name
    string name = get_string("What's your name? ");

    // greets the user with his name
    printf("hello, %s\n", name);
}
