// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *head = table[hash(word)];
    node *trav = head->next;
    while (trav != NULL)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        };
        trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char string[LENGTH + 1];
    FILE *dict;
    dict = fopen(dictionary);
    if (dict != NULL)
    {
        while (fscanf(dict, "%s", string) != EOF)
        {
            node *head = table[hash(string)];
            node *new = malloc(sizeof(node));
            if (new == NULL)
            {
                return false;
            }
            new->next = head->next;
            head->next = new;
            strcpy(new->word, string);
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int count = 0;
    node *head, *trav;
    for (int i = 0; i < N; i++)
    {
        head = table[i];
        trav = head;
        while (trav != NULL)
        {
            count++;
            trav = trav->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *head, *trav;
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        head = table[i];
        while (head != NULL)
        {
            trav = head;
            head = trav->next;
            free(trav);
            count++;
        }
    }
    if (count == size())
    {
        return true;
    }
    return false;
}
