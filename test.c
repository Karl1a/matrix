#include <check.h>
#include <locale.h>
#include <stdlib.h>

#include "s21_matrix.h"
/*
 Калькулятор для операций с матрицами
 https://ru.onlinemschool.com/math/assistance/matrix/determinant/
 */

// create and remove
START_TEST(s21_create_remove_good_test) {
  printf("Create and remove test 1\n");
  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(1, 1, &matrix), OK);
  s21_remove_matrix(&matrix);
}

END_TEST

START_TEST(s21_create_wrong_row_test) {
  printf("Create test 2\n");
  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(-1, 1, &matrix), INCORRECT_MATRIX);
}

END_TEST

START_TEST(s21_create_wrong_col_test) {
  printf("Create test 3\n");
  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(1, -1, &matrix), INCORRECT_MATRIX);
}

END_TEST

START_TEST(s21_create_wrong_row_col_test) {
  printf("Create test 4\n");
  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(-1, -1, &matrix), INCORRECT_MATRIX);
}

END_TEST

START_TEST(s21_create_nul_params_test) {
  printf("Create test 5\n");
  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(0, 0, &matrix), INCORRECT_MATRIX);
}

END_TEST

START_TEST(s21_create_null_matrix_test) {
  printf("Create test 6\n");
  ck_assert_int_eq(s21_create_matrix(-1, 1, NULL), INCORRECT_MATRIX);
}

END_TEST

// eq_matrix
START_TEST(s21_eq_good_test) {
  printf("Eq test 1\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  int count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      matrix2.matrix[y][x] = count;
      count++;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

START_TEST(s21_eq_diff_row_params_test) {
  printf("Eq test 2\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  s21_create_matrix(3, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  int count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      matrix2.matrix[y][x] = count;
      count++;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

START_TEST(s21_eq_diff_col_params_test) {
  printf("Eq test 3\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  int count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      matrix2.matrix[y][x] = count;
      count++;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

START_TEST(s21_eq_negat_params_test) {
  printf("Eq test 4\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  s21_create_matrix(-1, 2, &matrix1);
  s21_create_matrix(-1, 2, &matrix2);
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

START_TEST(s21_eq_diff_ceil_test) {
  printf("Eq test 5\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  int count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      matrix2.matrix[y][x] = count;
      count++;
    }
  }
  matrix1.matrix[0][0] = 100;
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

// sum
START_TEST(s21_sum_good_test) {
  printf("Sum test 1\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  s21_create_matrix(2, 2, &test_result);
  double count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      matrix2.matrix[y][x] = count;
      test_result.matrix[y][x] = count * 2;
      count++;
    }
  }
  printf("First matrix \n");
  printf("Second matrix \n");
  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), OK);
  printf("Result \n");
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_sum_diff_row_params_test) {
  printf("Sum test 2\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(s21_sum_diff_col_params_test) {
  printf("Sum test 3\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(s21_sum_first_null_matrix_test) {
  printf("Sum test 4\n");
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &matrix2);
  ck_assert_int_eq(s21_sum_matrix(NULL, &matrix2, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&matrix2);
}

END_TEST

START_TEST(s21_sum_second_null_matrix_test) {
  printf("Sum test 5\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &matrix1);
  ck_assert_int_eq(s21_sum_matrix(&matrix1, NULL, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&matrix1);
}

START_TEST(s21_sum_first_neg_param_test) {
  printf("Sum test 6\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 2, &matrix1);
  matrix1.columns = -1;
  s21_create_matrix(2, 2, &matrix2);
  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result),
                   INCORRECT_MATRIX);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

START_TEST(s21_sum_second_neg_params_test) {
  printf("Sum test 7\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(1, 2, &matrix2);
  matrix2.columns = -1;
  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result),
                   INCORRECT_MATRIX);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

// sub
START_TEST(s21_sub_good_test) {
  printf("Sub test 1\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  s21_create_matrix(2, 2, &test_result);
  double count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count * 3;
      matrix2.matrix[y][x] = count;
      test_result.matrix[y][x] = count * 2;
      count++;
    }
  }
  printf("First matrix \n");
  printf("Second matrix \n");
  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), OK);
  printf("Result \n");
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_sub_diff_row_params_test) {
  printf("Sub test 2\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(s21_sub_diff_col_params_test) {
  printf("Sub test 3\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(s21_sub_first_null_matrix_test) {
  printf("Sub test 4\n");
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &matrix2);
  ck_assert_int_eq(s21_sub_matrix(NULL, &matrix2, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&matrix2);
}

END_TEST

START_TEST(s21_sub_second_null_matrix_test) {
  printf("Sub test 5\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &matrix1);
  ck_assert_int_eq(s21_sub_matrix(&matrix1, NULL, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&matrix1);
}

START_TEST(s21_sub_first_neg_param_test) {
  printf("Sub test 6\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 2, &matrix1);
  matrix1.columns = -1;
  s21_create_matrix(2, 2, &matrix2);
  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result),
                   INCORRECT_MATRIX);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

START_TEST(s21_sub_second_neg_params_test) {
  printf("Sub test 7\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(1, 2, &matrix2);
  matrix2.columns = -1;
  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result),
                   INCORRECT_MATRIX);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

// mult_number
START_TEST(s21_mult_number_good_test) {
  printf("mult_number test 1\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &test_result);
  double count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      test_result.matrix[y][x] = count * 2;
      count++;
    }
  }
  printf("matrix * 2\n");
  ck_assert_int_eq(s21_mult_number(&matrix1, 2, &result), OK);
  printf("Result \n");
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_mult_number_null_matrix_test) {
  printf("mult_number test 2\n");
  matrix_t result = {0};
  ck_assert_int_eq(s21_mult_number(NULL, 2, &result), INCORRECT_MATRIX);
}

END_TEST

START_TEST(s21_mult_number_neg_param_test) {
  printf("mult_number test 3\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 2, &matrix1);
  matrix1.columns = -1;
  ck_assert_int_eq(s21_mult_number(&matrix1, 2, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&matrix1);
}

END_TEST

START_TEST(s21_mult_number_good_neg_number_test) {
  printf("mult_number test 4\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &test_result);
  double count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      test_result.matrix[y][x] = count * (-2);
      count++;
    }
  }
  printf("matrix * -2\n");
  ck_assert_int_eq(s21_mult_number(&matrix1, -2, &result), OK);
  printf("Result \n");
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

START_TEST(s21_mult_number_good_0_number_test) {
  printf("mult_number test 5\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &test_result);
  double count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      test_result.matrix[y][x] = count * 0;
      count++;
    }
  }
  printf("matrix * 0\n");
  ck_assert_int_eq(s21_mult_number(&matrix1, 0, &result), OK);
  printf("Result \n");
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

START_TEST(s21_mult_number_good_float_test) {
  printf("mult_number test 6\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &test_result);
  double count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      test_result.matrix[y][x] = count * 1.234567;
      count++;
    }
  }
  printf("matrix * 1.234567\n");
  ck_assert_int_eq(s21_mult_number(&matrix1, 1.234567, &result), OK);
  printf("Result \n");
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

// mult_matrix
/*
             1 4    1 -1  1    9 11 17
C = A × B =  2 5  × 2  3  4 = 12 13 22
             3 6              15 15 27
 */
START_TEST(s21_mult_matrix_good_test) {
  printf("mult_matrix test 1\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(3, 2, &matrix1);
  s21_create_matrix(2, 3, &matrix2);
  s21_create_matrix(3, 3, &test_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 2;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[2][0] = 3;
  matrix1.matrix[2][1] = 6;

  matrix2.matrix[0][0] = 1;
  matrix2.matrix[0][1] = -1;
  matrix2.matrix[0][2] = 1;
  matrix2.matrix[1][0] = 2;
  matrix2.matrix[1][1] = 3;
  matrix2.matrix[1][2] = 4;

  test_result.matrix[0][0] = 9;
  test_result.matrix[0][1] = 11;
  test_result.matrix[0][2] = 17;
  test_result.matrix[1][0] = 12;
  test_result.matrix[1][1] = 13;
  test_result.matrix[1][2] = 22;
  test_result.matrix[2][0] = 15;
  test_result.matrix[2][1] = 15;
  test_result.matrix[2][2] = 27;
  printf("matrix1\n");
  printf("* matrix2\n");
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), OK);
  printf("Result matrix is \n");
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_mult_matrix_wrong_params_test) {
  printf("mult_matrix test 2\n");
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 2, &matrix1);
  s21_create_matrix(3, 2, &matrix2);
  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

END_TEST

// transpose
/*
           1 4   1 2 3
A = A^T =  2 5 = 4 5 6
           3 6
 */
START_TEST(s21_transpose_good_test) {
  printf("transpose test 1\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(3, 2, &matrix1);
  s21_create_matrix(2, 3, &test_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 2;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[2][0] = 3;
  matrix1.matrix[2][1] = 6;

  test_result.matrix[0][0] = 1;
  test_result.matrix[0][1] = 2;
  test_result.matrix[0][2] = 3;
  test_result.matrix[1][0] = 4;
  test_result.matrix[1][1] = 5;
  test_result.matrix[1][2] = 6;
  printf("Before transpose ...\n");
  ck_assert_int_eq(s21_transpose(&matrix1, &result), OK);
  printf("After transpose ...\n");
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

// calc_complements

/*
     1 2 3
A  = 0 4 2
     5 2 1

      0  10 -20
M. =  4 -14   8
     -8  -2   4
 */
START_TEST(s21_calc_complements_good_test) {
  printf("calc_complements test 1\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &test_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = 2;
  matrix1.matrix[2][2] = 1;

  test_result.matrix[0][0] = 0;
  test_result.matrix[0][1] = 10;
  test_result.matrix[0][2] = -20;
  test_result.matrix[1][0] = 4;
  test_result.matrix[1][1] = -14;
  test_result.matrix[1][2] = 8;
  test_result.matrix[2][0] = -8;
  test_result.matrix[2][1] = -2;
  test_result.matrix[2][2] = 4;
  printf("For matrix \n");
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), OK);
  printf("Component's matrix is \n");
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_calc_complements_1_size_test) {
  printf("calc_complements test 2\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &matrix1);

  matrix1.matrix[0][0] = 1;
  printf("For matrix \n");
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(s21_calc_complements_2_size_test) {
  printf("calc_complements test 3\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &test_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;

  test_result.matrix[0][0] = 4;
  test_result.matrix[0][1] = 0;
  test_result.matrix[1][0] = -2;
  test_result.matrix[1][1] = 1;
  printf("For matrix \n");
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), OK);
  printf("Component's matrix is \n");
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_calc_complements_4_size_test) {
  printf("calc_complements test 4\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(4, 4, &matrix1);
  s21_create_matrix(4, 4, &test_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[0][3] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  matrix1.matrix[1][3] = 2;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = 2;
  matrix1.matrix[2][2] = 1;
  matrix1.matrix[2][3] = 1;
  matrix1.matrix[3][0] = 1;
  matrix1.matrix[3][1] = 2;
  matrix1.matrix[3][2] = 3;
  matrix1.matrix[3][3] = 4;

  test_result.matrix[0][0] = 0;
  test_result.matrix[0][1] = 10;
  test_result.matrix[0][2] = -60;
  test_result.matrix[0][3] = 40;
  test_result.matrix[1][0] = 4;
  test_result.matrix[1][1] = -14;
  test_result.matrix[1][2] = 8;
  test_result.matrix[1][3] = 0;
  test_result.matrix[2][0] = -8;
  test_result.matrix[2][1] = -2;
  test_result.matrix[2][2] = 4;
  test_result.matrix[2][3] = 0;
  test_result.matrix[3][0] = 0;
  test_result.matrix[3][1] = 0;
  test_result.matrix[3][2] = 40;
  test_result.matrix[3][3] = -40;
  printf("For matrix \n");
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), OK);
  printf("Component's matrix is \n");
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_calc_dif_row_col_test) {
  printf("calc_complements test 5\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 3, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  ck_assert_int_eq(s21_calc_complements(&matrix1, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}

END_TEST

// determinant

/*
     1 2 3
A =  4 5 6
     7 8 9
 */
START_TEST(s21_determinant_good_test) {
  printf("determinant test 1\n");
  matrix_t matrix1 = {0};
  s21_create_matrix(3, 3, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[1][2] = 6;
  matrix1.matrix[2][0] = 7;
  matrix1.matrix[2][1] = 8;
  matrix1.matrix[2][2] = 9;

  double determinant = 0;
  printf("For matrix \n");
  int status = s21_determinant(&matrix1, &determinant);
  ck_assert_ldouble_eq_tol(determinant, 0, EPS);
  ck_assert_int_eq(status, OK);
  printf("Determinant is %lf", determinant);
  s21_remove_matrix(&matrix1);
}

END_TEST

START_TEST(s21_determinant_1_size_test) {
  printf("determinant test 2\n");
  matrix_t matrix1 = {0};
  s21_create_matrix(1, 1, &matrix1);

  matrix1.matrix[0][0] = 10;

  double determinant = 0;
  printf("For matrix \n");
  int status = s21_determinant(&matrix1, &determinant);
  ck_assert_ldouble_eq_tol(determinant, 10, EPS);
  ck_assert_int_eq(status, OK);
  printf("Determinant is %lf", determinant);
  s21_remove_matrix(&matrix1);
}

END_TEST

START_TEST(s21_determinant_2_size_test) {
  printf("determinant test 3\n");
  matrix_t matrix1 = {0};
  s21_create_matrix(2, 2, &matrix1);

  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 2;
  matrix1.matrix[1][1] = 5;

  double determinant = 0;
  printf("For matrix \n");
  int status = s21_determinant(&matrix1, &determinant);
  ck_assert_ldouble_eq_tol(determinant, 7, EPS);
  ck_assert_int_eq(status, OK);
  printf("Determinant is %lf", determinant);
  s21_remove_matrix(&matrix1);
}

END_TEST

START_TEST(s21_determinant_4_size_test) {
  printf("determinant test 4\n");
  matrix_t matrix1 = {0};
  s21_create_matrix(4, 4, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 5;
  matrix1.matrix[0][2] = 6;
  matrix1.matrix[0][3] = 7;
  matrix1.matrix[1][0] = -3;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 6;
  matrix1.matrix[1][3] = 7;
  matrix1.matrix[2][0] = 9;
  matrix1.matrix[2][1] = 10;
  matrix1.matrix[2][2] = 24;
  matrix1.matrix[2][3] = 8;
  matrix1.matrix[3][0] = -5;
  matrix1.matrix[3][1] = 8;
  matrix1.matrix[3][2] = 4;
  matrix1.matrix[3][3] = 5;

  double determinant = 0;
  printf("For matrix \n");
  int status = s21_determinant(&matrix1, &determinant);
  ck_assert_ldouble_eq_tol(determinant, -2830, EPS);
  ck_assert_int_eq(status, OK);
  printf("Determinant is %lf", determinant);
  s21_remove_matrix(&matrix1);
}

END_TEST

START_TEST(s21_determinant_dif_row_col_test) {
  printf("determinant test 5\n");
  matrix_t matrix1 = {0};
  s21_create_matrix(2, 3, &matrix1);
  double det = 0;

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  ck_assert_int_eq(s21_determinant(&matrix1, &det), CALC_ERROR);
  s21_remove_matrix(&matrix1);
}

END_TEST

// inverse_matrix
/*
      2  5  7
A =   6  3  4
      5 -2 -3

                                 1  -1   1
A^(-1) =  1/|A| * M^T.       = -38  41 -34
                                27 -29  24
 */

START_TEST(s21_inverse_matrix_good_test) {
  printf("inverse_matrix test 1\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &test_result);

  matrix1.matrix[0][0] = 2;
  matrix1.matrix[0][1] = 5;
  matrix1.matrix[0][2] = 7;
  matrix1.matrix[1][0] = 6;
  matrix1.matrix[1][1] = 3;
  matrix1.matrix[1][2] = 4;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = -2;
  matrix1.matrix[2][2] = -3;

  test_result.matrix[0][0] = 1;
  test_result.matrix[0][1] = -1;
  test_result.matrix[0][2] = 1;
  test_result.matrix[1][0] = -38;
  test_result.matrix[1][1] = 41;
  test_result.matrix[1][2] = -34;
  test_result.matrix[2][0] = 27;
  test_result.matrix[2][1] = -29;
  test_result.matrix[2][2] = 24;
  printf("For matrix \n");
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), OK);
  printf("Inverse matrix is \n");
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_inverse_matrix_1_size_test) {
  printf("inverse_matrix test 2\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(1, 1, &matrix1);
  s21_create_matrix(1, 1, &test_result);

  matrix1.matrix[0][0] = 5;

  test_result.matrix[0][0] = 0.2;
  printf("For matrix \n");
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), OK);
  printf("Inverse matrix is \n");
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_inverse_matrix_2_size_test) {
  printf("inverse_matrix test 3\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &test_result);

  matrix1.matrix[0][0] = 2;
  matrix1.matrix[0][1] = 7;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = -6;

  test_result.matrix[0][0] = 0.15;
  test_result.matrix[0][1] = 0.175;
  test_result.matrix[1][0] = 0.1;
  test_result.matrix[1][1] = -0.05;
  printf("For matrix \n");
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), OK);
  printf("Inverse matrix is \n");
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

START_TEST(s21_inverse_matrix_4_size_test) {
  printf("inverse_matrix test 4\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(4, 4, &matrix1);
  s21_create_matrix(4, 4, &test_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[0][3] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  matrix1.matrix[1][3] = 2;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = 2;
  matrix1.matrix[2][2] = 1;
  matrix1.matrix[2][3] = 1;
  matrix1.matrix[3][0] = 1;
  matrix1.matrix[3][1] = 2;
  matrix1.matrix[3][2] = 3;
  matrix1.matrix[3][3] = 4;

  test_result.matrix[0][0] = 0;
  test_result.matrix[0][1] = -0.1;
  test_result.matrix[0][2] = 0.2;
  test_result.matrix[0][3] = 0;
  test_result.matrix[1][0] = -0.25;
  test_result.matrix[1][1] = 0.35;
  test_result.matrix[1][2] = 0.05;
  test_result.matrix[1][3] = 0;
  test_result.matrix[2][0] = 1.5;
  test_result.matrix[2][1] = -0.2;
  test_result.matrix[2][2] = -0.1;
  test_result.matrix[2][3] = -1;
  test_result.matrix[3][0] = -1;
  test_result.matrix[3][1] = 0;
  test_result.matrix[3][2] = 0;
  test_result.matrix[3][3] = 1;
  printf("For matrix \n");
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), OK);
  printf("Inverse matrix is \n");
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPS);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(s21_inverse_determ_0_test) {
  printf("inverse_matrix test 5\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[1][2] = 6;
  matrix1.matrix[2][0] = 7;
  matrix1.matrix[2][1] = 8;
  matrix1.matrix[2][2] = 9;

  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), CALC_ERROR);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(s21_inverse_matrix_dif_row_col_test) {
  printf("inverse_matrix test 6\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 3, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(s21_inverse_matrix_1_size_0_test) {
  printf("inverse_matrix test 7\n");
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &matrix1);

  matrix1.matrix[0][0] = 0;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(test_one_by_one) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    m.matrix[0][0] = 5;
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(result.matrix[0][0] == (1.0 / m.matrix[0][0]), 1);
    ck_assert_int_eq(code, OK);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

int main(void) {
  setlocale(LC_ALL, "");
  int number_failed;
  Suite *s = suite_create("s21_matrix");

  TCase *s21_matrix_h = tcase_create("s21_matrix_h");
  SRunner *sr = srunner_create(s);

  suite_add_tcase(s, s21_matrix_h);

  // create and remove
  tcase_add_test(s21_matrix_h, s21_create_remove_good_test);
  tcase_add_test(s21_matrix_h, s21_create_wrong_row_test);
  tcase_add_test(s21_matrix_h, s21_create_wrong_col_test);
  tcase_add_test(s21_matrix_h, s21_create_wrong_row_col_test);
  tcase_add_test(s21_matrix_h, s21_create_nul_params_test);
  tcase_add_test(s21_matrix_h, s21_create_null_matrix_test);

  // eq_matrix
  tcase_add_test(s21_matrix_h, s21_eq_good_test);
  tcase_add_test(s21_matrix_h, s21_eq_diff_row_params_test);
  tcase_add_test(s21_matrix_h, s21_eq_diff_col_params_test);
  tcase_add_test(s21_matrix_h, s21_eq_negat_params_test);
  tcase_add_test(s21_matrix_h, s21_eq_diff_ceil_test);

  // sum
  tcase_add_test(s21_matrix_h, s21_sum_good_test);
  tcase_add_test(s21_matrix_h, s21_sum_diff_row_params_test);
  tcase_add_test(s21_matrix_h, s21_sum_diff_col_params_test);
  tcase_add_test(s21_matrix_h, s21_sum_first_null_matrix_test);
  tcase_add_test(s21_matrix_h, s21_sum_second_null_matrix_test);
  tcase_add_test(s21_matrix_h, s21_sum_first_neg_param_test);
  tcase_add_test(s21_matrix_h, s21_sum_second_neg_params_test);

  // sub
  tcase_add_test(s21_matrix_h, s21_sub_good_test);
  tcase_add_test(s21_matrix_h, s21_sub_diff_row_params_test);
  tcase_add_test(s21_matrix_h, s21_sub_diff_col_params_test);
  tcase_add_test(s21_matrix_h, s21_sub_first_null_matrix_test);
  tcase_add_test(s21_matrix_h, s21_sub_second_null_matrix_test);
  tcase_add_test(s21_matrix_h, s21_sub_first_neg_param_test);
  tcase_add_test(s21_matrix_h, s21_sub_second_neg_params_test);

  // mult_number
  tcase_add_test(s21_matrix_h, s21_mult_number_good_test);
  tcase_add_test(s21_matrix_h, s21_mult_number_null_matrix_test);
  tcase_add_test(s21_matrix_h, s21_mult_number_neg_param_test);
  tcase_add_test(s21_matrix_h, s21_mult_number_good_neg_number_test);
  tcase_add_test(s21_matrix_h, s21_mult_number_good_0_number_test);
  tcase_add_test(s21_matrix_h, s21_mult_number_good_float_test);

  // mult_matrix
  tcase_add_test(s21_matrix_h, s21_mult_matrix_good_test);
  tcase_add_test(s21_matrix_h, s21_mult_matrix_wrong_params_test);

  // transpose
  tcase_add_test(s21_matrix_h, s21_transpose_good_test);

  // calc_complements
  tcase_add_test(s21_matrix_h, s21_calc_complements_good_test);
  tcase_add_test(s21_matrix_h, s21_calc_complements_1_size_test);
  tcase_add_test(s21_matrix_h, s21_calc_complements_2_size_test);
  tcase_add_test(s21_matrix_h, s21_calc_complements_4_size_test);
  tcase_add_test(s21_matrix_h, s21_calc_dif_row_col_test);

  // determinant
  tcase_add_test(s21_matrix_h, s21_determinant_good_test);
  tcase_add_test(s21_matrix_h, s21_determinant_1_size_test);
  tcase_add_test(s21_matrix_h, s21_determinant_2_size_test);
  tcase_add_test(s21_matrix_h, s21_determinant_4_size_test);
  tcase_add_test(s21_matrix_h, s21_determinant_dif_row_col_test);

  // inverse_matrix
  tcase_add_test(s21_matrix_h, s21_inverse_matrix_good_test);
  tcase_add_test(s21_matrix_h, s21_inverse_matrix_1_size_test);
  tcase_add_test(s21_matrix_h, s21_inverse_matrix_2_size_test);
  tcase_add_test(s21_matrix_h, s21_inverse_matrix_4_size_test);
  tcase_add_test(s21_matrix_h, s21_inverse_determ_0_test);
  tcase_add_test(s21_matrix_h, s21_inverse_matrix_dif_row_col_test);
  tcase_add_test(s21_matrix_h, s21_inverse_matrix_1_size_0_test);
  tcase_add_test(s21_matrix_h, test_one_by_one);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
