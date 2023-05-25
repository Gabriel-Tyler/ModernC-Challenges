#include <limits.h> /* SIZE_MAX */
#include <stddef.h> /* NULL, size_t */
#include <stdio.h>  /* fprintf, stderr */
#include <stdlib.h> /* malloc, calloc, free */

#include "unionfind.h" 

/*
typedef struct uf_t {
    size_t size;
    size_t* parent;
} UnionFind;
*/

/* Size: Get size of parent array */
size_t uf_size(UnionFind* this)
{
    if (this == NULL) {
        fprintf(stderr, "uf_size: this is NULL\n");
        return 0;
    }
    return this->size;
}

/* ParentAt: Return the value of parent at the index */
size_t uf_parentAt(UnionFind* this, size_t index)
{
    if (this == NULL) {
        fprintf(stderr, "uf_parentAt: this is NULL\n");
        return SIZE_MAX;
    }
    if (index >= uf_size(this)) {
        fprintf(stderr, "uf_parentAt: index out of bounds\n");
        return SIZE_MAX;
    }
    return this->parent[index];
}

/* SetParentAt: Set the value of parent at the index to another value */
void uf_setParentAt(UnionFind* this, size_t index, size_t value)
{
    if (this == NULL) {
        fprintf(stderr, "uf_setParentAt: this is NULL\n");
        return;
    }
    if (index >= uf_size(this)) {
        fprintf(stderr, "uf_setParentAt: index out of bounds\n");
        return;
    }
    this->parent[index] = value;
}

/* Init: Allocate size for parent and set size
 *       Return null if unable to allocate parent */
UnionFind* uf_init(size_t size)
{
    if (size == 0) {
        fprintf(stderr, "uf_init: given size is zero\n");
        return NULL;
    }

    UnionFind* this = malloc(sizeof(UnionFind));
    if (this == NULL) {
        fprintf(stderr, "uf_init: could not allocate uf struct\n");
        uf_clear(this);
        return NULL;
    }

    this->size = size;
    this->parent = calloc(size, sizeof(size_t));
    if (this->parent == NULL) {
        fprintf(stderr, "uf_init: could not allocate parent array\n");
        uf_clear(this);
        return NULL;
    }
    for (int i = 0; i < size; ++i)
        uf_setParentAt(this, i, SIZE_MAX);

    return this;
}

/* Clear: Free space of parent and UnionFind pointer */
void uf_clear(UnionFind* this)
{
    if (this != NULL && this->parent != NULL)
        free(this->parent);
    if (this != NULL)
        free(this);
}

/* Reset: Set all indices to be roots */
void uf_reset(UnionFind* this)
{
    if (this == NULL) {
        fprintf(stderr, "uf_reset: this is NULL\n");
        return;
    }
    for (int i = 0; i < uf_size(this); ++i)
        uf_setParentAt(this, i, SIZE_MAX);
}

/* Find: For a given index, return the root of its tree */
size_t uf_find(UnionFind* this, size_t index)
{
    if (this == NULL) {
        fprintf(stderr, "uf_find: this is NULL\n");
        return SIZE_MAX;
    }

    if (index >= uf_size(this)) {
        fprintf(stderr, "uf_find: index out of bounds\n");
        return SIZE_MAX;
    }

    size_t p = uf_parentAt(this, index);

    if (p == SIZE_MAX)
        return index;
    return uf_find(this, p);
}

/* FindReplace: Change all parent entries on a path to the root (including) 
 *              to a specific value */
void uf_findReplace(UnionFind* this, size_t index, size_t value)
{
    if (this == NULL) {
        fprintf(stderr, "uf_findReplace: this is NULL\n");
        return;
    }

    if (index >= uf_size(this)) {
        fprintf(stderr, "uf_findReplace: index out of bounds\n");
        return;
    }

    size_t p = uf_parentAt(this, index);
    uf_setParentAt(this, index, value);

    if (p == SIZE_MAX)
        return;
    uf_findReplace(this, p, value);
}

/* FindCompress: Change all parent entries to the root that has been found 
 *               Return index of root of tree */
size_t uf_findCompress(UnionFind* this, size_t index)
{
    if (this == NULL) {
        fprintf(stderr, "uf_findCompress: this is NULL\n");
        return SIZE_MAX;
    }
    if (index >= uf_size(this)) {
        fprintf(stderr, "uf_findCompress: index out of bounds\n");
        return SIZE_MAX;
    }

    size_t root = uf_find(this, index);
    if (root == SIZE_MAX) {
        fprintf(stderr, "uf_findCompress: root is SIZE_MAX\n");
        return SIZE_MAX;
    }

    uf_findReplace(this, index, root); 
    uf_setParentAt(this, root, SIZE_MAX); /* set root back to SIZE_MAX */
    return root;
}

/* Union: Given two elements, combine their trees into one
 *        Use FindCompress for one side and FindReplace for the other */
void uf_union(UnionFind* this, size_t index1, size_t index2)
{
    if (this == NULL) {
        fprintf(stderr, "uf_union: this is NULL\n");
        return;
    }

    if (index1 >= uf_size(this)) {
        fprintf(stderr, "uf_union: index1 out of bounds\n");
        return;
    }
    if (index2 >= uf_size(this)) {
        fprintf(stderr, "uf_union: index2 out of bounds\n");
        return;
    }

    size_t root1 = uf_findCompress(this, index1);

    if (root1 == SIZE_MAX) {
        fprintf(stderr, "uf_union: index1 root is SIZE_MAX\n");
        return;
    }

    size_t root2 = uf_find(this, index2);
    if (root1 == root2)
        return; /* already in the same set */

    uf_findReplace(this, index2, root1);
}

/* Printf: [indices] \n [parents]*/
void uf_print(UnionFind* this)
{
    if (this == NULL) {
        fprintf(stderr, "uf_print: this is NULL\n");
        return;
    }

    printf("     i: [");
    for (size_t i = 0; i < uf_size(this); ++i)
        printf("%2zu ", i);
    printf("]\n");

    printf("parent: [");
    for (size_t i = 0; i < uf_size(this); ++i) {
        size_t p = uf_parentAt(this, i);
        if (p == SIZE_MAX)
            printf("rt ");
        else 
            printf("%2zu ", p);
    }
    printf("]\n");
}
