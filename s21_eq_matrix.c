#include "s21_matrix.h"

//сравнение

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (!norm_matrix(A) && !norm_matrix(B)) {
    if (is_eq(A, B)) {
      for (int x = 0; x < A->rows; x += 1) {
        for (int y = 0; y < A->columns; y += 1) {
          if (fabs(A->matrix[x][y] - B->matrix[x][y]) > 1e-07) res = FAILURE;
        }
      }
    } else {
      res = FAILURE;
    }
  } else {
    res = FAILURE;
  }
  return res;
}
