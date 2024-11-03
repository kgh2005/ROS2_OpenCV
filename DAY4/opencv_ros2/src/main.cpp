#include <QApplication>
#include <iostream>

#include "../include/opencv_ros2/main_window.hpp"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
