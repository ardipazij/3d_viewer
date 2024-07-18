
#include <check.h>

#include "../s21_3dviewer_v1.0.h"
// char * path = "./backend/ui_test/test.obj\0";

START_TEST(s21_3d_open) {
  count_of_elements model = {0};
  char path[64] = "./backend/ui_test/test.obj\0";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);
  int data_exp = 0;
  free_data(&model);
  ck_assert_ptr_null(model.facets);
  ck_assert_int_eq(data_exp, model.max_x);
  ck_assert_int_eq(data_exp, model.min_x);
  ck_assert_int_eq(data_exp, model.max_y);
  ck_assert_int_eq(data_exp, model.min_y);
  ck_assert_int_eq(data_exp, model.cout_arg);
  ck_assert_int_eq(data_exp, model.count_of_vertexes);
}
END_TEST

START_TEST(s21_3d_open_fail_1) {
  count_of_elements model = {0};
  char path[124] = "./backend/objFiles/fail_5.obj";
  int error = view(path, &model);
  int error_expect = ERROR_NEGATIV_VALUE;
  ck_assert_int_eq(error_expect, error);
}
END_TEST

START_TEST(s21_3d_open_fail_2) {
  count_of_elements model = {0};
  char path[124] = "./backend/objFiles/fail.obj";
  int error = view(path, &model);
  int error_expect = ERROR_VERTEXS;
  ck_assert_int_eq(error_expect, error);
}
END_TEST

START_TEST(s21_3d_open_fail_3) {
  count_of_elements model = {0};
  char path[124] = "./backend/objFiles/fail_2.obj";
  int error = view(path, &model);
  int error_expect = ERROR_FACETS;
  ck_assert_int_eq(error_expect, error);
}
END_TEST

START_TEST(s21_3d_open_error_1) {
  count_of_elements *model = NULL;
  char path[64] = "./backend/ui_test/test.obj\0";
  int error = view(path, model);
  int error_expect = ERROR_FUNCTION_POINTER;
  ck_assert_int_eq(error_expect, error);
}
END_TEST

START_TEST(s21_3d_move_x_1) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = 0.00001;

  for (int i = 1; i < check_matrix.columns; i++) {
    double check_val = check_matrix.matrix[0][i];
    move_x(&(model.VERTEXES), change_val);
    double expect = check_val + change_val;
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect);
    move_x(&(model.VERTEXES), -change_val);
  }
}
END_TEST

START_TEST(s21_3d_move_x_2) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = -10000.01;

  move_x(&(model.VERTEXES), change_val);
  for (int i = 1; i < check_matrix.columns; i++) {
    double check_val = check_matrix.matrix[0][i];
    move_x(&(model.VERTEXES), change_val);
    double expect = check_val + change_val;
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect);
    move_x(&(model.VERTEXES), -change_val);
  }
}
END_TEST

START_TEST(s21_3d_move_y_1) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = 0.000001;

  for (int i = 1; i < check_matrix.columns; i++) {
    double check_val = check_matrix.matrix[1][i];
    move_y(&(model.VERTEXES), change_val);
    double expect = check_val + change_val;
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect);
    move_y(&(model.VERTEXES), -change_val);
  }
}
END_TEST

START_TEST(s21_3d_move_y_2) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = -10000.01;

  for (int i = 1; i < check_matrix.columns; i++) {
    double check_val = check_matrix.matrix[1][i];
    move_y(&(model.VERTEXES), change_val);
    double expect = check_val + change_val;
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect);
    move_y(&(model.VERTEXES), -change_val);
  }
}
END_TEST

START_TEST(s21_3d_move_z_1) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = 0.0000001;

  for (int i = 1; i < check_matrix.columns; i++) {
    double check_val = check_matrix.matrix[2][i];
    move_z(&(model.VERTEXES), change_val);
    double expect = check_val + change_val;
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect);
    move_z(&(model.VERTEXES), -change_val);
  }
}
END_TEST

START_TEST(s21_3d_move_z_2) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = -10000.01;

  for (int i = 1; i < check_matrix.columns; i++) {
    double check_val = check_matrix.matrix[2][i];
    move_z(&(model.VERTEXES), change_val);
    double expect = check_val + change_val;
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect);
    move_z(&(model.VERTEXES), -change_val);
  }
}
END_TEST

START_TEST(s21_3d_rotate_x_1) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  double change_val = 165.00;
  double angle = (change_val * M_PI) / 180;

  double expect_x[model.VERTEXES.columns];
  double expect_y[model.VERTEXES.columns];
  double expect_z[model.VERTEXES.columns];
  for (int i = 0; i < model.VERTEXES.columns; i++) {
    expect_x[i] = model.VERTEXES.matrix[0][i];
    expect_y[i] = model.VERTEXES.matrix[1][i] * cos(angle) +
                  model.VERTEXES.matrix[2][i] * sin(angle);
    expect_z[i] = (-1) * model.VERTEXES.matrix[1][i] * sin(angle) +
                  model.VERTEXES.matrix[2][i] * cos(angle);
  }
  rotation_by_ox(&(model.VERTEXES), change_val);
  for (int i = 1; i < model.VERTEXES.columns; i++) {
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect_x[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect_y[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect_z[i]);
  }
}
END_TEST

START_TEST(s21_3d_rotate_x_2) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  double change_val = 360.990;
  double angle = change_val * M_PI / 180;

  double expect_x[model.VERTEXES.columns];
  double expect_y[model.VERTEXES.columns];
  double expect_z[model.VERTEXES.columns];
  for (int i = 0; i < model.VERTEXES.columns; i++) {
    expect_x[i] = model.VERTEXES.matrix[0][i];
    expect_y[i] = model.VERTEXES.matrix[1][i] * cos(angle) +
                  model.VERTEXES.matrix[2][i] * sin(angle);
    expect_z[i] = -model.VERTEXES.matrix[1][i] * sin(angle) +
                  model.VERTEXES.matrix[2][i] * cos(angle);
  }
  rotation_by_ox(&(model.VERTEXES), change_val);
  for (int i = 1; i < model.VERTEXES.columns; i++) {
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect_x[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect_y[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect_z[i]);
  }
}
END_TEST

START_TEST(s21_3d_rotate_x_3) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  double change_val = -0.990;
  double angle = change_val * M_PI / 180;

  double expect_x[model.VERTEXES.columns];
  double expect_y[model.VERTEXES.columns];
  double expect_z[model.VERTEXES.columns];
  for (int i = 0; i < model.VERTEXES.columns; i++) {
    expect_x[i] = model.VERTEXES.matrix[0][i];
    expect_y[i] = model.VERTEXES.matrix[1][i] * cos(angle) +
                  model.VERTEXES.matrix[2][i] * sin(angle);
    expect_z[i] = -model.VERTEXES.matrix[1][i] * sin(angle) +
                  model.VERTEXES.matrix[2][i] * cos(angle);
  }
  rotation_by_ox(&(model.VERTEXES), change_val);
  for (int i = 1; i < model.VERTEXES.columns; i++) {
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect_x[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect_y[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect_z[i]);
  }
}
END_TEST

START_TEST(s21_3d_rotate_y_1) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  double change_val = 156.00;
  double angle = change_val * M_PI / 180;

  double expect_x[model.VERTEXES.columns];
  double expect_y[model.VERTEXES.columns];
  double expect_z[model.VERTEXES.columns];
  for (int i = 0; i < model.VERTEXES.columns; i++) {
    expect_x[i] = model.VERTEXES.matrix[0][i] * cos(angle) +
                  model.VERTEXES.matrix[2][i] * sin(angle);
    expect_y[i] = model.VERTEXES.matrix[1][i];
    expect_z[i] = -model.VERTEXES.matrix[0][i] * sin(angle) +
                  model.VERTEXES.matrix[2][i] * cos(angle);
  }
  rotation_by_oy(&(model.VERTEXES), change_val);
  for (int i = 1; i < model.VERTEXES.columns; i++) {
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect_x[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect_y[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect_z[i]);
  }
}
END_TEST

START_TEST(s21_3d_rotate_y_2) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  double change_val = -0.990;
  double angle = change_val * M_PI / 180;

  double expect_x[model.VERTEXES.columns];
  double expect_y[model.VERTEXES.columns];
  double expect_z[model.VERTEXES.columns];
  for (int i = 0; i < model.VERTEXES.columns; i++) {
    expect_x[i] = model.VERTEXES.matrix[0][i] * cos(angle) +
                  model.VERTEXES.matrix[2][i] * sin(angle);
    expect_y[i] = model.VERTEXES.matrix[1][i];
    expect_z[i] = -model.VERTEXES.matrix[0][i] * sin(angle) +
                  model.VERTEXES.matrix[2][i] * cos(angle);
  }
  rotation_by_oy(&(model.VERTEXES), change_val);
  for (int i = 1; i < model.VERTEXES.columns; i++) {
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect_x[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect_y[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect_z[i]);
  }
}
END_TEST

START_TEST(s21_3d_rotate_y_3) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  double change_val = 360.990;
  double angle = change_val * M_PI / 180;

  double expect_x[model.VERTEXES.columns];
  double expect_y[model.VERTEXES.columns];
  double expect_z[model.VERTEXES.columns];
  for (int i = 0; i < model.VERTEXES.columns; i++) {
    expect_x[i] = model.VERTEXES.matrix[0][i] * cos(angle) +
                  model.VERTEXES.matrix[2][i] * sin(angle);
    expect_y[i] = model.VERTEXES.matrix[1][i];
    expect_z[i] = -model.VERTEXES.matrix[0][i] * sin(angle) +
                  model.VERTEXES.matrix[2][i] * cos(angle);
  }
  rotation_by_oy(&(model.VERTEXES), change_val);
  for (int i = 1; i < model.VERTEXES.columns; i++) {
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect_x[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect_y[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect_z[i]);
  }
}
END_TEST

START_TEST(s21_3d_rotate_z_1) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  double change_val = 360.990;
  double angle = change_val * M_PI / 180;

  double expect_x[model.VERTEXES.columns];
  double expect_y[model.VERTEXES.columns];
  double expect_z[model.VERTEXES.columns];
  for (int i = 0; i < model.VERTEXES.columns; i++) {
    expect_x[i] = model.VERTEXES.matrix[0][i] * cos(angle) +
                  model.VERTEXES.matrix[1][i] * sin(angle);
    expect_y[i] = -model.VERTEXES.matrix[0][i] * sin(angle) +
                  model.VERTEXES.matrix[1][i] * cos(angle);
    expect_z[i] = model.VERTEXES.matrix[2][i];
  }
  rotation_by_oz(&(model.VERTEXES), change_val);
  for (int i = 1; i < model.VERTEXES.columns; i++) {
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect_x[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect_y[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect_z[i]);
  }
}
END_TEST

START_TEST(s21_3d_rotate_z_2) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  double change_val = 161.0;
  double angle = change_val * M_PI / 180;

  double expect_x[model.VERTEXES.columns];
  double expect_y[model.VERTEXES.columns];
  double expect_z[model.VERTEXES.columns];
  for (int i = 0; i < model.VERTEXES.columns; i++) {
    expect_x[i] = model.VERTEXES.matrix[0][i] * cos(angle) +
                  model.VERTEXES.matrix[1][i] * sin(angle);
    expect_y[i] = -model.VERTEXES.matrix[0][i] * sin(angle) +
                  model.VERTEXES.matrix[1][i] * cos(angle);
    expect_z[i] = model.VERTEXES.matrix[2][i];
  }
  rotation_by_oz(&(model.VERTEXES), change_val);
  for (int i = 1; i < model.VERTEXES.columns; i++) {
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect_x[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect_y[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect_z[i]);
  }
}
END_TEST

START_TEST(s21_3d_rotate_z_3) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  double change_val = -0.990;
  double angle = change_val * M_PI / 180;

  double expect_x[model.VERTEXES.columns];
  double expect_y[model.VERTEXES.columns];
  double expect_z[model.VERTEXES.columns];
  for (int i = 0; i < model.VERTEXES.columns; i++) {
    expect_x[i] = model.VERTEXES.matrix[0][i] * cos(angle) +
                  model.VERTEXES.matrix[1][i] * sin(angle);
    expect_y[i] = -model.VERTEXES.matrix[0][i] * sin(angle) +
                  model.VERTEXES.matrix[1][i] * cos(angle);
    expect_z[i] = model.VERTEXES.matrix[2][i];
  }
  rotation_by_oz(&(model.VERTEXES), change_val);
  for (int i = 1; i < model.VERTEXES.columns; i++) {
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect_x[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[1][i], expect_y[i]);
    ck_assert_double_eq(model.VERTEXES.matrix[2][i], expect_z[i]);
  }
}
END_TEST

START_TEST(s21_3d_scale_in_1) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = 1.001;

  for (int i = 1; i < check_matrix.columns; i++) {
    double expect = check_matrix.matrix[0][i] * change_val;
    scaling(&(model.VERTEXES), change_val);
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect);
    scaling(&(model.VERTEXES), -change_val);
  }
}
END_TEST

START_TEST(s21_3d_scale_in_2) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = 200.5;

  for (int i = 1; i < check_matrix.columns; i++) {
    double expect = check_matrix.matrix[0][i] * change_val;
    scaling(&(model.VERTEXES), change_val);
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect);
    scaling(&(model.VERTEXES), -change_val);
  }
}
END_TEST

START_TEST(s21_3d_scale_out_1) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = -200.1;

  for (int i = 1; i < check_matrix.columns; i++) {  // может некоректный тест
    double expect = check_matrix.matrix[0][i] * change_val;
    scaling(&(model.VERTEXES), change_val);
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect);
    scaling(&(model.VERTEXES), -change_val);
  }
}
END_TEST

START_TEST(s21_3d_scale_out_2) {
  count_of_elements model = {0};
  char path[124] = "./backend/ui_test/test.obj";
  int error = view(path, &model);
  int error_expect = 0;
  ck_assert_int_eq(error_expect, error);

  matrix_t check_matrix = model.VERTEXES;
  double change_val = 0.0005;

  for (int i = 1; i < check_matrix.columns; i++) {  // может некоректный тест
    double expect = check_matrix.matrix[0][i] * change_val;
    scaling(&(model.VERTEXES), change_val);
    ck_assert_double_eq(model.VERTEXES.matrix[0][i], expect);
    scaling(&(model.VERTEXES), -change_val);
  }
}
END_TEST

Suite *suite_open() {
  Suite *suite = suite_create("\033[1;30;47m S21_3D_OPEN \033[0;0;0m");
  TCase *test_case = tcase_create("\033[1;30;47m s21_3d_open \033[0;0;0m");
  suite_add_tcase(suite, test_case);

  tcase_add_test(test_case, s21_3d_open);
  tcase_add_test(test_case, s21_3d_open_fail_1);
  tcase_add_test(test_case, s21_3d_open_fail_2);
  tcase_add_test(test_case, s21_3d_open_fail_3);
  tcase_add_test(test_case, s21_3d_open_error_1);

  suite_add_tcase(suite, test_case);
  return suite;
}

Suite *suite_move() {
  Suite *suite = suite_create("\033[1;30;47m S21_3D_MOVE \033[0;0;0m");
  TCase *test_case = tcase_create("\033[1;30;47m s21_3d_move \033[0;0;0m");
  suite_add_tcase(suite, test_case);

  tcase_add_test(test_case, s21_3d_move_x_1);
  tcase_add_test(test_case, s21_3d_move_x_2);

  tcase_add_test(test_case, s21_3d_move_y_1);
  tcase_add_test(test_case, s21_3d_move_y_2);

  tcase_add_test(test_case, s21_3d_move_z_1);
  tcase_add_test(test_case, s21_3d_move_z_2);

  suite_add_tcase(suite, test_case);
  return suite;
}

Suite *suite_rotate() {
  Suite *suite = suite_create("\033[1;30;47m S21_3D_ROTATE \033[0;0;0m");
  TCase *test_case = tcase_create("\033[1;30;47m s21_3d_rotate \033[0;0;0m");
  suite_add_tcase(suite, test_case);

  tcase_add_test(test_case, s21_3d_rotate_x_1);
  tcase_add_test(test_case, s21_3d_rotate_x_2);
  tcase_add_test(test_case, s21_3d_rotate_x_3);

  tcase_add_test(test_case, s21_3d_rotate_y_1);
  tcase_add_test(test_case, s21_3d_rotate_y_2);
  tcase_add_test(test_case, s21_3d_rotate_y_3);

  tcase_add_test(test_case, s21_3d_rotate_z_1);
  tcase_add_test(test_case, s21_3d_rotate_z_2);
  tcase_add_test(test_case, s21_3d_rotate_z_3);

  suite_add_tcase(suite, test_case);
  return suite;
}

Suite *suite_scale() {
  Suite *suite = suite_create("\033[1;30;47m S21_3D_SCALE \033[0;0;0m");
  TCase *test_case = tcase_create("\033[1;30;47m s21_3d_scale \033[0;0;0m");
  suite_add_tcase(suite, test_case);

  tcase_add_test(test_case, s21_3d_scale_in_1);
  tcase_add_test(test_case, s21_3d_scale_in_2);
  // возможно некоректные тесты
  tcase_add_test(test_case, s21_3d_scale_out_1);
  tcase_add_test(test_case, s21_3d_scale_out_2);

  suite_add_tcase(suite, test_case);
  return suite;
}

void run_set(Suite *current_set) {
  SRunner *all_test = srunner_create(current_set);

  srunner_set_fork_status(all_test, CK_NOFORK);
  srunner_run_all(all_test, CK_NORMAL);

  srunner_free(all_test);
}

void test_sets() {
  Suite *sets[] = {suite_open(), suite_move(), suite_rotate(), suite_scale(),
                   NULL};

  for (Suite **current_set = sets; *current_set != NULL; current_set++) {
    run_set(*current_set);
  }
}

int main() {
  test_sets();
  return 0;
}
