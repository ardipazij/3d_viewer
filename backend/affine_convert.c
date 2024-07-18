#include "s21_3dviewer_v1.0.h"

void move_x(matrix_t *VERTEXS, double a) {
  for (int i = 1; i < VERTEXS->columns; i++) VERTEXS->matrix[0][i] += a;
}
void move_y(matrix_t *VERTEXS, double a) {
  for (int i = 1; i < VERTEXS->columns; i++) VERTEXS->matrix[1][i] += a;
}
void move_z(matrix_t *VERTEXS, double a) {
  for (int i = 1; i < VERTEXS->columns; i++) VERTEXS->matrix[2][i] += a;
}

void rotation_by_ox(matrix_t *VERTEXS, double a) {
  double rad = (a * M_PI) / 180;

  for (int i = 1; i < VERTEXS->columns; i++) {
    double Y = VERTEXS->matrix[1][i];
    VERTEXS->matrix[1][i] = Y * cos(rad) + VERTEXS->matrix[2][i] * sin(rad);
    VERTEXS->matrix[2][i] =
        (-1) * Y * sin(rad) + VERTEXS->matrix[2][i] * cos(rad);
  }
}
void rotation_by_oy(matrix_t *VERTEXS, double a) {
  double rad = (a * M_PI) / 180;
  for (int i = 1; i < VERTEXS->columns; i++) {
    double X = VERTEXS->matrix[0][i];
    VERTEXS->matrix[0][i] = X * cos(rad) + VERTEXS->matrix[2][i] * sin(rad);
    VERTEXS->matrix[2][i] =
        (-1) * X * sin(rad) + VERTEXS->matrix[2][i] * cos(rad);
  }
}

void rotation_by_oz(matrix_t *VERTEXS, double a) {
  double rad = (a * M_PI) / 180;
  for (int i = 1; i < VERTEXS->columns; i++) {
    double X = VERTEXS->matrix[0][i];
    VERTEXS->matrix[0][i] = X * cos(rad) + VERTEXS->matrix[1][i] * sin(rad);
    VERTEXS->matrix[1][i] =
        (-1) * X * sin(rad) + VERTEXS->matrix[1][i] * cos(rad);
  }
}
void scaling(matrix_t *VERTEXS, double a) {
  if (a == 0) a = 1;
  for (int i = 1; i < VERTEXS->columns; i++) {
    VERTEXS->matrix[0][i] *= a;
    VERTEXS->matrix[1][i] *= a;
    VERTEXS->matrix[2][i] *= a;
  }
}