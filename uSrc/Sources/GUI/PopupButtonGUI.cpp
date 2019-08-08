//
// Created by Manuel Trambert on 21/05/2018.
//

#include "PopupButtonGUI.h"

Ucraft::PopupButtonGUI::PopupButtonGUI(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, const char *icon,
                                       const std::string &name,
                                       const std::string &type, GUI *gui, uScreen *parent)
        : _gui(gui) {
    int sizeX = ((int) (((float) (parent->getWidth()) / 100.00) * size[0]));
    int sizeY = (int) (((float) (parent->getHeight()) / 100.00) * size[1]);

    int posX = ((int) (((float) (parent->getWidth()) / 100.00) * pos[0]));
    int posY = (int) (((float) (parent->getHeight()) / 100.00) * pos[1]);

    _pos = pos;
    _size = size;

    setType(type);
    _icon = strdup(icon);
    _name = name;
    _hasAlreadyBePrinted = false;
    _parent = new nanogui::Window(parent, "");
    _parent->setFixedSize(Eigen::Vector2i(sizeX, sizeY));
    _parent->setPosition(Eigen::Vector2i(posX, posY));
    nanogui::Theme *historyTheme = new nanogui::Theme(parent->nvgContext());
    historyTheme->mWindowHeaderHeight = 0;
    historyTheme->mWindowDropShadowSize = 0;
    historyTheme->mBorderDark = nanogui::Color(0, 0);
    historyTheme->mBorderLight = nanogui::Color(0, 0);
    historyTheme->mBorderMedium = nanogui::Color(0, 0);
    historyTheme->mDropShadow = nanogui::Color(0, 255);
    historyTheme->mWindowFillFocused = nanogui::Color(0, 0);
    historyTheme->mWindowFillUnfocused = nanogui::Color(0, 0);
    _parent->setTheme(historyTheme);
    _widget = new nanogui::PopupButton(_parent, "Plugins");
    ((nanogui::PopupButton *) _widget)->setFixedSize(Eigen::Vector2i(sizeX, sizeY));
    ((nanogui::PopupButton *) _widget)->setSide(nanogui::Popup::Side::Left);
    _popup = ((nanogui::PopupButton *) _widget)->popup();
    _popup->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 5, 5));
    _popup->setFixedSize(Eigen::Vector2i(200, 300));
    nanogui::VScrollPanel *panel = new nanogui::VScrollPanel(_popup);
    panel->setFixedSize(Eigen::Vector2i(200, 300));
    panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 2, 2));
    _stacked = new nanogui::Window(panel, "");
    _popup->setTheme(historyTheme);
    _stacked->setTheme(historyTheme);
    _stacked->setFixedSize(Eigen::Vector2i(200, 300));
    _stacked->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 5, 5));
}

void Ucraft::PopupButtonGUI::printObject() {
    ((nanogui::PopupButton *) _widget)->setVisible(true);
}

void Ucraft::PopupButtonGUI::disableObject() {
    ((nanogui::PopupButton *) _widget)->setVisible(false);
    _popup->setVisible(false);
    _hasAlreadyBePrinted = false;
}

void Ucraft::PopupButtonGUI::setType(const std::string &type) {
    _type = type;
}

void Ucraft::PopupButtonGUI::setName(const std::string &name) {
    _name = name;
}

const std::string &Ucraft::PopupButtonGUI::getType() {
    return _type;
}

const std::string &Ucraft::PopupButtonGUI::getName() {
    return _name;
}

const bool Ucraft::PopupButtonGUI::getIsPrinted() {
    return _hasAlreadyBePrinted;
}

void Ucraft::PopupButtonGUI::setIsPrinted(bool isPrinted) {
    _hasAlreadyBePrinted = isPrinted;
}

void Ucraft::PopupButtonGUI::setWidget(nanogui::Widget *widget) {
    _widget = widget;
}

void Ucraft::PopupButtonGUI::addPlugin(const std::string &pluginName) {
    nanogui::Button *child = new nanogui::Button(_stacked, pluginName);
    child->setWidth(180);
    child->setCallback([this, child]() {
        if (this->_gui->getPluginName() != child->caption()) {
            this->_gui->setPluginName(child->caption());
            this->_gui->reloadInventory();
        }
    });
}

nanogui::Widget *Ucraft::PopupButtonGUI::getWidget() {
    return _parent;
}

const int Ucraft::PopupButtonGUI::getPosX() { return _pos[0]; };

const int Ucraft::PopupButtonGUI::getPosY() { return _pos[1]; };

const int Ucraft::PopupButtonGUI::getSizeX() { return _size[0]; };

const int Ucraft::PopupButtonGUI::getSizeY() { return _size[1]; };
