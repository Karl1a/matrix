#include "s21_matrix.h"

//транспонирование

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = norm_matrix(A);
  res_null(result);
  s21_create_matrix(A->columns, A->rows, result);
  if (res == 0) {
    for (int x = 0; x < result->rows; x += 1) {
      for (int y = 0; y < result->columns; y += 1)
        result->matrix[x][y] = A->matrix[y][x];
    }
  }

  return res;
}
