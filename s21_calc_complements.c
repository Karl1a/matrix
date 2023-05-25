#include "s21_matrix.h"

//вычисление матрицы алгребраический дополнений

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  result->columns = A->columns;
  int res = norm_matrix(A);
  if (!res) {
    if (A->columns != A->rows)
      res = CALC_ERROR;
    else {
      res = s21_create_matrix(A->rows, A->columns, result);
      if (A->rows != 1) {
        int sign = 0;
        matrix_t temp = {0};
        s21_create_matrix(A->rows, A->rows, &temp);
        for (int x = 0; x < A->rows; x += 1) {
          for (int y = 0; y < A->columns; y += 1) {
            Minor(A->matrix, temp.matrix, x, y, A->rows);
            sign = ((x + y) % 2 == 0) ? 1 : (-1);
            result->matrix[x][y] = sign * calculate_det(&temp, A->rows - 1);
          }
        }
        s21_remove_matrix(&temp);
      } else {
        res = CALC_ERROR;
      }
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}
