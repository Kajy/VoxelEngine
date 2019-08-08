//
// Created by Manuel Trambert on 21/05/2018.
//

#include "ButtonGUI.h"

Ucraft::ButtonGUI::ButtonGUI(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, const char *icon, const std::string &name,
                             const std::string &type, OnActionFuncButton *onAction, GUI *gui, WindowGUI *parent)
        : _ptrFunc(onAction), _gui(gui) {
    setType(type);
    _pos = pos;
    _size = size;
    _icon = strdup(icon);
    _name = name;
    _hasAlreadyBePrinted = false;
    _parent = parent;
    _widget = _parent->getWindow()->addButton(_name, buttonFunc());
    _widget->setFixedHeight(_size[0]);
    _widget->setFixedWidth(_size[1]);
}

void Ucraft::ButtonGUI::printObject() {
    _widget->setVisible(true);
}

void Ucraft::ButtonGUI::disableObject() {
    _hasAlreadyBePrinted = false;
}

void Ucraft::ButtonGUI::setType(const std::string &type) {
    _type = type;
}

void Ucraft::ButtonGUI::setName(const std::string &name) {
    _name = name;
}

const std::string &Ucraft::ButtonGUI::getType() {
    return _type;
}

const std::string &Ucraft::ButtonGUI::getName() {
    return _name;
}

const bool Ucraft::ButtonGUI::getIsPrinted() {
    return _hasAlreadyBePrinted;
}

void Ucraft::ButtonGUI::setIsPrinted(bool isPrinted) {
    _hasAlreadyBePrinted = isPrinted;
}

void Ucraft::ButtonGUI::setWidget(nanogui::Widget *widget) {
    _widget = widget;
}

nanogui::Widget *Ucraft::ButtonGUI::getWidget() {
    return _widget;
}

const int Ucraft::ButtonGUI::getPosX() { return _pos[0]; };

const int Ucraft::ButtonGUI::getPosY() { return _pos[1]; };

const int Ucraft::ButtonGUI::getSizeX() { return _size[0]; };

const int Ucraft::ButtonGUI::getSizeY() { return _size[1]; };

const std::function<void()> Ucraft::ButtonGUI::buttonFunc() {
    std::function<void()> lambda = [this]() {
        _ptrFunc(this, _gui);
    };
    return lambda;
};