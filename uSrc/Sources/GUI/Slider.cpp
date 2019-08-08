#include "Slider.h"

Ucraft::Slider::Slider(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, const Eigen::Vector2f &range,
                       WindowGUI *parent, uScreen *infos, const std::string &name, const std::string &type) {
    setType(type);
    _size = size;
    _pos = pos;
    _name = name;
    _parent = parent;
    _infos = infos;
    _range = range;
    _hasAlreadyBePrinted = false;
    _title = new nanogui::Label(parent->getWidget(),
                                name + " : 100"  +
                                " %", "sans-bold", 14);
    _title->setFontSize(12);
    _widget = new nanogui::Slider(parent->getWidget());
    ((nanogui::Slider *) _widget)->setValue(100.0);
    ((nanogui::Slider *) _widget)->setRange(std::pair<float, float>(_range[0], _range[1]));
    ((nanogui::Slider *) _widget)->setCallback([this](float value) {
        this->_title->setCaption(this->_name + " : " + std::to_string((int) ((value - _range[0]) / (_range[1] - _range[0]) * 100.0)) + " %");
        this->_infos->setFov(value);
    });
};

Ucraft::Slider::~Slider() {};

void Ucraft::Slider::printObject() {
    ((nanogui::Slider *) _widget)->setVisible(true);
}

void Ucraft::Slider::disableObject() {
    _widget->setVisible(false);
    _hasAlreadyBePrinted = false;
}

void Ucraft::Slider::setWidget(nanogui::Widget *widget) {
    _widget = widget;
}

void Ucraft::Slider::setType(const std::string &type) {
    _type = type;
}

void Ucraft::Slider::setName(const std::string &name) {
    _name = name;
}

const std::string &Ucraft::Slider::getType() {
    return _type;
}

const std::string &Ucraft::Slider::getName() {
    return _name;
}

const bool Ucraft::Slider::getIsPrinted() {
    return _hasAlreadyBePrinted;
}

void Ucraft::Slider::setIsPrinted(bool isPrinted) {
    _hasAlreadyBePrinted = isPrinted;
}

nanogui::Widget *Ucraft::Slider::getWidget() {
    return _widget;
}

const int Ucraft::Slider::getPosX() { return _pos[0]; };

const int Ucraft::Slider::getPosY() { return _pos[1]; };

const int Ucraft::Slider::getSizeX() { return _size[0]; };

const int Ucraft::Slider::getSizeY() { return _size[1]; };