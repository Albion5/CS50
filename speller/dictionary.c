// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
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
const unsigned int N = 150;

// Hash table
node *table[N];

unsigned int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *head = table[hash(word)];
    while (head != NULL)
    {
        if (strcasecmp(head->word, word) == 0)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int value = 0;
    unsigned int key_len = strlen(word);
    for (int i = 0; i < key_len; i++)
    {
        value = value + 37 * tolower(word[i]);
    }
    value = value % N;
    return value;
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char string[LENGTH + 1];
    FILE *dict;
    dict = fopen(dictionary, "r");
    if (dict != NULL)
    {
        unsigned int hash_index;
        while (fscanf(dict, "%s", string) != EOF)
        {
            hash_index = hash(string);
            node *head = table[hash_index];
            node *new = malloc(sizeof(node));
            if (new == NULL)
            {
                unload();
                fclose(dict);
                return false;
            }
            strcpy(new->word, string);

            if (head == NULL)
            {
                new->next = NULL;
                table[hash_index] = new;
            }
            else
            {
                new->next = table[hash_index];
                table[hash_index] = new;
            }

            // new->next = head;
            // head = new;

            dict_size++;
        }
        fclose(dict);
    }
    else
    {
        return false;
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // unsigned int count = 0;
    // node *head;
    // for (int i = 0; i < N; i++)
    // {
    //     head = table[i];
    //     while (head != NULL)
    //     {
    //         count++;
    //         head = head->next;
    //     }
    // }
    // return count;
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *head, *trav;
    for (int i = 0; i < N; i++)
    {
        head = table[i];
        while (head != NULL)
        {
            trav = head;
            head = head->next;
            free(trav);
        }
        if (head == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
