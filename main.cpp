#include <QApplication>
#include <QGraphicsScene>
#include "Scene.h"
#include <QGraphicsView>
#include <QBrush>
#include <QImage>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Scene *scene = new Scene(600, 600);

    return a.exec();
}
