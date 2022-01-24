#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    string key = argv[1];
    // printf("using atoi\n", atoi("30"));
    // check if there is only 1 CLI argument
    if (argc != 2)
    {
        printf("Missing Correct Comand Line Argument!\n");
        return 1;
    }

    // check if every char is a digit
    if (only_digits(key))
    {
        // printf("the key is %s \n", key);
        // convert argv[1] to int
        long secret = atoi(argv[1]);
        // prompt user to enter plain text
        string plainText = get_string("Input Plain Text:  ");
        // for each char in the plain text rotate char  if it's a letter
        // printf("Plain Text:  %s\n", plainText);
        // string cipherText = "";
        printf("ciphertext: ");
        for (int j = 0; j < strlen(plainText); j++)
        {
            char cipher = rotate(plainText[j], secret);
            printf("%c", cipher);
            // cipherText[j] = cipher;
        }
        // printf("Cipher Text: %s\n", cipherText);
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
}
// finction to check if the key is digit only
bool only_digits(string s)
{
    int count = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            count++;
        }
    }
    if (count == strlen(s))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// function to rotate the plain text by the given key
char rotate(char c, int n)
{
    int index = 0, shifted = 0;
    char done = 0;
    // to check if the char is an alphabet
    if (isalpha(c))
    {
        // check if the char is in upper case
        if (isupper(c))
        {
            // printf("%i\n", c);
            index = (int) c - 65;
            shifted = (index + n) % 26;
            shifted += 65;
            // printf("%i\n", shifted);
            done = (char) shifted;
            // printf("%c\n", done);
        }
        // check if the char is a lower case
        else if (islower(c))
        {
            // printf("%i\n", c);
            index = (int) c - 97;
            shifted = (index + n) % 26;
            shifted += 97;
            // printf("%i\n", shifted);
            done = (char) shifted;
            // printf("%c\n", done);
        }
        return done;
    }
    // if the char is not an alphabet then return itself
    else
    {
        return c;
    }
}
