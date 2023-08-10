/* Create adjacency matrix and the following functions: 
 *  - breadth first search
 *  - find connected components 
 *  - find a spanning tree 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SCREEN_CLEAR() printf("\033[H\033[J")

typedef struct Graph {
        size_t n;
        int**  adj_matrix;
} Graph;

int** make_square_int_matrix(size_t n) {
        int** sqr_matrix = calloc(n, sizeof(int*));
        for (size_t i = 0; i < n; ++i)
                sqr_matrix[i] = calloc(n, sizeof(int));
        return sqr_matrix;
}

void free_square_int_matrix(int** sqr_matrix, size_t n) {
        for (size_t i = 0; i < n; ++i)
                free(sqr_matrix[i]);
        free(sqr_matrix);
}

void init_graph(Graph* self, size_t n) {
        self->n = n;
        self->adj_matrix = make_square_int_matrix(n);
}

void free_graph(Graph* self) {
        free_square_int_matrix(self->adj_matrix, self->n);
}

void set_edge(Graph* self, size_t n1, size_t n2, int w) {
        self->adj_matrix[n1][n2] = w;
}

int get_edge(Graph* self, size_t n1, size_t n2) {
        return self->adj_matrix[n1][n2];
}

void print_graph(Graph* self) {
        size_t n = self->n;
        for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j)
                        printf("%d", get_edge(self, i, j));
                printf("\n");
        }
}

//void set_line(Graph* self, size_t r, size_t c, size_t len) {
//        // lmao
//        // only used in test_adj_matrix_line_animation()
//        size_t n = self->n;
//        size_t prev_r = r;
//        if (c == 0)
//                prev_r = (r+n-1)%n;
//        size_t prev_c = (c+n-1)%n;
//        set_edge(self, prev_r, prev_c, 0);
//        for (int i = 0; i < len; ++i) {
//                set_edge(self, (r+(c+i)/n)%n, (c+i)%n, 1);
//        }
//}
//
//void test_adj_matrix_line_animation(void) {
//        for (size_t i = 0; i < n; ++i) {
//                for (size_t j = 0; j < n; ++j) {
//                        SCREEN_CLEAR();
//                        set_line(&g, i, j, 8);
//                        print_graph(&g);
//                        usleep(100000);
//                }
//        }
//}

int main(void) {
        size_t const n = 10;
        Graph g;
        init_graph(&g, n);

        // -------- Cool animation: --------
        //size_t cycles = 2;
        //while (cycles--)
        //        test_adj_matrix_line_animation();

        free_graph(&g);
}


