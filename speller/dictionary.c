#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// ammoun of (buckets) in the table hash
const unsigned int N = 26;

// Table hash (initialised as NULL)
node *table[N] = {NULL};

// global variable to count the loads words in the dictionary
unsigned int dictionary_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to obtain the index (ensure hash is case-insensitive)
    unsigned int index = hash(word);

    // Traverse the linked list in the hash table bucket at that index
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // Compare case-insensitively using strcasecmp
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    // If no match is found, return false
    return false;
}

// Hashes word to a number using the djb2 algorithm
unsigned int hash(const char *word)
{
    // Initialize with one value fixed (5381 is common in djb2)
    unsigned int hash = 5381;

    // map the word, becoming each letter to lowercase so that the comparison be insensitive to
    // uppers/lowers
    for (int i = 0; word[i] != '\0'; i++)
    {
        // hash = hash * 33 + tolower(letter)
        hash = ((hash << 5) + hash) + tolower(word[i]);
    }

    // return an index between 0 and N - 1
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the file of dictionary in read mode
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // buffer to store each word (it is assumed that don't exceeds LENGTH)
    char word[LENGTH + 1];

    // read words of the file until each the final
    while (fscanf(file, "%s", word) != EOF)
    {

        // assign memory for an new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return 1;
        }

        // copy the word in the new node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // calculate the hash index for the word
        unsigned int index = hash(word);

        // append the new node at start of the linked list
        new_node->next = table[index];
        table[index] = new_node;

        // increment the counter of word
        dictionary_count++;
    }

    // close the file of the dictionary
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    // map each tray of the hash table
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        // while there nodes in the linked list of the tray
        while (cursor != NULL)
        {
            node *temp = cursor;   // keep the current node
            cursor = cursor->next; // advance to next node
            free(temp);            // free the current nod
        }
    }
    return true;
}
