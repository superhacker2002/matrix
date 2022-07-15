#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int status = OK;
    if (rows <= 0 || columns <= 0) {
        status = INCORRECT_MTRX;
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
    if (A && A->matrix) {
        for (int row = 0; row < A->rows; row++) {
            free(A->matrix[row]);
        }
        free(A->matrix);
    }
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

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int status = OK;
    matrix_t minor;
    if (incorrect_matrix(A)) {
        status = INCORRECT_MTRX;
    } else if (A->rows != A->columns) {
        status = CALC_ERROR;
    } else {
        double determinant = 0;
        s21_create_matrix(A->rows, A->columns, result);
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < A->columns; column++) {
                s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
                s21_fill_minor_matrix(A, row, column, &minor);
                s21_determinant(&minor, &determinant);
                result->matrix[row][column] = pow(-1, row + column) * determinant;
                s21_remove_matrix(&minor);
            }
        }
    }
    return status;
}

int s21_determinant(matrix_t *A, double *result) {
    int status = OK;
    if (incorrect_matrix(A) || A->columns != A->rows) {
        status = INCORRECT_MTRX;
    } else {
        *result = 0;
        if (A->rows == 1) {
            *result  = A->matrix[0][0];
        } else if (A->rows == 2) {
            *result  = find_det_matrix_2x2(A);
        } else {
            matrix_t minor;
            minor.matrix = NULL;
            s21_create_matrix(A->rows -1, A->columns - 1, &minor);
            for (int i = 0; i < A->columns; i++) {
                double tmp = 0;
                s21_fill_minor_matrix(A, 0, i, &minor);
                s21_determinant(&minor, &tmp);
                tmp = pow(-1, i + 2) * tmp;
                *result += (A->matrix[0][i]) * tmp;
            }
            s21_remove_matrix(&minor);
        }
    }
    return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int status = OK;
    if (incorrect_matrix(A)) {
        status = INCORRECT_MTRX;
    } else if (A->rows != A->columns) {
        status = CALC_ERROR;
    } else {
        double determinant = 0;
        matrix_t transposed_A;
        matrix_t complements_transposed;
        s21_determinant(A, &determinant);
        if (fabs(determinant) < EPS) {
            status = CALC_ERROR;
        } else {
            s21_transpose(A, &transposed_A);
            s21_calc_complements(&transposed_A, &complements_transposed);
            s21_mult_number(&complements_transposed, 1.0 / determinant, result);
            s21_remove_matrix(&transposed_A);
            s21_remove_matrix(&complements_transposed);
        }
    }
    return status;
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

void set_size(int rows, int columns, matrix_t *A) {
    A->rows = rows;
    A->columns = columns;
}

void s21_fill_matrix_random(matrix_t *A) {
    srand(time(NULL));
    for (int row = 0; row < A->rows; row++) {
        for (int column = 0; column < A->columns; column++) {
            A->matrix[row][column] = (double)(rand () % 10);
        }
    }
}

void s21_fill_minor_matrix(matrix_t *A, int deleted_row, int deleted_col, matrix_t *minor) {
    if (minor->matrix != NULL) {
        for (int row = 0, row_small = 0; row < A->rows; row++) {
            if (row != deleted_row) {
                for (int col = 0, col_small = 0; col < A->columns; col++) {
                    if (col != deleted_col) {
                       minor->matrix[row_small][col_small++] = A->matrix[row][col];
                    }
                }
                row_small++;
            }
        }
    }
}

double find_det_matrix_2x2(matrix_t *determinant) {
    return determinant->matrix[0][0] * determinant->matrix[1][1] -
            determinant->matrix[0][1] * determinant->matrix[1][0];
}



