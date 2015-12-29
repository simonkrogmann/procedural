#pragma once

#include <string>
#include <QImage>

// outside of util to avoid mixing QOpenGL and glbinding
QImage loadImage(const std::string& filename);
void saveImage(const std::vector<unsigned char>& data,
    const int& width, const int& height, const std::string& filename);
