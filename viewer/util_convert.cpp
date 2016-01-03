#include "util.h"

#include <QImage>
#include <QGLWidget>

#include <iostream>

// outside of util.cpp to avoid mixing QOpenGL and glbinding

namespace util
{
QImage loadImage(const std::string& filename)
{
    const QImage image{QString::fromStdString(filename)};
    return QGLWidget::convertToGLFormat(image);
}

void saveImage(const std::vector<unsigned char>& data, const int& width,
               const int& height, const std::string& filename)
{
    const QImage image{data.data(), width, height, QImage::Format_ARGB32};
    const auto flippedImage = image.mirrored();
    if (flippedImage.save(QString::fromStdString(filename)))
    {
        std::cout << "Saved image " << filename << std::endl;
    }
}
}
