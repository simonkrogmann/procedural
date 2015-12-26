#include "convert.h"

#include <QImage>
#include <QGLWidget>

QImage convertToGL(std::string filename)
{
    QImage image { QString::fromStdString(filename) };
    return QGLWidget::convertToGLFormat(image);
}
