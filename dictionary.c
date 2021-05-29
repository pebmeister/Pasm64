// ReSharper disable CppClangTidyClangDiagnosticExtraSemiStmt
#pragma warning(disable: 4996)

// ***********************************************************************
// Assembly         : 
// Author           : Paul
// Created          : 11-27-2015
// ***********************************************************************

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#include "str.h"
#include "error.h"
#include "mem.h"

#define INITIAL_SIZE    (50 * 1024)
#define GROWTH_FACTOR   (2)
#define MAX_LOAD_FACTOR (.80)

/// <summary>
/// dictionary initialization code used in both DictCreate and grow.
/// </summary>
/// <param name="size">The size.</param>
/// <param name="elementSize">Size of the element.</param>
/// <returns>Dictionary.</returns>
DictionaryPtr InternalDictCreate(const int size, const int elementSize)
{
    DictionaryPtr dictionary = (DictionaryPtr)ALLOCATE(sizeof(*dictionary));
    const char* module = "InternalDictCreate";

    if (dictionary == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }

    memset(dictionary, 0, sizeof(*dictionary));
    dictionary->size = size;
    dictionary->element_size = elementSize;

    dictionary->table = (ElementPtr*)ALLOCATE(sizeof(ElementPtr) * dictionary->size);
    if (dictionary->table == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    memset(dictionary->table, 0, sizeof(ElementPtr) * dictionary->size);

    return dictionary;
}

/// <summary>
/// Dictionary creation.
/// </summary>
/// <returns>Dict.</returns>
DictionaryPtr DictCreate(const int elementSize)
{
    return InternalDictCreate(INITIAL_SIZE, elementSize);
}

/// <summary>
/// Dictionary destroy.
/// </summary>
/// <param name="d">The d.</param>
void DictDestroy(DictionaryPtr d)
{ 
    if (d == NULL) return;

    for (int index = 0; index < d->size; index++) 
    {
        ElementPtr next;
        for (ElementPtr element = d->table[index]; element != 0; element = next)
        {
            next = element->next;
            FREE(element->key);  // NOLINT(clang-diagnostic-cast-qual)
            FREE(element->value);
            FREE(element);
        }
    }

    FREE(d->table);
    FREE(d);
}

/// <summary>
/// Hash_function
/// </summary>
/// <param name="key">The string.</param>
/// <returns>unsigned long.</returns>
static unsigned long HashFunction(const char *key)
{
    unsigned long hash = 0;

    for (unsigned long index = 0; key[index]; ++index)
    {
        hash += ((index % 2) ? tolower(key[index]) : toupper(key[index]));
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
static DictionaryPtr Grow(DictionaryPtr d)
{
    // ReSharper disable once CppTooWideScope
    const char* module = "Grow";

    DictionaryPtr d2 = InternalDictCreate(d->size * GROWTH_FACTOR, d->element_size);
    if (d2 == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    d2->collisions = d->collisions;
    for (int index = 0; index < d->size; index++) 
    {
        for (ElementPtr element = d->table[index]; element != 0; element = element->next) 
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

    // ReSharper disable once CppLocalVariableMayBeConst
    ElementPtr e = (ElementPtr)ALLOCATE(sizeof(Element));
    if (e == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    // IMPORTANT: This sets the next to NULL
    memset(e, 0, sizeof(Element));

    e->key = key;
    if (e->key == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    e->value = ALLOCATE(d->element_size);
    if (e->value == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    memcpy(e->value, value, d->element_size);

    const unsigned long h = HashFunction(e->key) % d->size;
    e->next = d->table[h];
    if (e->next) 
        d->collisions++;

    d->table[h] = e;
    d->number_elements++;

    /* grow table if there is not enough room */
    if ((double)(d->number_elements) >= (d->size * MAX_LOAD_FACTOR))
    {
        *dd = Grow(d);        
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
    const unsigned long h = HashFunction(key) % d->size;
    for (ElementPtr e = d->table[h]; e != 0; e = e->next)
    {
        if (!StrICmp(e->key, key)) 
        {
            /* got it */
            return e->value;
        }
    }
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
    const unsigned long h = HashFunction(key) % d->size;

    for (ElementPtr* prev = &(d->table[h]); *prev != 0; prev = &((*prev)->next)) 
    {
        if (!StrICmp((*prev)->key, key)) 
        {
            /* got it */
            // ReSharper disable once CppLocalVariableMayBeConst
            ElementPtr e = *prev;
            *prev = e->next;

            FREE(e->key);
            FREE(e->value);
            FREE(e);
            return;
        }
    }
}
