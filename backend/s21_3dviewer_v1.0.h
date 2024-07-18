#ifndef _SRC_BACKEND_
#define _SRC_BACKEND_

#define OK 0;
#define ERROR 1;
#define ERROR_NEGATIV_VALUE 2;
#define FILE_ERROR 3;
#define ERROR_FUNCTION_POINTER 4;
#define ERROR_VERTEXS 5;  // Вершины
#define ERROR_FACETS 6;   // Поверхности

#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "./matrix/s21_matrix.h"

typedef struct Data {
  unsigned long long count_of_vertexes;
  unsigned long long count_of_facets;
  matrix_t VERTEXES;
  int *facets;
  double max_x, max_y, min_x, min_y;
  int cout_arg;
} count_of_elements;

// ОСНОВНАЯ ФУНКЦИЯ //
/**
 * @brief Основная функция;
 * @param file Путь до файла;
 * @return 0 - Успешно
 *         3 - Ошибка открытия файла
 */
int view(char *file, count_of_elements *DATA);

// ОТКРЫТИЕ ФАЙЛА //
/**
 * @brief Эта функция открывает файл;
 * @param file Указатель на поток данных;
 * @param log Данные для log файла;
 * @param 0 - Успешно
 *        3 - Ошибка открытия файла
 */
int open_file(FILE **fp, char *file);

// ПОДСЧЕТ КОЛИЧЕСТВ ВЕРШИН И ГРАНЕЙ //
/**
 * @brief Эта функция считае количество верши и граней;
 * @param fp Указатель на поток данных;
 * @param DATA Указатель на структуру (количество элементов)
 * @param flag 0 - Считает количество элементов
 *             1 - Записывает элементы в массив
 * @param FACETS Массив точек
 * @param VERTEXES Массив поверхностей
 * @param max_arg Указатель на максимальное количество точек полигона для
 * выделения памяти
 */
void element_counting(FILE **fp, count_of_elements *DATA, int flag,
                      int *max_arg, int *flag_error, int *index);

// ПРОВЕРКА АРГУМЕНТОВ ВЕРШИН //
/**
 * @brief Эта функция проверяет первые три аргумента вершины;
 * @param str Указатель на строку;
 * @param i Номер элемента массива
 * @param length_str Длина строки
 * @return 0 - ОК
 *         1 - ERORRO
 */
int check_argument_facets(char *str, unsigned long long *i);

// ПРОВЕРКА АРГУМЕНТОВ ПОВЕРХНОСТЕЙ //
/**
 * @brief Эта функция проверяет первые три аргумента поверхностей;
 * @param str Указатель на строку;
 * @param i Номер элемента массива
 * @param length_str Длина строки
 * @param count_arg Считае количество аргументов поверхности
 * @return 0 - ОК
 *         1 - ERORRO
 */
int check_argument_vertexes(char *str, unsigned long long *i,
                            count_of_elements *DATA);

// ЗАПИСЬ ДАННЫХ В МАССИВ //
/**
 * @brief Эта функция открывает файл;
 * @param fp Указатель на поток данных;
 * @param DATA Количество вершин и поверхностей;
 * @param FACETS Массив точек
 * @param VERTEXES Массив поверхностей
 * @param max_arg Указатель на максимальное количество точек полигона для
 * выделения памяти
 */
void data_recording(FILE **fp, count_of_elements *DATA, int *flag_error,
                    int *index);

// ОБРАБОТКА ОТРИЦАТЕЛЬНЫХ ПОЛИГОНОВ//
/**
 * @brief Эта функция ишет отрицательные полигоны и преобразует;
 * @param VERTEXES Массив поверхностей
 */
void negative_vertexes(int *num, count_of_elements *DATA);

void checking_negative_values(count_of_elements *DATA, int *flag_error,
                              int *index);

void recording_counting_facets(int *flag, int *m_facets, char *str,
                               count_of_elements *DATA);
void recording_counting_vertexes(int *flag, int *max_arg, char *str,
                                 count_of_elements *DATA, int *index);

void check_argument_facets_check_arg(unsigned long long *i, int *a,
                                     int *count_dot, int *flag_result,
                                     char *str);
void check_argument_vertexes_check_arg(unsigned long long *i, int *a,
                                       int *flag_result, char *str);

// ОСНОВНАЯ ФУНКЦИЯ ЗАПИСИ КООРДИНАТ//
/**
 * @brief Эта функция записывает координаты в матрицу вершин;
 * @param str Массив чтения
 * @param i Индекс массива чтения
 * @param m Индекс столбца
 * @param DATA Структура данных
 * @param argument_counter Счетчик аргументов одной строки
 */
void data_recording_facets(char *str, int i, int m, count_of_elements *DATA);

// ЗАПИСЬ ЧИСЛА В МАССИВ//
/**
 * @brief Эта функция записывает число из строки для перевода sscanf;
 * @param str Массив чтения
 * @param str_num Массив записи
 * @param n Индекс строки матрицы
 * @param m Индекс стольбца матрицы
 * @param num Число для записи
 */
void writing_number_string_array_facets(char *str, char *str_num, int *i,
                                        int *a);

// СКАНИРОВАНИЕ СТРОКИ И ПЕРЕВОД В DOUBLE ЗНАЧЕНИЕ КООРДИНАТ//
/**
 * @brief Эта функция сканирует массив символов и переводит число в double;
 * @param DATA Структура данных
 * @param str_num Массив чтения
 * @param argument_counter Счетчик аргументов одной строки
 * @param i Индекс массива чтения
 * @param a Индекс массива записи
 */
void sscanf_number_facets(count_of_elements *DATA, char *str_num,
                          int *argument_counter, int *n, int m, double *num);

// ПОИСК МИНИМАЛЬНОГО И МАКСИМАЛЬНОГО ЗНАЧЕНИЯ oX and oY//
/**
 * @brief Эта функция ишет минмальное и максимальное значение oX and oY и
 * записывает данные в структуру;
 * @param DATA Структура данных
 * @param num Число для сравнения
 * @param n Элемент массива для сравнения
 */
void shearch_min_max_oXoY(count_of_elements *DATA, double num, int *n);

// ОСНОВНАЯ ФУНКЦИЯ ЗАПИСИ ПОВЕРХНОСТИ//
/**
 * @brief Эта функция записывает координаты в матрицу вершин;
 * @param str Массив чтения
 * @param i Индекс массива чтения
 * @param DATA Структура данных
 * @param index Индекс массива записи
 */
void data_recording_vertexes(char *str, int i, count_of_elements *DATA,
                             int *index);

// ЗАПИСЬ НОМЕРА ТОЧКИ В МАССИВ//
/**
 * @brief Эта функция записывает число из строки для перевода sscanf;
 * @param str Массив чтения
 * @param str_num Массив записи
 * @param i Индекс массиа чтения
 * @param a Индекс массиа записи
 */
void writing_number_string_array_vertexes(char *str, char *str_num, int *i,
                                          int *a);

// СКАНИРОВАНИЕ СТРОКИ И ПЕРЕВОД В DOUBLE ЗНАЧЕНИЕ НОМЕРА ТОЧКИ//
/**
 * @brief Эта функция сканирует массив символов и переводит число в int;
 * @param DATA Структура данных
 * @param str_num Массив чтения
 * @param argument_counter Счетчик аргументов одной строки
 * @param i Индекс массива чтения
 * @param a Индекс массива записи
 */
void sscanf_number_vertexes(count_of_elements *DATA, char *str_num, int *num,
                            int *num_arg, int *index);

void free_data(count_of_elements *DATA);
void norma(count_of_elements *DATA);
// АФФИННЫЕ ПРЕОБРАЗОВАНИЯ //

void move_x(matrix_t *FACETS, double a);
void move_y(matrix_t *FACETS, double a);
void move_z(matrix_t *FACETS, double a);
void rotation_by_ox(matrix_t *FACETS, double a);
void rotation_by_oy(matrix_t *FACETS, double a);
void rotation_by_oz(matrix_t *FACETS, double a);
void scaling(matrix_t *FACETS, double a);

#endif  // _SRC_BACKEND_
