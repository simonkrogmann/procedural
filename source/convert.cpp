#include "convert.h"

#include <QImage>
#include <QGLWidget>

#include <iostream>

QImage loadImage(const std::string& filename)
{
    QImage image { QString::fromStdString(filename) };
    return QGLWidget::convertToGLFormat(image);
}

void saveImage(const std::vector<unsigned char>& data,
    const int& width, const int& height, const std::string& filename)
{
    QImage image { data.data(), width, height, QImage::Format_ARGB32 };
    std::cout << image.save(QString::fromStdString(filename)) << std::endl;
    std::cout << "Saved image " << filename << std::endl;
}
