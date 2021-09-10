// Implements a dictionary's functionality

#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Keeping track of size
int sizeWords = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)]; // set cursor to the table index based on hashcode

    // for each linked list in table index, compare strings
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
// simplified version of hash function. 
// I've experimented with first letter, second letter, all letter hashcodes
// most efficient solution was to use an already build hash function 
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dectionary file to read
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }

    // create buffer to store words from dictionary
    char dictWord[LENGTH + 1];

    // scan each word from the dictionary until end of file (EOF)
    while (fscanf(dict, "%s", dictWord) != EOF)
    {
        // allocate memory for node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Could not allocate memory node.\n");
            unload();
            return false;
        }

        strcpy(n->word, dictWord); // copy from buffer string to the string in node
        unsigned int hashcode = hash(n->word); // get hashcode of word
        n->next = table[hashcode]; // set nodes next pointer to the value of the table index hashcode
        table[hashcode] = n; // set table index hashcode to point to the newly created node
        sizeWords += 1; // increment to track number of words added
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return sizeWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // iterate over each index in the table to free allocated linked lists
    for (int i = 0; i < N; i++)
    {
        // set two pointer to move through the linked list and delete each item
        node *cursor = table[i];
        node *tmp = table[i];

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
