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
const unsigned int N = 300;

// Hash table
node *table[N];

unsigned int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get hash index in the hash table for the word
    // Set cursor to the head of a linked list at hash index
    node *trav = table[hash(word)];
    // Keep searching for a word in a linked list
    while (trav != NULL)
    {
        // If found return true
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
        // Set cursor to the next element in the list
        head = trav->next;
    }
    // If not found return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Calculate the sum of all the letters in a word converted to lower case
    unsigned int hash_value = 0;
    unsigned int key_len = strlen(word);
    for (int i = 0; i < key_len; i++)
    {
        hash_value = hash_value + tolower(word[i]);
    }
    // Make sure hash_value is valid and less than the number of buckets in the hash table
    return hash_value % N;
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Temporary array for storing a word in a dictionary
    char string[LENGTH + 1];
    // Open dictionary
    FILE *dict;
    dict = fopen(dictionary, "r");
    if (dict != NULL)
    {
        // If opened
        unsigned int hash_index;
        // Keep reading words in temporary array untill there's EOF
        while (fscanf(dict, "%s", string) != EOF)
        {
            // Get hash_index for storing a word in the table
            hash_index = hash(string);
            // Get the head of a linked list at hash index in the table
            node *head = table[hash_index];
            // Allocate memory for a new node where word will be stored
            node *new = malloc(sizeof(node));
            if (new == NULL)
            {
                // If malloc fales
                // Free everything that's been loaded into memory, close the dictionary and return false
                unload();
                fclose(dict);
                return false;
            }
            // If malloc was successful copy word from temporary array to new node
            strcpy(new->word, string);

            // If there's nothing yet in the linked list
            if (head == NULL)
            {
                // New node points to NULL and becomes new head
                new->next = NULL;
                table[hash_index] = new;
            }
            else
            {
                // New node points to where head is pointing
                new->next = table[hash_index];
                // New node becomes new head
                table[hash_index] = new;
            }

            // new->next = head;
            // head = new;
            // Increase the number of words loaded into memory
            dict_size++;
        }
        // Close dictionary after loading all of the words
        fclose(dict);
    }
    else
    {
        // If dictionary couldn't be opened return false
        return false;
    }
    // If all was successful return true
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
    // Global variable that changes its value during loading the dictionary into memory
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Create head pointer and a temporary pointer
    node *head, *trav;
    // For each hash value in the hash table
    for (int i = 0; i < N; i++)
    {
        // Get the head of a linked list
        head = table[i];
        while (head != NULL)
        {
            // Save old head to a temporary pointer
            trav = head;
            // Set new head to the next elemet of the linked list
            head = head->next;
            // Free old head
            free(trav);
        }
        if (head == NULL && i == N - 1)
        {
            // If all of the elements in the hash table have been freed return true
            return true;
        }
    }
    // If something went wrong return false
    return false;
}
