//
// Created by Manuel Trambert on 29/11/2018.
//

#include "GuiText.h"

/**
 *
 * @param name The name of the object
 * @param type The type of object
 *
 * Constructor to add a text to the GUI.
 */
Ucraft::GuiText::GuiText(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, nanogui::Widget *parent, int fontSize,
                 const std::string &name, const std::string &type) {
    setType(type);
    _fontSize = fontSize;
    _name = name;
    _widget = new nanogui::Label(parent, name, "sans-bold");
    _widget->setFontSize(fontSize);
    _pos = pos;
    _size = size;
    _hasAlreadyBePrinted = false;
    _widget->setVisible(false);
};

Ucraft::GuiText::~GuiText() {};

void Ucraft::GuiText::printObject() {
    _widget->setVisible(true);
}

void Ucraft::GuiText::disableObject() {
    _widget->setVisible(false);
    _hasAlreadyBePrinted = false;
}

void Ucraft::GuiText::setWidget(nanogui::Widget *widget) {
    _widget = widget;
}

void Ucraft::GuiText::setCaption(const std::string &value) {
    std::string text(((nanogui::Label*)_widget)->caption() + "\n" + value);
    ((nanogui::Label*)_widget)->setCaption(text);
}

void Ucraft::GuiText::setType(const std::string &type) {
    _type = type;
}

void Ucraft::GuiText::setName(const std::string &name) {
    _name = name;
    ((nanogui::Label*)_widget)->setCaption(name);
}

const std::string &Ucraft::GuiText::getType() {
    return _type;
}

const std::string &Ucraft::GuiText::getName() {
    return _name;
}

const bool Ucraft::GuiText::getIsPrinted() {
    return _hasAlreadyBePrinted;
}

void Ucraft::GuiText::setIsPrinted(bool isPrinted) {
    _hasAlreadyBePrinted = isPrinted;
}

nanogui::Widget *Ucraft::GuiText::getWidget() {
    return _widget;
}

const int Ucraft::GuiText::getPosX() { return _pos[0]; };

const int Ucraft::GuiText::getPosY() { return _pos[1]; };

const int Ucraft::GuiText::getSizeX() { return _size[0]; };

const int Ucraft::GuiText::getSizeY() { return _size[1]; };