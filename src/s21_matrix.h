#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SUCCESS 1
#define FAILURE 0
#define PRECISION 1e-7
enum statuses {
    OK,
    INCORRECT_MTRX,
    CALC_ERROR
};


typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
void s21_print_matrix(matrix_t A);
void s21_fill_matrix(matrix_t *A, double value);
int incorrect_matrix(matrix_t *A);
int equal_matrix_size(matrix_t *A, matrix_t *B);
void set_size(int rows, int columns, matrix_t *A);
void matrix_struct_init(matrix_t *A);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_
