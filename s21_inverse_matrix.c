#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (!norm_matrix(A)) {
    if (A->rows == A->columns) {
      matrix_t tmp = {0};
      double determinant = 0;
      s21_determinant(A, &determinant);
      if (fabs(determinant) > 1e-6) {
        if (A->rows == 1) {
          int codec = s21_create_matrix(A->rows, A->rows, result);
          if (codec == OK) result->matrix[0][0] = 1.0 / A->matrix[0][0];
        } else {
          s21_calc_complements(A, result);
          s21_transpose(result, &tmp);
          s21_remove_matrix(result);
          s21_mult_number(&tmp, 1.0 / determinant, result);
          s21_remove_matrix(&tmp);
        }
      } else {
        res = CALC_ERROR;
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}