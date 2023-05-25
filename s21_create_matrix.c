#include "s21_matrix.h"

//создание
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (!result->matrix[i]) {
          for (int j = 0; j < i; j++) free(result->matrix[j]);
          free(result->matrix);
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

int is_eq(matrix_t *A, matrix_t *B) {
  return (A->rows == B->rows && A->columns == B->columns);
}

int norm_matrix(matrix_t *A) {
  int res = OK;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    res = INCORRECT_MATRIX;
  }
  return res;
}

void Minor(double **A, double **temp, int row, int col, int A_row) {
  for (int row_1 = 0, x = 0; row_1 < A_row; row_1 += 1) {
    for (int col_1 = 0, y = 0; col_1 < A_row; col_1 += 1) {
      if (row_1 != row && col_1 != col) {
        //        printf("A: %lf\n", A[row_1][col_1]);
        temp[x][y++] = A[row_1][col_1];
        if (y == A_row - 1) {
          y = 0;
          x++;
        }
      }
    }
  }
}

void print_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      printf("%f ", A->matrix[i][j]);
    }
    printf("\n");
  }
}

double calculate_det(matrix_t *A, int A_row) {
  double result = 0;
  matrix_t temp = {0};
  s21_create_matrix(A_row, A_row, &temp);
  if (A_row == 1)
    result = A->matrix[0][0];
  else if (A_row == 2) {
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int sign = 1, x = 0; x < A_row; x += 1, sign *= (-1)) {
      Minor(A->matrix, temp.matrix, 0, x, A_row);
      result += sign * A->matrix[0][x] * calculate_det(&temp, A_row - 1);
    }
  }
  s21_remove_matrix(&temp);
  return result;
}

void res_null(matrix_t *result) {
  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;
}
