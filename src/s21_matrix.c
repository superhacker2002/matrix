#include "s21_matrix.h"

int main() {
    matrix_t matrix;
    matrix_init(&matrix);
    s21_create_matrix(3, 4, &matrix);
    s21_fill_matrix(&matrix);
    s21_print_matrix(&matrix);

    printf("%d\n", matrix.rows);
    printf("%d\n", matrix.columns);
    s21_remove_matrix(&matrix);
}

void matrix_init(matrix_t *A) {
    A->columns = 0;
    A->rows = 0;
    A->matrix = NULL;
}

void s21_print_matrix(matrix_t *A) {
    for (int row; row < A->rows; row++) {
        for (int column; column < A->columns; column++) {
            printf("%f ", A->matrix[row][column]);
        }
        printf("\n");
    }
}

void s21_fill_matrix(matrix_t *A) {
    for (int row; row < A->rows; row++) {
        for (int column; column < A->columns; column++) {
            A->matrix[row][column] = 1.12345678; 
        }
    }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int status = SUCCESS;
    if (rows <= 0 && columns <= 0) {
        status = FAILURE;
    } else {
        result->rows = rows;
        result->columns = columns;
        result->matrix = (double **)malloc(rows * sizeof(double*));
        for (int row = 0; row < rows; row++) {
           result->matrix[row] = (double *)malloc(columns * sizeof(double));
        }
    }
    return status;
}

void s21_remove_matrix(matrix_t *A) {
    for (int row = 0; row < A->rows; row++) {
        free(A->matrix[row]);
    }
    free(A);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int status = SUCCESS;
    double precision = 0.0000001;
    if (A->rows == B->rows && A->columns == B->columns) {
        int equal = 0;
        status = FAILURE;
        for (int row; row < A->rows; row++) {
            for (int column; column < A->columns; column++) {
                if ((A->matrix[row][column] - precision) < B->matrix[row][column] &&
                    (A->matrix[row][column] + precision) > B->matrix[row][column]) {
                    status = FAILURE;
                    break;  
                }
            }
        }
    }
}