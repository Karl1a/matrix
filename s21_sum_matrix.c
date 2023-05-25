#include "s21_matrix.h"

//сложение
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (!norm_matrix(A) && !norm_matrix(B)) {
    if (is_eq(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int x = 0; x < A->rows; x++) {
        for (int y = 0; y < A->columns; y++)
          result->matrix[x][y] = A->matrix[x][y] + B->matrix[x][y];
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}