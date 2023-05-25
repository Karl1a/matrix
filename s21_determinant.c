#include "s21_matrix.h"

//вычисление определителя

int s21_determinant(matrix_t *A, double *result) {
  *result = 0;
  int res = OK;
  if (norm_matrix(A)) res = FAIL;
  if (A->columns != A->rows) res = FAIL_MATRIX;

  if (A->rows == 1)
    *result = A->matrix[0][0];
  else
    *result = calculate_det(A, A->rows);
  return res;
}