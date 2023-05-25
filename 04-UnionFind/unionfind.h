#pragma once

#include <stddef.h> /* size_t */

typedef struct uf_t {
    size_t size;
    size_t* parent;
} UnionFind;

/* Size: return size of parent array */
size_t uf_size(UnionFind* this);

/* ParentAt: return the value of parent at an index */
size_t uf_parentAt(UnionFind* this, size_t index);

/* SetParentAt: set the value of parent at the index to another value */
void uf_setParentAt(UnionFind* this, size_t index, size_t value);

/* Init: Allocate size for parent and set size 
 *       Return null if unable to allocate parent */
UnionFind* uf_init(size_t size);

/* Clear: Free space of parent and UnionFind pointer */
void uf_clear(UnionFind* this);

/* Reset: Set all indices to be roots */
void uf_reset(UnionFind* this);

/* Find: For a given index, return the root of its tree */
size_t uf_find(UnionFind* this, size_t index);

/* FindReplace: Change all parent entries on a path to the root (including) 
 *                to a specific value */
void uf_findReplace(UnionFind* this, size_t index, size_t value);

/* FindCompress: Change all parent entries to the root that has been found 
 *               Return index of root of tree */
size_t uf_findCompress(UnionFind* this, size_t index);

/* Union: Given two elements, combine their trees into one
 *        Use FindCompress for one side and FindReplace for the other */
void uf_union(UnionFind* this, size_t index1, size_t index2);

/* Printf: [indices] \n [parents]*/
void uf_print(UnionFind* this);

