#include "s21_matrix.h"
// opana
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows < 1 || columns < 1) return INCORRECT_MATRIX;
  int flag_error = OK;
  result->rows = rows;
  result->columns = columns;
  result->matrix = calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    flag_error = CALLOC_ERROR;
  } else {
    int is_create_columns = 0;
    for (int i = 0; i < rows && !is_create_columns; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        is_create_columns = 1;
        flag_error = CALLOC_ERROR;
      }
    }
  }
  return flag_error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}
