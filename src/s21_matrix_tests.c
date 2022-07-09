#include "s21_matrix.h"
#include <check.h>
#define MAX_DOUBLE 1.7976931348623158e308

START_TEST(s21_eq_matrix_tests) {
    matrix_t first_matrix;
    matrix_t second_matrix;

    s21_create_matrix(3, 4, &first_matrix);
    s21_create_matrix(3, 4, &second_matrix);
    s21_fill_matrix(&first_matrix, 123456.1234567);
    s21_fill_matrix(&second_matrix, 123456.1234568);
    ck_assert_int_eq(s21_eq_matrix(&first_matrix, &second_matrix), FAILURE);  // different values
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);

    s21_create_matrix(3, 3, &first_matrix);
    s21_create_matrix(3, 4, &second_matrix);
    s21_fill_matrix(&first_matrix, 123456.1234567);
    s21_fill_matrix(&second_matrix, 123456.1234567);
    ck_assert_int_eq(s21_eq_matrix(&first_matrix, &second_matrix), FAILURE);  // different sizes
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);

    s21_create_matrix(1000, 1000, &first_matrix);
    s21_create_matrix(1000, 1000, &second_matrix);
    s21_fill_matrix(&first_matrix, 123456.1234567999);
    s21_fill_matrix(&second_matrix, 123456.1234567456);
    ck_assert_int_eq(s21_eq_matrix(&first_matrix, &second_matrix), SUCCESS);  // equal
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);

    s21_create_matrix(1, 1, &first_matrix);
    s21_create_matrix(1, 1, &second_matrix);
    s21_fill_matrix(&first_matrix, MAX_DOUBLE);
    s21_fill_matrix(&second_matrix, MAX_DOUBLE);
    ck_assert_int_eq(s21_eq_matrix(&first_matrix, &second_matrix), SUCCESS);  // equal max doubles
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);

    matrix_struct_init(&first_matrix);
    matrix_struct_init(&second_matrix);
    ck_assert_int_eq(s21_eq_matrix(&first_matrix, &second_matrix), FAILURE);  // zero structures

    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);
    ck_assert_ptr_eq(first_matrix.matrix, NULL);
    ck_assert_ptr_eq(second_matrix.matrix, NULL);  // check for removing pointers array in struct
}
END_TEST

START_TEST(s21_sum_matrix_tests) {
    matrix_t first_matrix;
    matrix_t second_matrix;
    matrix_t sum_result;

    s21_create_matrix(3, 4, &first_matrix);  // correct matrices
    s21_create_matrix(3, 4, &second_matrix);
    s21_fill_matrix(&first_matrix, 2.0);
    s21_fill_matrix(&second_matrix, 1.0);
    ck_assert_int_eq(s21_sum_matrix(&first_matrix, &second_matrix, &sum_result), OK);
    for (int i = 0; i < first_matrix.rows; i++) {
        for (int j = 0; j < first_matrix.columns; j++) {
            ck_assert_double_eq(sum_result.matrix[i][j], 2.0 + 1.0);
        }
    }
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);
    s21_remove_matrix(&sum_result);

    s21_create_matrix(3, 4, &first_matrix);  // different sizes
    s21_create_matrix(3, 3, &second_matrix);
    s21_fill_matrix(&first_matrix, 2.0);
    s21_fill_matrix(&second_matrix, 1.0);
    ck_assert_int_eq(s21_sum_matrix(&first_matrix, &second_matrix, &sum_result), CALC_ERROR);
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);

    matrix_struct_init(&first_matrix);  // zero structures
    matrix_struct_init(&second_matrix);
    s21_fill_matrix(&first_matrix, 2.0);
    s21_fill_matrix(&second_matrix, 1.0);
    ck_assert_int_eq(s21_sum_matrix(&first_matrix, &second_matrix, &sum_result), INCORRECT_MTRX);
}
END_TEST

START_TEST(s21_sub_matrix_tests) {
    matrix_t first_matrix;
    matrix_t second_matrix;
    matrix_t sum_result;

    s21_create_matrix(3, 4, &first_matrix);  // correct matrices
    s21_create_matrix(3, 4, &second_matrix);
    s21_fill_matrix(&first_matrix, 2.0);
    s21_fill_matrix(&second_matrix, 1.0);
    ck_assert_int_eq(s21_sub_matrix(&first_matrix, &second_matrix, &sum_result), OK);
    for (int i = 0; i < first_matrix.rows; i++) {
        for (int j = 0; j < first_matrix.columns; j++) {
            ck_assert_double_eq(sum_result.matrix[i][j], 2.0 - 1.0);
        }
    }
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);
    s21_remove_matrix(&sum_result);

    s21_create_matrix(3, 4, &first_matrix);  // different sizes
    s21_create_matrix(3, 3, &second_matrix);
    s21_fill_matrix(&first_matrix, 2.0);
    s21_fill_matrix(&second_matrix, 1.0);
    ck_assert_int_eq(s21_sub_matrix(&first_matrix, &second_matrix, &sum_result), CALC_ERROR);
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);

    matrix_struct_init(&first_matrix);  // zero structures
    matrix_struct_init(&second_matrix);
    s21_fill_matrix(&first_matrix, 2.0);
    s21_fill_matrix(&second_matrix, 1.0);
    ck_assert_int_eq(s21_sub_matrix(&first_matrix, &second_matrix, &sum_result), INCORRECT_MTRX);
}
END_TEST

START_TEST(s21_mult_number_tests) {
    matrix_t first_matrix;
    matrix_t result;
    s21_create_matrix(1000, 1000, &first_matrix);  // correct matrix
    s21_fill_matrix(&first_matrix, 123456.12345678);
    ck_assert_int_eq(s21_mult_number(&first_matrix, 2.0, &result), OK);
    ck_assert_double_eq(result.matrix[0][0], 123456.12345678 * 2.0);
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&result);

    s21_create_matrix(5, 5, &first_matrix);  // correct matrix
    s21_fill_matrix(&first_matrix, -999);
    ck_assert_int_eq(s21_mult_number(&first_matrix, 1000.0, &result), OK);
    ck_assert_double_eq(result.matrix[0][0], -999 * 1000.0);
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&result);

    matrix_struct_init(&first_matrix);  //  zero structure
    ck_assert_int_eq(s21_mult_number(&first_matrix, 2.0, &result), INCORRECT_MTRX);
}
END_TEST

START_TEST(s21_mult_matrix_tests) {
    matrix_t first_matrix;
    matrix_t second_matrix;
    matrix_t result;
    s21_create_matrix(2, 3, &first_matrix);  // correct matrices
    s21_create_matrix(3, 2, &second_matrix);
    s21_fill_matrix(&first_matrix, 2.0);
    s21_fill_matrix(&second_matrix, 3.0);
    ck_assert_int_eq(s21_mult_matrix(&first_matrix, &second_matrix, &result), OK);
    ck_assert_int_eq(result.rows, first_matrix.rows);  // check size
    ck_assert_int_eq(result.columns, second_matrix.columns);
    for (int i = 0; i < first_matrix.rows; i++) {
        for (int j = 0; j < second_matrix.columns; j++) {
            ck_assert_double_eq(result.matrix[i][j], 18.0);
        }
    }
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);
    s21_remove_matrix(&result);

    s21_create_matrix(2, 3, &first_matrix);  // correct matrices
    s21_create_matrix(2, 3, &second_matrix);
    ck_assert_int_eq(s21_mult_matrix(&first_matrix, &second_matrix, &result), CALC_ERROR);
    s21_remove_matrix(&first_matrix);
    s21_remove_matrix(&second_matrix);

    matrix_struct_init(&first_matrix);  // zero structures
    matrix_struct_init(&second_matrix);
    ck_assert_int_eq(s21_mult_matrix(&first_matrix, &second_matrix, &result), INCORRECT_MTRX);
}

START_TEST(s21_transpose_tests) {
    matrix_t first_matrix;
    matrix_t result;
    s21_create_matrix(3, 4, &first_matrix);  // correct matrix
    s21_fill_matrix_random(&first_matrix);
    ck_assert_int_eq(s21_transpose(&first_matrix, &result), OK);
    ck_assert_int_eq(result.rows, first_matrix.columns);
    ck_assert_int_eq(result.columns, first_matrix.rows);
    s21_remove_matrix(&first_matrix);

    matrix_struct_init(&first_matrix);  // zero structure
    ck_assert_int_eq(s21_transpose(&first_matrix, &result), INCORRECT_MTRX);
}

int main(void) {
    Suite *suite = suite_create("s21_matrix_tests");
    SRunner *srunner = srunner_create(suite);

    TCase *eq_matrix = tcase_create("s21_eq_matrix");
    suite_add_tcase(suite, eq_matrix);
    tcase_add_test(eq_matrix, s21_eq_matrix_tests);

    TCase *sum_matrix = tcase_create("s21_sum_matrix");
    suite_add_tcase(suite, sum_matrix);
    tcase_add_test(sum_matrix, s21_sum_matrix_tests);

    TCase *sub_matrix = tcase_create("s21_sub_matrix");
    suite_add_tcase(suite, sub_matrix);
    tcase_add_test(sub_matrix, s21_sub_matrix_tests);

    TCase *mult_number = tcase_create("s21_mult_number");
    suite_add_tcase(suite, mult_number);
    tcase_add_test(mult_number, s21_mult_number_tests);

    TCase *mult_matrix = tcase_create("s21_mult_matrix");
    suite_add_tcase(suite, mult_matrix);
    tcase_add_test(mult_matrix, s21_mult_matrix_tests);

    TCase *transpose = tcase_create("s21_transpose");
    suite_add_tcase(suite, transpose);
    tcase_add_test(transpose, s21_transpose_tests);

    srunner_run_all(srunner, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
