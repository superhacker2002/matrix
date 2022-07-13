#include "s21_matrix.h"

void s21_print_matrix(matrix_t A) {
    for (int row = 0; row < A.rows; row++) {
        for (int column = 0; column < A.columns; column++) {
            printf("%.10lf ", A.matrix[row][column]);
        }
        printf("\n");
    }
}

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

void s21_fill_matrix_scanf(matrix_t *A) {
    for (int row = 0; row < A->rows; row++) {
        for (int column = 0; column < A->columns; column++) {
            scanf("%lf", &A->matrix[row][column]);
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
    if (incorrect_matrix(A) || incorrect_matrix(B)) {
        status = FAILURE;
    } else if (equal_matrix_size(A, B)) {
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
    if (incorrect_matrix(A) || incorrect_matrix(B)) {
        status = INCORRECT_MTRX;
    } else if (equal_matrix_size(A, B)) {
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

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int status = OK;
    if (incorrect_matrix(A) || incorrect_matrix(B)) {
        status = INCORRECT_MTRX;
    } else if (equal_matrix_size(A, B)) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < A->columns; column++) {
               result->matrix[row][column] = A->matrix[row][column] - B->matrix[row][column];
            }
        }
    } else {
        status = CALC_ERROR;
    }
    return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int status = OK;
    if (incorrect_matrix(A)) {
        status = INCORRECT_MTRX;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < A->columns; column++) {
               result->matrix[row][column] = A->matrix[row][column] * number;
            }
        }
    }
    return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int status = OK;
    if (incorrect_matrix(A) || incorrect_matrix(B)) {
        status = INCORRECT_MTRX;
    } else if (A->columns == B->rows) {
        s21_create_matrix(A->rows, B->columns, result);
        for (int row = 0; row < result->rows; row++) {
            for (int column = 0; column < result->columns; column++) {
                result->matrix[row][column] = 0;
                for (int k = 0; k < A->columns; k++) {
                    result->matrix[row][column] += A->matrix[row][k] * B->matrix[k][column];
                }
            }
        }
    } else {
        status = CALC_ERROR;
    }
    return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int status = OK;
    if (incorrect_matrix(A)) {
        status = INCORRECT_MTRX;
    } else {
        s21_create_matrix(A->columns,  A->rows, result);
        for (int row = 0; row < A->columns; row++) {
            for (int column = 0; column < A->rows; column++) {
                result->matrix[row][column] = A->matrix[column][row];
            }
        }
    }
    return status;
}

void s21_fill_matrix_random(matrix_t *A) {
    srand(time(NULL));
    for (int row = 0; row < A->rows; row++) {
        for (int column = 0; column < A->columns; column++) {
            A->matrix[row][column] = (double)(rand () % 10);
        }
    }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int status = OK;
    double matrix_minor = 0;
    matrix_t determinant;
    if (incorrect_matrix(A)) {
        status = INCORRECT_MTRX;
    } else {
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < A->columns; column++) {
                s21_create_matrix(A->rows - 1, A->columns - 1, &determinant);
                fill_determinant(&determinant, row, column, A);

            }
        }
    }
    return status;
}

void fill_determinant(matrix_t *determinant, int deleted_row, int deleted_column, matrix_t *prev_matrix) {
    int row_new = 0, col_new = 0;
    double determinant_num = 0;
    for (int row = 0; row < prev_matrix->rows; row++) {
        if (row == deleted_row) row++;
        col_new = 0;
        for (int column = 0; column < prev_matrix->columns; column++) {
            if (column == deleted_column) column++;
            determinant->matrix[row_new][col_new++] = prev_matrix->matrix[row][column];
        }
        row_new++;
    }
    if (row_new == 2) {
        determinant_num = find_det_matrix_2x2(determinant);
    } else if (row_new == 3) {
        
    }
}

double find_det_matrix_2x2(matrix_t *determinant) {
    return determinant->matrix[0][0] * determinant->matrix[1][1] -
            determinant->matrix[0][1] * determinant->matrix[1][0];
}


int main() {
//     matrix_t s21_matrix;
//     matrix_t s21_matrix_2;
//     matrix_t result;
//     s21_create_matrix(2, 2, &s21_matrix);
//     s21_create_matrix(3, 2, &s21_matrix_2);
//     printf("first\n");
//     s21_fill_matrix(&s21_matrix, 1.0);
//     printf("second\n");
//     s21_fill_matrix_scanf(&s21_matrix_2);
//     // s21_mult_matrix(&s21_matrix, &s21_matrix_2, &result);
//     s21_transpose(&s21_matrix_2, &result);

//     s21_print_matrix(result);

    matrix_t A;
    matrix_t det;
    s21_create_matrix(5, 5, &A);

    s21_create_matrix(4, 4, &det);
    s21_fill_matrix_random(&A);
    s21_print_matrix(A);
    printf("---------------------\n");
    fill_determinant(&det, 1, 2, &A);
    s21_print_matrix(det);
}
