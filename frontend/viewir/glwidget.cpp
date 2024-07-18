#include "glwidget.h"

#include <QDebug>
void glwidget::opana() { qDebug() << "opana"; }

glwidget::glwidget(QWidget *parent) : QOpenGLWidget(parent) {}

void glwidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}
void glwidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

// переработать
void glwidget::set_projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  normalize();
  if (type_projection) {
    glOrtho(-80, 80, -80, 80, 2.5, 999999);
  } else {
    glFrustum(-2.5, 2.5, -2.5, 2.5, 2.5, 999999);  // заменить на динамику
  }
  glTranslatef(0, -1, -100);
}
void glwidget::paintGL() {
  glClearColor(background_color.red / 255, background_color.green / 255,
               background_color.blue / 255, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  set_projection();
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  draw_model();
}
void glwidget::normalize() {
  if (reshape()) {
    for (int i = 0; i < (data.VERTEXES.columns * data.VERTEXES.rows - 4); i++) {
      if ((ver_array[i]) > normalize_value) {
        normalize_value = abs(ver_array[i]);
      }
    }
    remove_vertex_array(&ver_array);
  }
}

void glwidget::draw_model() {
  int is_memory_exist = reshape();
  if (is_memory_exist) {
    glVertexPointer(4, GL_FLOAT, 0, ver_array);
    if (is_point_exist) draw_points();
    if (is_line_exist) draw_lines();
    remove_vertex_array(&ver_array);
    ver_array = nullptr;
  }
}

void glwidget::draw_points() {
  glPointSize(point_size);
  glColor3d(point_color.red / 255, point_color.green / 255,
            point_color.blue / 255);
  glEnableClientState(GL_VERTEX_ARRAY);
  vertex_type_view();
  glDrawArrays(GL_POINTS, 0, data.count_of_vertexes);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glwidget::draw_lines() {
  glLineWidth(line_size);
  glColor3d(lines_color.red / 255, lines_color.green / 255,
            lines_color.blue / 255);
  glEnableClientState(GL_VERTEX_ARRAY);
  line_type_view();

  glDrawElements(GL_LINES, data.cout_arg, GL_UNSIGNED_INT, data.facets);
  glDisableClientState(GL_VERTEX_ARRAY);
}

int glwidget::reshape() {
  ver_array = new float[data.count_of_vertexes * 4]();
  if (ver_array == nullptr) return 0;
  int index = 0;
  for (int j = 1; j < data.VERTEXES.columns; j++) {
    for (int i = 0; i < data.VERTEXES.rows; i++) {
      ver_array[index] = data.VERTEXES.matrix[i][j];
      index += 1;
    }
  }
  return 1;
}

void glwidget::remove_vertex_array(float **ver_array) { delete[](*ver_array); }

void glwidget::line_type_view() {
  if (type_line_view) {
    if (glIsEnabled(GL_LINE_STIPPLE)) glDisable(GL_LINE_STIPPLE);
  } else {
    if (!glIsEnabled(GL_LINE_STIPPLE)) {
      glEnable(GL_LINE_STIPPLE);
    }
    glLineStipple(1, 15);
  }
}
void glwidget::vertex_type_view() {
  if (type_vertex_view) {
    if (glIsEnabled(GL_POINT_SMOOTH)) glDisable(GL_POINT_SMOOTH);
  } else {
    if (!glIsEnabled(GL_POINT_SMOOTH)) glEnable(GL_POINT_SMOOTH);
  }
}

void glwidget::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void glwidget::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void glwidget::reset_settings() {
  free_data(&data);
  if (ver_array != nullptr) {
    delete[] ver_array;
  }
}
