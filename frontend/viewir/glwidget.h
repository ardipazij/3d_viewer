#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GL_SILENCE_DEPRECATION
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtGui>
#include <vector>
//#include <QColor>

#ifdef __cplusplus
extern "C" {
#endif
#include "../../backend/s21_3dviewer_v1.0.h"
#ifdef __cplusplus
}
#endif

class glwidget : public QOpenGLFunctions, public QOpenGLWidget {
 public:
  count_of_elements data = {0, 0, {nullptr, 0, 0}, nullptr, 0, 0, 0, 0, 0};
  float *ver_array = nullptr;
  int type_projection = 0;
  typedef struct color {
    double red;
    double green;
    double blue;
  } color;
  color point_color = {0, 255, 0};
  color lines_color = {0, 0, 255};
  color background_color = {7, 118, 160};
  double point_size = 5;
  double line_size = 5;
  short type_line_view = 1;
  short type_vertex_view = 1;
  short is_point_exist = 1;
  short is_line_exist = 1;
  int normalize_value = 0;

  void opana();
  explicit glwidget(QWidget *parent = 0);
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void draw_model();
  void set_projection();
  int reshape();
  void remove_vertex_array(float **ver_array);
  void verticleMode();
  void line_type_view();
  void vertex_type_view();
  void draw_points();
  void normalize();
  void draw_lines();
  void reset_settings();  // реализовать сброс настроек при загрузке новой
                          // модели. Предусмотреть сброс при загрузке модели
                          // сразу после запуска

 private:
  int count{};
  float xRot{}, yRot{}, zRot{};
  QPoint mPos;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif  // GLWIDGET_H
