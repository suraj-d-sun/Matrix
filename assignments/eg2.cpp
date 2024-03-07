//Assignment -01
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Matrix {
private:
    int **ptr;
    int rows, cols;

public:
    Matrix() {
        rows = 0;
        cols = 0;
        ptr = NULL;
    }

    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        ptr = (int **)malloc(sizeof(int *) * rows);
        for (int i = 0; i < rows; i++) {
            ptr[i] = (int *)malloc(sizeof(int) * cols);
        }
    }

    Matrix operator*(const Matrix &other) {
        if (cols != other.rows)
            throw string("Unable to perform operation for the given dimensions");

        Matrix z(rows, other.cols);
        int sum = 0;

        for (int r1 = 0; r1 < rows; r1++) {
            for (int c2 = 0; c2 < other.cols; c2++) {
                sum = 0;
                for (int c1 = 0, r2 = 0; c1 < cols; c1++, r2++) {
                    sum += (ptr[r1][c1]) * (other.ptr[r2][c2]);
                }
                int r3 = r1;
                int c3 = c2;
                z.ptr[r3][c3] = sum;
            }
        }
        return z;
    }

    int getRowCount() {
        return rows;
    }

    int getColumnCount() {
        return cols;
    }

    int getData(int row, int col) {
        return ptr[row][col];
    }

    int &operator()(int r, int c) {
        return ptr[r][c];
    }

    ~Matrix() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                delete ptr[r];
            }
        }
        delete ptr;
    }
};

ostream &operator<<(ostream &o, Matrix &m) {
    for (int r = 0; r < m.getRowCount(); r++) {
        for (int c = 0; c < m.getColumnCount(); c++) {
            o << m.getData(r, c) << " ";
        }
        o << endl;
    }
    return o;
}

int main() {
    try {
        Matrix x(4, 5);
        Matrix y(5, 2);

        x(0, 0) = 1;
        x(0, 1) = 2;
        x(0, 2) = 3;
        x(0, 3) = 4;
        x(0, 4) = 5;

        x(1, 0) = 6;
        x(1, 1) = 7;
        x(1, 2) = 8;
        x(1, 3) = 9;
        x(1, 4) = 10;

        x(2, 0) = 11;
        x(2, 1) = 12;
        x(2, 2) = 13;
        x(2, 3) = 14;
        x(2, 4) = 15;

        x(3, 0) = 16;
        x(3, 1) = 17;
        x(3, 2) = 18;
        x(3, 3) = 19;
        x(3, 4) = 20;

        y(0, 0) = 10;
        y(0, 1) = 20;

        y(1, 0) = 30;
        y(1, 1) = 40;

        y(2, 0) = 50;
        y(2, 1) = 60;

        y(3, 0) = 70;
        y(3, 1) = 80;

        y(4, 0) = 90;
        y(4, 1) = 100;

        Matrix z;
        z = x * y;
        cout << endl
             << z << endl;
    } catch (string e) {
        cout << "Error : " << e << endl;
    }
    return 0;
}
