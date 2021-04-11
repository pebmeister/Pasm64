#pragma warning(disable: 4996)

// ***********************************************************************
// Assembly         : 
// Author           : Paul
// Created          : 11-27-2015
//
// Last Modified By : Paul
// Last Modified On : 11-27-2015
// ***********************************************************************

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "str.h"
#include "error.h"

#define INITIAL_SIZE    (10243)
#define GROWTH_FACTOR   (2)
#define MAX_LOAD_FACTOR (.80)

/// <summary>
/// dictionary initialization code used in both DictCreate and grow.
/// </summary>
/// <param name="size">The size.</param>
/// <param name="elementSize">Size of the element.</param>
/// <returns>Dictionary.</returns>
DictionaryPtr internalDictCreate(int size, int elementSize)
{
    DictionaryPtr dictionary = (DictionaryPtr) malloc(sizeof(*dictionary));
    const char* module = "internalDictCreate";

    if (dictionary == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    memset(dictionary, 0, sizeof(*dictionary));
    dictionary->size = size;
    dictionary->elementSize = elementSize;

    dictionary->table = (elementPtr*) malloc(sizeof(elementPtr) * dictionary->size);
    if (dictionary->table == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    memset(dictionary->table, 0, sizeof(elementPtr) * dictionary->size);

    return dictionary;
}

/// <summary>
/// Dictionary creation.
/// </summary>
/// <returns>Dict.</returns>
DictionaryPtr DictCreate(int elementSize)
{
    return internalDictCreate(INITIAL_SIZE, elementSize);
}

/// <summary>
/// Dictionary destroy.
/// </summary>
/// <param name="d">The d.</param>
void DictDestroy(DictionaryPtr d)
{
    if (d == NULL) return;

    elementPtr next;

    for (int index = 0; index < d->size; index++) 
    {
        for (elementPtr element = d->table[index]; element != 0; element = next) 
        {
            next = element->next;

            free(element->key);
            free(element->value);
            free(element);
        }
    }

    free(d->table);
    free(d);
}

/// <summary>
/// Hash_function
/// </summary>
/// <param name="key">The string.</param>
/// <returns>unsigned long.</returns>
static unsigned long hash_function(const char *key)
{
    register unsigned long hash = 0, index = 0;

    for (; key[index]; ++index)
    {
        hash += ((index % 2) ? key[index] : toupper(key[index]));
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

/// <summary>
/// Grows the specified dictionary returns new dictionary.
/// </summary>
/// <param name="d">The d.</param>
static DictionaryPtr grow(DictionaryPtr d)
{
    const char* module = "grow";

    DictionaryPtr d2 = internalDictCreate(d->size * GROWTH_FACTOR, d->elementSize);
    if (d2 == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    d2->collisions = d->collisions;
    for (int index = 0; index < d->size; index++) 
    {
        for (elementPtr element = d->table[index]; element != 0; element = element->next) 
        {
            /* note: this recopies everything */
            /* a more efficient implementation would
             * to avoid this problem */
            DictInsert(&d2, element->key, element->value);
        }
    }

    DictDestroy(d);
    return d2;
}

/// <summary>
/// insert a new key-value pair into an existing dictionary.
/// dictionary may grow
/// </summary>
/// <param name="dd">The address of dictionary pointer.</param>
/// <param name="key">The key.</param>
/// <param name="value">The value.</param>
void* DictInsert(DictionaryPtr *dd, const char *key, void *value)
{
    // ReSharper disable once CppLocalVariableMayBeConst
    DictionaryPtr d = *dd;
    const char* module = "DictInsert";

    elementPtr e = (elementPtr)malloc(sizeof(*e));
    if (e == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    memset(e, 0, sizeof(*e));

    e->key = Strlower(key);
    if (e->key == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    e->value = malloc(d->elementSize);
    if (e->value == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    memcpy(e->value, value, d->elementSize);

    const unsigned long h = hash_function(e->key) % d->size;
    e->next = d->table[h];
    if (e->next) 
        d->collisions++;

    d->table[h] = e;
    d->numberElements++;

    /* grow table if there is not enough room */
    if ((double)(d->numberElements) >= (d->size * MAX_LOAD_FACTOR))
    {
        *dd = grow(d);        
        return DictSearch(*dd, key);
    }
    return e->value;
}

/// <summary>
/// return the most recently inserted value associated with a key.
/// or NULL if no matching key is present
/// </summary>
/// <param name="d">The d.</param>
/// <param name="key">The key.</param>
/// <returns>void *.</returns>
void * DictSearch(DictionaryPtr d, const char *key)
{
    const char* module = "DictSearch";

    char* lowerKey = Strlower(key);
    if (lowerKey == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    const unsigned long h = hash_function(lowerKey) % d->size;
    for (elementPtr e = d->table[h]; e != 0; e = e->next)
    {
        if (!strcmp(e->key, lowerKey)) 
        {
            free(lowerKey);
            /* got it */
            return e->value;
        }
    }
    free(lowerKey);
    return NULL;
}

/// <summary>
/// delete the most recently inserted record with the given key
/// if there is no such record, has no effect
/// </summary>
/// <param name="d">The dictionary.</param>
/// <param name="key">The key.</param>
void DictDelete(DictionaryPtr d, const char *key)
{
    const char* module = "DictDelete";
    char* lowerKey = Strlower(key);

    if (lowerKey == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return;
    }

    const unsigned long h = hash_function(lowerKey) % d->size;

    for (elementPtr* prev = &(d->table[h]); *prev != 0; prev = &((*prev)->next)) 
    {
        if (!strcmp((*prev)->key, lowerKey)) 
        {
            /* got it */
            // ReSharper disable once CppLocalVariableMayBeConst
            elementPtr e = *prev;
            *prev = e->next;

            free(e->key);
            free(e->value);
            free(e);
            free(lowerKey);
            return;
        }
    }
    free(lowerKey);
}
