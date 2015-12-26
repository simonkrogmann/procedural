#pragma once

#include <string>
#include <QImage>

// outside of util to avoid mixing QOpenGL and glbinding
QImage convertToGL(std::string filename);
