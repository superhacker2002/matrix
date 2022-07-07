#include "s21_matrix.h"

int main() {
    matrix_t s21_matrix;
    matrix_t s21_matrix_2;
    s21_create_matrix(3, 4, &s21_matrix);
    s21_create_matrix(3, 4, &s21_matrix_2);
    s21_fill_matrix(&s21_matrix, 1.1234567);
    s21_print_matrix(s21_matrix);
    
    s21_fill_matrix(&s21_matrix_2, 1.1234567);
    s21_print_matrix(s21_matrix_2);
    // if (s21_eq_matrix(&s21_matrix, &s21_matrix_2) == SUCCESS) {
    //     printf("equal\n");
    // } else {
    //     printf("not equal\n ");
    // }
    // printf("%d\n", matrix.rows);
    // printf("%d\n", matrix.columns);
    s21_remove_matrix(&s21_matrix);
    s21_remove_matrix(&s21_matrix_2);
}

void s21_print_matrix(matrix_t A) {
    for (int row = 0; row < A.rows; row++) {
        for (int column = 0; column < A.columns; column++) {
            printf("%.10lf ", A.matrix[row][column]);
        }
        printf("\n");
    }
}

void s21_fill_matrix(matrix_t *A, double value) {
    for (int row = 0; row < A->rows; row++) {
        for (int column = 0; column < A->columns; column++) {
            A->matrix[row][column] = value; 
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
    double eps = 0.0000001;
    if (A->rows == B->rows && A->columns == B->columns) {
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < A->columns; column++) {
                if (fabs(A->matrix[row][column] - B->matrix[row][column]) < eps) { 
                } else {
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