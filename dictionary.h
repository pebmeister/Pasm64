// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
//
// copyright (c) 2015 Paul Baxter
//
// Last Modified By : Paul
// Last Modified On : 11-29-2015
// ***********************************************************************

/// <summary>
/// element structure
/// </summary>
typedef struct element 
{
    /// <summary>
    /// The next
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
} element, *elementPtr;

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
    int numberElements;
    /// <summary>
    /// The element size
    /// </summary>
    int elementSize;
    /// <summary>
    /// The number of collisions
    /// </summary>
    int collisions;
    /// <summary>
    /// The table
    /// </summary>    
    struct element **table;
} dict, *DictionaryPtr; 

/* create a new empty dictionary */
DictionaryPtr DictCreate(int elementSize);

/* destroy a dictionary */
void DictDestroy(DictionaryPtr);

/*
   insert a new key-value pair into an existing dictionary
   the dictionary may expanded which why address of pointer is passed 
*/
void* DictInsert(DictionaryPtr*, const char *key, void *value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
void *DictSearch(DictionaryPtr, const char *key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void DictDelete(DictionaryPtr, const char *key);
