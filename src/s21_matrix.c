#include "s21_matrix.h"

// void s21_print_matrix(matrix_t A) {
//     for (int row = 0; row < A.rows; row++) {
//         for (int column = 0; column < A.columns; column++) {
//             printf("%.10lf ", A.matrix[row][column]);
//         }
//         printf("\n");
//     }
// }

void matrix_struct_init(matrix_t *A) {
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
}

void s21_fill_matrix(matrix_t *A, double value) {
    for (int row = 0; row < A->rows; row++) {
        for (int column = 0; column < A->columns; column++) {
            A->matrix[row][column] = value;
        }
    }
}

int incorrect_matrix(matrix_t *A) {
    int status = 0;
    if (A->rows <= 0 || A->columns <= 0 || A->matrix == NULL) {
        status = 1;
    }
    return status;
}

int equal_matrix_size(matrix_t *A, matrix_t *B) {
    int status = 0;
    if (A->rows == B->rows && A->columns == B->columns) {
        status = 1;
    }
    return status;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int status = 0;
    if (rows <= 0 && columns <= 0) {
        status = 1;
    } else {
        set_size(rows, columns, result);
        result->matrix = calloc(rows, sizeof(double*));
        for (int row = 0; row < rows; row++) {
           result->matrix[row] = calloc(columns, sizeof(double));
        }
    }
    return status;
}

void s21_remove_matrix(matrix_t *A) {
    for (int row = 0; row < A->rows; row++) {
        free(A->matrix[row]);
    }
    free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int status = SUCCESS;
    if (incorrect_matrix(A) || incorrect_matrix(B)) status = FAILURE;
    if (equal_matrix_size(A, B)) {
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < A->columns; column++) {
                if (fabs(A->matrix[row][column] - B->matrix[row][column]) >= PRECISION) {
                    status = FAILURE;
                    break;
                }
            }
        }
    } else {
        status = FAILURE;
    }
    return status;
}

void set_size(int rows, int columns, matrix_t *A) {
    A->rows = rows;
    A->columns = columns;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int status = OK;
    if (incorrect_matrix(A) || incorrect_matrix(B)) status = INCORRECT_MTRX;
    if (equal_matrix_size(A, B)) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < A->columns; column++) {
               result->matrix[row][column] = A->matrix[row][column] + B->matrix[row][column];
            }
        }
    } else {
        status = CALC_ERROR;
    }
    return status;
}
