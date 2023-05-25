#include "s21_matrix.h"

//умножение на число

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = norm_matrix(A);
  if (res == 0) {
    res_null(result);
    s21_create_matrix(A->rows, A->columns, result);
    for (int x = 0; x < A->rows; x += 1) {
      for (int y = 0; y < A->columns; y += 1)
        result->matrix[x][y] = A->matrix[x][y] * number;
    }
  }
  return res;
}