// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// set the no_of_buckets to 17576 which is 26^3
const unsigned int N = 17576;

// size of dictionary to be loaded
int size_of_dict = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash the word to get a hash value
    int hval = hash(word);
    // pont to the linked list that is at the index of the hash value
    node *n = table[hval];
    // while n is not NULL visit each node of the linked list
    while (n != NULL)
    {
        // check if the word is in the dict
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        // check the next word
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // get index of each char in the word(0-25) by subtracting 65("a") from the char, then get sum of chars in the word and then return sum divided by no_of_buckets.
    long word_sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        // word_sum += toupper(word[i]) - 97;
        word_sum += tolower(word[i]) - 65;
    }
    return word_sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dkctionary file
    FILE *dict = fopen(dictionary, "r");
    // check if dict can't be opened
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    // length of the word to be stored
    char dict_word[LENGTH + 1];
    while (fscanf(dict, "%s", dict_word) != EOF)
    {
        // create a node for each dict_word
        node *n = malloc(sizeof(node));
        // check for malloc if no storage or other
        if (n == NULL)
        {
            return false;
        }
        // copy word into node
        strcpy(n->word, dict_word);
        // call hash fun to get hash value
        int hval = hash(dict_word);
        // insert node into hash table
        n->next = table[hval];
        table[hval] = n;
        size_of_dict++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //  size_of_dict will return a value if a dict is loaded else 0
    return size_of_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // for each node in a linked list of the hash table free memoryt
    for (int i = 0; i < N; i++)
    {
        // pinting n to the first node(head)
        node *n = table[i];
        // for each linked list free if n != NULL.
        while (n != NULL)
        {
            // Make temp pionter to piont to the node to be freed
            node *temp = n;
            // Point n to next node
            n = n->next;
            // free temp
            free(temp);
        }
        // check if every node is freed if so return true else false
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
