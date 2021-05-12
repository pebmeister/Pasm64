// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
//
// ***********************************************************************

/// <summary>
/// element structure
/// </summary>
#pragma once
typedef struct element 
{
    /// <summary>
    /// The next element
    /// </summary>
    struct element *next;
    /// <summary>
    /// The key
    /// </summary>
    char *key;
    /// <summary>
    /// The value
    /// </summary>
    void *value;
} Element, *ElementPtr;

/// <summary>
/// dict struct
/// </summary>
typedef struct dict 
{
    /// <summary>
    /// size of the pointer table
    /// </summary>
    int size;
    /// <summary>
    /// The number elements stored
    /// </summary>
    int number_elements;
    /// <summary>
    /// The element size
    /// </summary>
    int element_size;
    /// <summary>
    /// The number of collisions
    /// </summary>
    int collisions;
    /// <summary>
    /// The table
    /// </summary>    
    struct element **table;
} Dict, *DictionaryPtr; 

/* create a new empty dictionary */
extern DictionaryPtr DictCreate(int elementSize);

/* destroy a dictionary */
extern void DictDestroy(DictionaryPtr);

/*
   insert a new key-value pair into an existing dictionary
   the dictionary may expanded which why address of pointer is passed 
*/
extern void* DictInsert(DictionaryPtr*, char *key, void *value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
extern void *DictSearch(DictionaryPtr, const char *key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
extern void DictDelete(DictionaryPtr, const char *key);
