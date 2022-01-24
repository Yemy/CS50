#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

long calculate_letters(char text[]);
long calculate_words(char text[]);
long calculate_sentences(char text[]);

int main(void)
{
    // get input text
    string text = get_string("Input Text: ");

    // run the functions
    long letters = calculate_letters(text);
    long words = calculate_words(text);
    long sentences = calculate_sentences(text);

    // printf("%ld%ld%ld", letters, words, sentences);
    // run the calculations
    float L = 0.0588 * (float) letters / words * 100;
    float S = 0.296 * (float) sentences / words * 100;
    float index = L - S - 15.8;
    int grade = round(index);

    // output
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// calculate the noof letters
long calculate_letters(char text[])
{
    long letters = 0;
    for (long i = 0; i < strlen(text); i++)
    {
        if ((64 < text[i] && text[i] < 91) || (96 < text[i] && text[i] < 123))
        {
            letters++;
        }
    }
    return letters;
}

// calculate the noof words
long calculate_words(char text[])
{
    long words = 1;
    for (long i = 0; i < strlen(text); i++)
    {
        if (text[i] == 32)
        {
            words++;
        
    }
    return words;
}

// calculate the noof sentences
long calculate_sentences(char text[])
{
    long sentences = 0;
    for (long i = 0; i < strlen(text); i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}