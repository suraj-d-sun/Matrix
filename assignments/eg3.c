//ASSIGNMENT-02
#include <stdio.h>
#include <stdlib.h>

typedef struct __ndarray {
    int **data;
    int rows;
    int cols;
} ndarray;

struct __np {
    ndarray (*array)(int, int);
    ndarray (*dot)(ndarray, ndarray);
} np;

ndarray __create_ndarray(int rows, int cols) {
    ndarray n;
    n.rows = rows;
    n.cols = cols;
    n.data = (int **)malloc(sizeof(int *) * (n.rows));
    for (int r = 0; r < n.rows; r++) {
        n.data[r] = (int *)malloc(sizeof(int) * (n.cols));
    }
    return n;
}

ndarray __ndarray_multiply(ndarray a, ndarray b) {
    if (a.cols != b.rows) {
        printf("Unable to perform the operation for the given dimensions...");
        exit(0);
    }
    int r1, r2, c1, c2;
    int r3, c3;
    ndarray n = __create_ndarray(a.rows, b.cols);
    int sum = 0;
    for (r1 = 0; r1 < a.rows; r1++) {
        for (c2 = 0; c2 < b.cols; c2++) {
            sum = 0;
            for (c1 = 0, r2 = 0; c1 < a.cols; c1++, r2++) sum += (a.data[r1][c1]) * (b.data[r2][c2]);
            r3 = r1;
            c3 = c2;
            n.data[r3][c3] = sum;
        }
    }
    return n;
}

void print_ndarray(ndarray n) {
    for (int r = 0; r < n.rows; r++) {
        for (int c = 0; c < n.cols; c++) {
            printf("%d ", n.data[r][c]);
        }
        printf("\n");
    }
}

int main() {
    // np.array = __create_ndarray;
    // np.dot = __ndarray_multiply;
    ndarray x = np.array(4, 5);
    ndarray y = np.array(5, 2);
    ndarray z = np.dot(x, y);
    print_ndarray(z);
    return 0;
}
