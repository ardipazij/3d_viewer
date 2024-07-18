#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define GL_SILENCE_DEPRICATION
#include <unistd.h>  // для Unix систем

#include <QDebug>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QPainter>
#include <QSettings>
#include <QThread>
#include <QtOpenGL>

#include "glwidget.h"
#include "qgifimage.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../../backend/s21_3dviewer_v1.0.h"
int view(char *file, count_of_elements *DATA);
#ifdef __cplusplus
}
#endif
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
  count_of_elements number_of_vertex_and_facets;

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_open_file_clicked();
  int model_load(QString filename);

  void model_load();

  void on_move_x_valueChanged(double arg1);
  void on_move_y_valueChanged(double arg1);
  void on_move_z_valueChanged(double arg1);

  void on_rotate_x_valueChanged(double arg1);
  void on_rotate_y_valueChanged(double arg1);
  void on_rotate_z_valueChanged(double arg1);

  void on_comboBox_currentIndexChanged(int index);

  void wheelEvent(QWheelEvent *event);

  void on_red_slider_valueChanged(int value);
  void on_green_slider_valueChanged(int value);
  void on_blue_slider_valueChanged(int value);

  void on_point_size_value_valueChanged(int value);
  void on_line_size_value_valueChanged(int value);

  void on_point_circle_clicked();
  void on_point_cube_clicked();

  void on_solid_button_clicked();
  void on_dashed_button_clicked();

  void on_point_is_exist_currentIndexChanged(int index);
  void on_line_is_exist_currentIndexChanged(int index);

  void save_settings();
  void upload_settings();

  void on_scale_valueChanged(double arg1);

  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

  void record_gif();
  void on_choose_view_activated(int index);

 private:
  Ui::MainWindow *ui;

  QGifImage *gif;
  QTimer *timerGIF;
  int frame;

  double prev_move_x = 0;
  double prev_move_y = 0;
  double prev_move_z = 0;

  double prev_rotate_x = 0;
  double prev_rotate_y = 0;
  double prev_rotate_z = 0;

  double prev_scale = 1;
  bool is_button_gif_pressed = false;
  QString filename, empty;
};
#endif  // MAINWINDOW_H
