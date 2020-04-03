#include <QtWidgets/QApplication>
#include "server.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ChatSimulator::Server s;
  return a.exec();
}