#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum {
  OK = 0,
  INCORRECT_MATRIX = 1,
  CALC_ERROR = 2,
};
#define FAIL 1
#define FAIL_MATRIX 2

#define SUCCESS 1
#define FAILURE 0

#define EPS 1e-6

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void Minor(double **A, double **temp, int row, int col, int A_row);
int is_eq(matrix_t *A, matrix_t *B);
int norm_matrix(matrix_t *A);
void print_matrix(matrix_t *A);
double calculate_det(matrix_t *A, int size);
void res_null(matrix_t *result);

#endif  // SRC_S21_MATRIX_H_