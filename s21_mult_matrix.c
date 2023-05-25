#include "s21_matrix.h"

//умножение

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (!norm_matrix(A) && !norm_matrix(B)) {
    if (A->columns == B->rows) {
      // res_null(result);
      res = s21_create_matrix(A->rows, B->columns, result);
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; ++j) {
            for (int k = 0; k < B->rows; ++k) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}