#include "mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtOpenGL>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->path_to_file_text->setText("Path to file");
  ui->rotate_x->setMaximum(360);
  ui->rotate_x->setMinimum(0);
  ui->rotate_x->setSingleStep(1);
  ui->rotate_x->setDecimals(2);

  ui->rotate_y->setMaximum(360);
  ui->rotate_y->setMinimum(0);
  ui->rotate_y->setSingleStep(1);
  ui->rotate_y->setDecimals(2);

  ui->rotate_z->setMaximum(360);
  ui->rotate_z->setMinimum(0);
  ui->rotate_z->setSingleStep(1);
  ui->rotate_z->setDecimals(2);
  upload_settings();

  ui->red_slider->setValue(ui->openGLWidget->lines_color.red);
  ui->red_value->setNum(ui->openGLWidget->lines_color.red);
  ui->green_slider->setValue(ui->openGLWidget->lines_color.green);
  ui->green_value->setNum(ui->openGLWidget->lines_color.green);
  ui->blue_slider->setValue(ui->openGLWidget->lines_color.blue);
  ui->blue_value->setNum(ui->openGLWidget->lines_color.blue);

  ui->point_size_value->setValue(ui->openGLWidget->point_size);
  ui->line_size_value->setValue(ui->openGLWidget->line_size);

  ui->solid_button->setChecked(ui->openGLWidget->type_line_view);
  ui->dashed_button->setChecked(!ui->openGLWidget->type_line_view);

  ui->point_circle->setChecked(!ui->openGLWidget->type_vertex_view);
  ui->point_cube->setChecked(ui->openGLWidget->type_vertex_view);

  ui->point_is_exist->setCurrentIndex(!ui->openGLWidget->is_point_exist);
  ui->line_is_exist->setCurrentIndex(!ui->openGLWidget->is_line_exist);

  ui->comboBox->setCurrentIndex(ui->openGLWidget->type_projection);
}

MainWindow::~MainWindow() {
  save_settings();
  ui->openGLWidget->reset_settings();
  delete ui;
}

void MainWindow::on_open_file_clicked() {
  filename = QFileDialog::getOpenFileName(this, "Open file", "/Users",
                                          "OBJ files (*.obj)");

  if (!filename.isEmpty()) {
    ui->openGLWidget->reset_settings();
    model_load(filename);
  } else {
    QMessageBox::StandardButton my = QMessageBox::question(
        this, "Can't read file", "Do you want try open other file?",
        QMessageBox::Yes | QMessageBox::No);
    if (my == QMessageBox::No) {
      model_load();

    } else
      on_open_file_clicked();
  }
}
void MainWindow::model_load() {
  ui->openGLWidget->reset_settings();
  ui->vertex_count->setText("Vertex count: file isn't exist");
  ui->facets_count->setText("Facets count: file isn't exist");
  filename = empty;
}
int MainWindow::model_load(QString filename) {
  int flag_result = SUCCESS;
  QByteArray ba = filename.toLocal8Bit();
  char *path_to_file = ba.data();
  if (!view(path_to_file, &ui->openGLWidget->data)) {
    ui->path_to_file_text->setText(filename);
    QString result_numver_of_vertex =
        QString::number(ui->openGLWidget->data.count_of_vertexes);
    ui->vertex_count->setText("Vertex count: " + result_numver_of_vertex);
    QString result_numver_of_facets =
        QString::number(ui->openGLWidget->data.count_of_facets);
    ui->facets_count->setText("Facets count: " + result_numver_of_facets);
    ui->openGLWidget->opana();
    ui->openGLWidget->update();
  } else {
    ui->openGLWidget->reset_settings();
    ui->path_to_file_text->setText("undefined value");
    ui->vertex_count->setText("Vertex count: undefined value");
    ui->facets_count->setText("Facets count: undefined value");
    flag_result = FAILURE;
  }
  return flag_result;
}

void MainWindow::on_move_x_valueChanged(double current_x) {
  double shift = current_x - prev_move_x;
  move_x(&ui->openGLWidget->data.VERTEXES, ui->speed_coeff->value() * shift);
  ui->openGLWidget->update();
  prev_move_x = current_x;
}

void MainWindow::on_move_y_valueChanged(double current_y) {
  double shift = current_y - prev_move_y;
  move_y(&ui->openGLWidget->data.VERTEXES, ui->speed_coeff->value() * shift);
  ui->openGLWidget->update();
  prev_move_y = current_y;
}

void MainWindow::on_move_z_valueChanged(double current_z) {
  double shift = current_z - prev_move_z;
  move_z(&ui->openGLWidget->data.VERTEXES, ui->speed_coeff->value() * shift);
  ui->openGLWidget->update();
  prev_move_z = current_z;
}

void MainWindow::on_rotate_z_valueChanged(double current_z) {
  double shift = current_z - prev_rotate_z;
  rotation_by_oz(&ui->openGLWidget->data.VERTEXES, shift);
  ui->openGLWidget->update();
  prev_rotate_z = current_z;
}

void MainWindow::on_rotate_y_valueChanged(double current_y) {
  double shift = current_y - prev_rotate_y;
  rotation_by_oy(&ui->openGLWidget->data.VERTEXES, shift);
  ui->openGLWidget->update();
  prev_rotate_y = current_y;
}

void MainWindow::on_rotate_x_valueChanged(double current_x) {
  double shift = current_x - prev_rotate_x;
  rotation_by_ox(&ui->openGLWidget->data.VERTEXES, shift);
  ui->openGLWidget->update();
  prev_rotate_x = current_x;
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
  ui->openGLWidget->type_projection = index;
  ui->openGLWidget->update();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0)  // up Wheel
    scaling(&ui->openGLWidget->data.VERTEXES, 1.1);
  else if (event->angleDelta().y() < 0)  // down Wheel
    scaling(&ui->openGLWidget->data.VERTEXES, 0.9);
  ui->openGLWidget->update();
}

void MainWindow::on_scale_valueChanged(double scale_count) {
  double shift = scale_count / prev_scale;
  scaling(&ui->openGLWidget->data.VERTEXES, shift);
  prev_scale = scale_count;
  ui->openGLWidget->update();
}

void MainWindow::on_red_slider_valueChanged(int value) {
  if (ui->choose_view->currentIndex() == 0)
    ui->openGLWidget->lines_color.red = value;
  else if (ui->choose_view->currentIndex() == 1)
    ui->openGLWidget->point_color.red = value;
  else if (ui->choose_view->currentIndex() == 2)
    ui->openGLWidget->background_color.red = value;
  ui->red_value->setNum(value);
  ui->openGLWidget->update();
}

void MainWindow::on_green_slider_valueChanged(int value) {
  if (ui->choose_view->currentIndex() == 0)
    ui->openGLWidget->lines_color.green = value;
  else if (ui->choose_view->currentIndex() == 1)
    ui->openGLWidget->point_color.green = value;
  else if (ui->choose_view->currentIndex() == 2)
    ui->openGLWidget->background_color.green = value;
  ui->openGLWidget->update();
  ui->green_value->setNum(value);
}

////////////////////////////////////////////////////////////
void MainWindow::on_blue_slider_valueChanged(int value) {
  if (ui->choose_view->currentIndex() == 0)
    ui->openGLWidget->lines_color.blue = value;
  else if (ui->choose_view->currentIndex() == 1)
    ui->openGLWidget->point_color.blue = value;
  else if (ui->choose_view->currentIndex() == 2)
    ui->openGLWidget->background_color.blue = value;
  ui->openGLWidget->update();
  ui->blue_value->setNum(value);
}
/////////////////////////////////////////////////////////

void MainWindow::on_point_size_value_valueChanged(int value) {
  ui->point_size->setNum(value);
  ui->openGLWidget->point_size = value;
  ui->openGLWidget->update();
}

void MainWindow::on_line_size_value_valueChanged(int value) {
  ui->line_size->setNum(value);
  ui->openGLWidget->line_size = value;
  ui->openGLWidget->update();
}

void MainWindow::on_point_cube_clicked() {
  ui->openGLWidget->type_vertex_view = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_point_circle_clicked() {
  ui->openGLWidget->type_vertex_view = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_solid_button_clicked() {
  ui->openGLWidget->type_line_view = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_dashed_button_clicked() {
  ui->openGLWidget->type_line_view = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_point_is_exist_currentIndexChanged(int index) {
  if (!index) {
    ui->openGLWidget->is_point_exist = 1;
  } else {
    ui->openGLWidget->is_point_exist = 0;
  }
  ui->openGLWidget->update();
}

void MainWindow::on_line_is_exist_currentIndexChanged(int index) {
  if (!index) {
    ui->openGLWidget->is_line_exist = 1;
  } else {
    ui->openGLWidget->is_line_exist = 0;
  }
  ui->openGLWidget->update();
}

void MainWindow::save_settings() {
  QSettings settings(
      QCoreApplication::applicationDirPath() + "/4d_settings.conf",
      QSettings::NativeFormat);
  settings.setValue("Backgroung color_blue",
                    ui->openGLWidget->background_color.blue);
  settings.setValue("Backgroung color_green",
                    ui->openGLWidget->background_color.green);
  settings.setValue("Backgroung color_red",
                    ui->openGLWidget->background_color.red);

  settings.setValue("point_color color_blue",
                    ui->openGLWidget->point_color.blue);
  settings.setValue("point_color color_green",
                    ui->openGLWidget->point_color.green);
  settings.setValue("point_color color_red", ui->openGLWidget->point_color.red);

  settings.setValue("lines_color color_blue",
                    ui->openGLWidget->lines_color.blue);
  settings.setValue("lines_color color_green",
                    ui->openGLWidget->lines_color.green);
  settings.setValue("lines_color color_red", ui->openGLWidget->lines_color.red);

  settings.setValue("is_line_exist", ui->openGLWidget->is_line_exist);
  settings.setValue("is_point_exist", ui->openGLWidget->is_point_exist);

  settings.setValue("line_type_view", ui->openGLWidget->type_line_view);
  settings.setValue("point_type_view", ui->openGLWidget->type_vertex_view);

  settings.setValue("size_point", ui->openGLWidget->point_size);
  settings.setValue("size_line", ui->openGLWidget->line_size);

  settings.setValue("type_projection", ui->openGLWidget->type_projection);
}

void MainWindow::upload_settings() {
  QSettings settings(
      QCoreApplication::applicationDirPath() + "/4d_settings.conf",
      QSettings::NativeFormat);
  ui->openGLWidget->background_color.blue =
      settings.value("Backgroung color_blue", 160).toInt();
  ui->openGLWidget->background_color.green =
      settings.value("Backgroung color_green", 118).toInt();
  ui->openGLWidget->background_color.red =
      settings.value("Backgroung color_red", 7).toInt();

  ui->openGLWidget->point_color.blue =
      settings.value("point_color color_blue", 0).toDouble();
  ui->openGLWidget->point_color.green =
      settings.value("point_color color_green", 0).toDouble();
  ui->openGLWidget->point_color.red =
      settings.value("point_color color_red", 255).toDouble();

  ui->openGLWidget->lines_color.blue =
      settings.value("lines_color color_blue", 0).toDouble();
  ui->openGLWidget->lines_color.green =
      settings.value("lines_color color_green", 0).toDouble();
  ui->openGLWidget->lines_color.red =
      settings.value("lines_color color_red", 0).toDouble();

  ui->openGLWidget->type_line_view =
      settings.value("line_type_view", 0).toInt();
  ui->openGLWidget->type_vertex_view =
      settings.value("point_type_view", 0).toInt();

  ui->openGLWidget->point_size = settings.value("size_point", 5).toInt();
  ui->openGLWidget->line_size = settings.value("size_line", 5).toInt();

  ui->openGLWidget->is_line_exist = settings.value("is_line_exist", 1).toInt();
  ui->openGLWidget->is_point_exist =
      settings.value("is_point_exist", 1).toInt();

  ui->openGLWidget->type_projection =
      settings.value("type_projection", 0).toInt();
}
void MainWindow::on_pushButton_clicked() {
  gif = new QGifImage(QSize(640, 480));
  timerGIF = new QTimer(this);
  connect(timerGIF, &QTimer::timeout, this, &MainWindow::record_gif);
  timerGIF->start(100);
  frame = 0;
}
void MainWindow::record_gif() {
  ui->pushButton->setEnabled(0);
  QImage image(640, 480, QImage::Format_RGB32);
  image = ui->openGLWidget->grabFramebuffer();
  frame++;
  gif->addFrame(image, 100);  // цифра это задержка
  if (frame == 50) {
    QString file_name =
        QFileDialog::getSaveFileName(this, "Save Gif", "", "GIF (*.gif)");
    timerGIF->stop();
    gif->save(file_name);
    QFileInfo check_file(file_name);
    if (check_file.exists())
      QMessageBox::information(NULL, QObject::tr("Информация"),
                               tr("Файл сохранен успешно"));
    else
      QMessageBox::critical(NULL, QObject::tr("Ошибка"),
                            tr("Файл не сохранен"));
    delete gif;
    delete timerGIF;
    ui->pushButton->setEnabled(1);
  }
}

void MainWindow::on_pushButton_2_clicked() {
  QImage image = ui->openGLWidget->grabFramebuffer();
  QString fileName = QFileDialog::getSaveFileName(
      this, "Save Screenshot", "", "JPEG (*.jpeg);; PNG (*.png)");

  if (!fileName.isEmpty()) {
    QString format = QFileInfo(fileName).suffix().toLower();
    if (format == "jpeg" || format == "jpg") {
      image.save(fileName, "JPEG");
    } else if (format == "png") {
      image.save(fileName, "PNG");
    } else {
      QMessageBox::critical(this, "Error", "Invalid file format selected");
    }
  }
}

void MainWindow::on_choose_view_activated(int index) {
  if (index == 0) {
    ui->red_slider->setValue(ui->openGLWidget->lines_color.red);
    ui->red_value->setNum(ui->openGLWidget->lines_color.red);
    ui->green_slider->setValue(ui->openGLWidget->lines_color.green);
    ui->green_value->setNum(ui->openGLWidget->lines_color.green);
    ui->blue_slider->setValue(ui->openGLWidget->lines_color.blue);
    ui->blue_value->setNum(ui->openGLWidget->lines_color.blue);

  } else if (index == 1) {
    ui->red_slider->setValue(ui->openGLWidget->point_color.red);
    ui->red_value->setNum(ui->openGLWidget->point_color.red);
    ui->green_slider->setValue(ui->openGLWidget->point_color.green);
    ui->green_value->setNum(ui->openGLWidget->point_color.green);
    ui->blue_slider->setValue(ui->openGLWidget->point_color.blue);
    ui->blue_value->setNum(ui->openGLWidget->point_color.blue);
  } else {
    ui->red_slider->setValue(ui->openGLWidget->background_color.red);
    ui->red_value->setNum(ui->openGLWidget->background_color.red);
    ui->green_slider->setValue(ui->openGLWidget->background_color.green);
    ui->green_value->setNum(ui->openGLWidget->background_color.green);
    ui->blue_slider->setValue(ui->openGLWidget->background_color.blue);
    ui->blue_value->setNum(ui->openGLWidget->background_color.blue);
  }
}
