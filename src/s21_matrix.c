#include "s21_matrix.h"

int main() {
    matrix_t s21_matrix;
    matrix_t s21_matrix_2;
    s21_create_matrix(3, 4, &s21_matrix);
    s21_create_matrix(3, 4, &s21_matrix_2);

    s21_fill_matrix(&s21_matrix);
    s21_fill_matrix(&s21_matrix_2);
    
    int result = s21_eq_matrix(&s21_matrix, &s21_matrix_2);
    printf("equal: %d", result);
    s21_remove_matrix(&s21_matrix);
    s21_remove_matrix(&s21_matrix_2);
}


void s21_print_matrix(matrix_t A) {
    for (int row = 0; row < A.rows; row++) {
        for (int column = 0; column < A.columns; column++) {
            printf("%f ", A.matrix[row][column]);
        }
        printf("\n");
    }
}

void s21_fill_matrix(matrix_t *A) {
    for (int row = 0; row < A->rows; row++) {
        for (int column = 0; column < A->columns; column++) {
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
    double precision = 0.0000001;
    if (A->rows != B->rows && A->columns != B->columns) {
        status = FAILURE;
    } else {
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < A->columns; column++) {
                if ((A->matrix[row][column] - precision) < B->matrix[row][column] &&
                    (A->matrix[row][column] + precision) > B->matrix[row][column]) {
                    status = FAILURE;
                    break;
                }
            }
        }
    }
    return status;
}