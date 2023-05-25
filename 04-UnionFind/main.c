#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "unionfind.h"

void printMenu();
int getUInt(size_t lower, size_t upper);

int main(int argc, char* argv[static 1])
{

    if (argc != 2) {
        printf("usage: ./unionfind (size)\n");
        return EXIT_FAILURE;
    }

    size_t size;
    int matches = sscanf(argv[1], "%zu", &size);
    if (matches != 1) {
        printf("usage: ./unionfind (size)\nInvalid size\n");
        return EXIT_FAILURE;
    }

    UnionFind* uf = uf_init(size);
    if (uf == NULL) {
        fprintf(stderr, "main: could not init UnionFind\n");
        return EXIT_FAILURE;
    }

    bool good = true;
    while (good) {
        printMenu();
        size_t option = getUInt(1, 5);

        size_t i, j;
        switch (option) {

        case 1: /* union */
            printf("Index 1: \n");
            i = getUInt(0, uf_size(uf));
            printf("Index 2: \n");
            j = getUInt(0, uf_size(uf));
            if (i != j)
                uf_union(uf, i, j);
            break;

        case 2: /* find  */
            printf("Index to find: \n");
            i = getUInt(0, uf_size(uf));
            printf("Root of index %zu is %zu\n", i, uf_find(uf, i));
            break;

        case 3: /* reset */
            printf("Resetting...\n");
            uf_reset(uf);
            break;

        case 4: /* print */
            uf_print(uf);
            break;

        case 5: /* quit  */
            printf("Quitting...\n");
            good = false;
            break;

        default:
            fprintf(stderr, "main: unknown option, quitting\n");
            good = false;
        }
    }

    uf_clear(uf);
    return EXIT_SUCCESS;
}

void printMenu()
{
    printf("---- Union Find ----\n"
           "1. Union\n"
           "2. Find\n"
           "3. Reset\n"
           "4. Print\n"
           "5. Quit\n");
}

int getUInt(size_t lower, size_t upper)
{
    int matches;
    int n;
    do {
        printf("> ");
        matches = scanf("%d", &n);
    } while (matches != 1 || n < lower || n > upper);
    return n;
}

