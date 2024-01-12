// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LENGTH 45

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 5;
node *table[5];

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Implement a proper hash function
    // You can use a simple hash function for now
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = hash * 31 + word[i];
    }
    return hash % N;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert word to lowercase
    char lowercaseWord[LENGTH + 1];
    strcpy(lowercaseWord, word);
    for (int i = 0; lowercaseWord[i] != '\0'; i++)
    {
        lowercaseWord[i] = tolower(lowercaseWord[i]);
    }

    unsigned int index = hash(lowercaseWord);

    // Traverse the linked list at the hash table index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, lowercaseWord) == 0)
        {
            return true; // Word found
        }
        cursor = cursor->next;
    }

    return false; // Word not found
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false; // Unable to open dictionary file
    }

    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];

    // Read words from dictionary and insert into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for the word
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            fclose(file);
            return false; // Memory allocation failed
        }
        strcpy(newNode->word, word);

        // Hash the word to get the index
        unsigned int index = hash(word);

        // Insert the new node at the beginning of the linked list
        newNode->next = table[index];
        table[index] = newNode;
    }

    fclose(file);
    return true; // Successfully loaded dictionary
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int wordCount = 0;

    // Traverse each linked list in the hash table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            wordCount++;
            cursor = cursor->next;
        }
    }

    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Traverse each linked list in the hash table and free memory
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true; // Successfully unloaded dictionary
}
