#include "UOptions.h"

Ucraft::Options::Options(int w, int h) : _width(w), _height(h) {
    _resized = false;
    _fromMenu = false;
}

int *Ucraft::Options::getWidth() {
    return &_width;
}

int *Ucraft::Options::getHeight() {
    return &_height;
}

void Ucraft::Options::setSize(const int width, const int height) {
    _width = width;
    _height = height;
    _resized = true;
}

void Ucraft::Options::setResized(bool resized) {
    _resized = resized;
}

bool Ucraft::Options::getResized() {
    return _resized;
}

void Ucraft::Options::setFromMenu(bool is) {
    _fromMenu = is;
}

bool Ucraft::Options::isFromMenu() {
    return _fromMenu;
}
