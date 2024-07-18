#include "s21_3dviewer_v1.0.h"

int view(char *file, count_of_elements *DATA) {
  if (DATA == NULL) return ERROR_FUNCTION_POINTER;
  FILE *fp;
  int flag_error = OK int max_arg = 0, index = 0;
  if ((flag_error = open_file(&fp, file)) != 0) flag_error = FILE_ERROR;
  {
    element_counting(&fp, DATA, 0, &max_arg, &flag_error, &index);
    fclose(fp);
  }
  if ((flag_error = open_file(&fp, file)) != 0 && flag_error == 0)
    flag_error = FILE_ERROR;
  {
    data_recording(&fp, DATA, &flag_error, &index);

    norma(DATA);

    fclose(fp);
  }
  checking_negative_values(DATA, &flag_error, &index);
  return flag_error;
}

int open_file(FILE **fp, char *file) {
  int flag_error = OK;
  if ((*fp = fopen(file, "r")) == NULL) flag_error = ERROR;
  return flag_error;
}

void element_counting(FILE **fp, count_of_elements *DATA, int flag,
                      int *max_arg, int *flag_error, int *index) {
  char str[4096] = {0};
  int m_facets = 0;
  // Проверка аргументов вершин
  while (fgets(str, 4096, *fp) != NULL) {
    unsigned long long length_str = strlen(str), i = 0;
    while ((i < length_str) && str[i] == ' ') i = i + 1;
    // Проверка вершин
    if (i < length_str && length_str > 2 && str[i] == 'v' &&
        str[i + 1] == ' ') {
      i = i + 1;
      if (check_argument_facets(str, &i) == 0)
        recording_counting_facets(&flag, &m_facets, str, DATA);
      else
        *flag_error = ERROR_VERTEXS;

    }
    // Проверка граней
    else if (i < length_str && length_str > 2 && str[i] == 'f' &&
             str[i + 1] == ' ') {
      i = i + 1;
      if (check_argument_vertexes(str, &i, DATA) == 0)
        recording_counting_vertexes(&flag, max_arg, str, DATA, index);
      else
        *flag_error = ERROR_FACETS;
    }
  }
}

int check_argument_facets(char *str, unsigned long long *i) {
  int a = 0, flag_result = OK;
  while (str[(*i)] == ' ') {
    int count_dot = 0;
    while (str[(*i)] == ' ') *i = *i + 1;
    if ((a < 3 && str[(*i)] == '-') ||
        ((str[(*i)] > 47 && str[(*i)] < 58) || str[(*i)] == 46))
      check_argument_facets_check_arg(i, &a, &count_dot, &flag_result, str);
  }
  if (!((a == 3 || a == 4) &&
        (str[(*i)] == ' ' || str[(*i)] == '\n' || str[(*i)] == '\0' ||
         str[(*i)] == 10 || str[(*i)] == 13) &&
        flag_result == 0))
    flag_result = 1;
  return flag_result;
}

int check_argument_vertexes(char *str, unsigned long long *i,
                            count_of_elements *DATA) {
  int flag_result = 0, a = 0, flag_exit = 0;
  while (str[*i] == ' ' && flag_exit == 0)
    check_argument_vertexes_check_arg(i, &a, &flag_result, str);
  if ((a > 0) &&
      (str[*i] == ' ' || str[*i] == '\n' || str[*i] == '\0' || str[*i] == 10 ||
       str[(*i)] == 13) &&
      flag_result == 0)
    DATA->cout_arg += a;
  else
    flag_result = 1;
  return flag_result;
}

void recording_counting_facets(int *flag, int *m_facets, char *str,
                               count_of_elements *DATA) {
  if (*flag == 1) {
    *m_facets = *m_facets + 1;
    data_recording_facets(str, 1, *m_facets, DATA);
  } else
    DATA->count_of_vertexes = DATA->count_of_vertexes + 1;
}

void recording_counting_vertexes(int *flag, int *max_arg, char *str,
                                 count_of_elements *DATA, int *index) {
  if (*flag == 1) {
    data_recording_vertexes(str, 1, DATA, index);
  } else {
    *max_arg = (DATA->cout_arg > *max_arg) ? DATA->cout_arg : *max_arg;
    DATA->count_of_facets = DATA->count_of_facets + 1;
  }
}

void check_argument_facets_check_arg(unsigned long long *i, int *a,
                                     int *count_dot, int *flag_result,
                                     char *str) {
  if (str[(*i)] == '-') *i = *i + 1;
  while (((str[(*i)] > 47 && str[(*i)] < 58) || str[(*i)] == 46) &&
         *flag_result == 0) {
    if (str[(*i)] == 46) *count_dot = *count_dot + 1;
    if (*count_dot == 0 || *count_dot == 1) {
      if (str[(*i) + 1] == ' ' || str[(*i) + 1] == '\0' ||
          str[(*i) + 1] == '\0' || str[(*i) + 1] == 10 || str[(*i) + 1] == 13) {
        *a = *a + 1;
      }
      *i = *i + 1;
    } else
      *flag_result = 1;
  }
}

void check_argument_vertexes_check_arg(unsigned long long *i, int *a,
                                       int *flag_result, char *str) {
  int number_slesh = 0;
  while (str[*i] == ' ') *i = *i + 1;
  while (((str[*i] > 47 && str[*i] < 58) || str[*i] == 47 || str[*i] == '-') &&
         *flag_result == 0) {
    if (str[*i] == '-') *i = *i + 1;
    if (str[*i] == 47) number_slesh = number_slesh + 1;
    if (number_slesh > 2) *flag_result = 1;
    if (str[*i + 1] == ' ' || str[*i + 1] == '\n' || str[*i + 1] == '\0' ||
        str[*i + 1] == 10 || str[(*i) + 1] == 13)
      *a = *a + 1;
    *i = *i + 1;
  }
}

void data_recording(FILE **fp, count_of_elements *DATA, int *flag_error,
                    int *index) {
  int f = 0;
  DATA->facets = malloc((DATA->cout_arg * 2) * sizeof(int));
  s21_create_matrix(4, DATA->count_of_vertexes + 1, &DATA->VERTEXES);
  element_counting(fp, DATA, 1, &f, flag_error, index);
}

void data_recording_facets(char *str, int i, int m, count_of_elements *DATA) {
  int n = 0, argument_counter = 0;
  while (str[i] == ' ') {
    int a = 0;
    char str_num[256] = {0};
    double num = 0;
    while (str[i] == ' ') i = i + 1;
    writing_number_string_array_facets(str, str_num, &i, &a);
    sscanf_number_facets(DATA, str_num, &argument_counter, &n, m, &num);
    if (argument_counter == 3) DATA->VERTEXES.matrix[3][m] = 1;
  }
}

void writing_number_string_array_facets(char *str, char *str_num, int *i,
                                        int *a) {
  while (((str[*i] > 47 && str[*i] < 58) || str[*i] == 46 || str[*i] == '-')) {
    str_num[*a] = str[*i];
    *i = *i + 1;
    *a = *a + 1;
  }
}

void sscanf_number_facets(count_of_elements *DATA, char *str_num,
                          int *argument_counter, int *n, int m, double *num) {
  if (str_num[0] != 0) {
    *argument_counter = *argument_counter + 1;
    str_num[strlen(str_num)] = '\0';
    sscanf(str_num, "%lf", num);
    DATA->VERTEXES.matrix[*n][m] = *num;
    shearch_min_max_oXoY(DATA, *num, n);
  }
}

void shearch_min_max_oXoY(count_of_elements *DATA, double num, int *n) {
  if (*n == 0) {
    DATA->max_x = (DATA->max_x < num) ? num : DATA->max_x;
    DATA->min_x = (DATA->max_x > num) ? num : DATA->min_x;
  }
  if (*n == 1) {
    DATA->min_y = (DATA->max_y > num) ? num : DATA->min_y;
    DATA->max_y = (DATA->max_y < num) ? num : DATA->max_y;
  }
  *n = *n + 1;
}

void data_recording_vertexes(char *str, int i, count_of_elements *DATA,
                             int *index) {
  int num_arg = 0, delta_index = *index;
  while (str[i] == ' ') {
    int a = 0;
    char str_num[256] = {0};
    int num = 0;
    while (str[i] == ' ') i = i + 1;
    writing_number_string_array_vertexes(str, str_num, &i, &a);
    while ((str[i] > 47 && str[i] < 58) || str[i] == '/' || str[i] == '-') {
      i = i + 1;
    }
    sscanf_number_vertexes(DATA, str_num, &num, &num_arg, index);
  }
  delta_index = *index - delta_index;
  if (num_arg > 1) {
    DATA->facets[(*index)] = DATA->facets[(*index) - (num_arg + 2)];
    *index = (*index) + 1;
  }
  if (delta_index == 1) {
    DATA->facets[(*index)] = DATA->facets[(*index) - 1];
    *index = (*index) + 1;
  }
}

void writing_number_string_array_vertexes(char *str, char *str_num, int *i,
                                          int *a) {
  while ((str[*i] > 47 && str[*i] < 58) || str[*i] == '-') {
    str_num[*a] = str[*i];
    *i = *i + 1;
    *a = *a + 1;
  }
}

void sscanf_number_vertexes(count_of_elements *DATA, char *str_num, int *num,
                            int *num_arg, int *index) {
  if (str_num[0] != 0) {
    (*num_arg)++;
    str_num[strlen(str_num)] = '\0';
    sscanf(str_num, "%d", num);
    if (*num < 0) negative_vertexes(num, DATA);
    (*num) = ((*num) == 0) ? (*num) : (*num) - 1;
    if ((*num_arg) == 1)
      DATA->facets[(*index)++] = (*num);
    else {
      DATA->facets[(*index)++] = (*num);
      DATA->facets[(*index)++] = (*num);
    }
  }
}

void negative_vertexes(int *num, count_of_elements *DATA) {
  // Узнаем количество записанных точек в данный момент
  int number_facet = 0, flag_stop = 0;
  for (int m = 0; m < DATA->VERTEXES.columns && flag_stop == 0; m++) {
    if (DATA->VERTEXES.matrix[m] == 0)
      flag_stop = 1;
    else
      number_facet = number_facet + 1;
  }
  *num = number_facet - abs(*num);
}
void checking_negative_values(count_of_elements *DATA, int *flag_error,
                              int *index) {
  for (int a = 0; a < *index; a++) {
    if (DATA->facets[a] < 0) *flag_error = ERROR_NEGATIV_VALUE;
  }
}

void free_data(count_of_elements *DATA) {
  if (DATA != NULL) {
    s21_remove_matrix(&(DATA->VERTEXES));

    if (DATA->facets != NULL) {
      free(DATA->facets);
      DATA->facets = NULL;
    }
    DATA->count_of_facets = 0;
    DATA->count_of_vertexes = 0;
    DATA->cout_arg = 0;
    DATA->max_x = 0;
    DATA->min_x = 0;
    DATA->max_y = 0;
    DATA->min_y = 0;
  }
}
void norma(count_of_elements *DATA) {
  double del_max = 0, del_x = DATA->max_x - DATA->min_x,
         del_y = DATA->max_y - DATA->min_y;
  del_max = (del_x > del_y) ? del_x : del_y;
  double keff = 45 / del_max;
  for (int i = 1; i < DATA->VERTEXES.columns; i++) {
    DATA->VERTEXES.matrix[0][i] *= keff;
    DATA->VERTEXES.matrix[1][i] *= keff;
    DATA->VERTEXES.matrix[2][i] *= keff;
  }
}
