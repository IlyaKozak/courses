// Implements a dictionary's functionality

#include <stdbool.h>


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Node definition
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Hast table
node *hash_table[TABLE_SIZE];

// Word count
unsigned int word_count = 0;

// Hash function "djb2". Source: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int len = strlen(word);
    char copy[len + 1];
    copy[len] = '\0';

    // Copy of a word for hashing
    for (int i = 0; i < len; i++)
    {
        copy[i] = tolower(word[i]);
    }

    int index = hash(copy) % TABLE_SIZE;
    node *trav = hash_table[index];

    while (trav != NULL)
    {
        if (strcmp(copy, trav -> word) == 0)
        {
            return true;
        }
        trav = trav -> next;
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opening the dictionary
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];
    int limit = LENGTH + 2;

    // Reads a line (word) from the dictionary. It stops when either (limit - 1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
    while (fgets(buffer, limit, fp) != NULL)
    {
        // Remove '\n' character
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        int index = hash(buffer) % TABLE_SIZE;

        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(fp);
            return false;
        }

        strcpy(new_node -> word, buffer);
        new_node -> next = hash_table[index];

        hash_table[index] = new_node;
        word_count++;
    }

    fclose(fp);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        node *next = hash_table[i];
        while (next != NULL)
        {
            node *tmp = next;
            next = next -> next;
            free(tmp);
        }
    }
    return true;
}
