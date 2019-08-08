
#include "WindowGUI.h"


Ucraft::WindowGUI::WindowGUI(float posX, float posY, const std::string &name, const std::string &type, uScreen *screen) {
    setType(type);
    _pos = Eigen::Vector2i(0, 0);
    _size = Eigen::Vector2i(100, 100);
    _name = name;
    _hasAlreadyBePrinted = false;
    _gui = new nanogui::FormHelper(screen);
    _gui->addWindow(_pos, _name);
    _gui->window()->setFixedSize(Eigen::Vector2i(screen->getWidth(), screen->getHeight()));
    _gui->window()->setVisible(false);
    _widget = _gui->window();
}

Ucraft::WindowGUI::WindowGUI(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, const std::string &name,
                             const std::string &type, uScreen *screen) {
    setType(type);
    _size = size;
    _pos = pos;

    int sizeX = (int) (((float) (screen->getWidth()) / 100.00) * _size[0]);
    int sizeY = (int) (((float) (screen->getHeight()) / 100.00) * _size[1]);
    int posX = (int) (((float) (screen->getWidth()) / 100.00) * _pos[0]);
    int posY = (int) (((double) (screen->getHeight()) / 100.00) * _pos[1]);

    _name = name;
    _hasAlreadyBePrinted = false;
    _gui = new nanogui::FormHelper(screen);
    _gui->addWindow(Eigen::Vector2i(posX, posY), _name);
    _gui->window()->setFixedSize(Eigen::Vector2i(screen->getWidth(), sizeY));
    _gui->window()->setVisible(false);
    _gui->window()->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 2, 5));
    _gui->window()->setTitle("");
    _panel = new nanogui::VScrollPanel(_gui->window());
    _panel->setFixedSize(Eigen::Vector2i(sizeX, sizeY));
    _panel->setVisible(true);
    _widget = new nanogui::Window(_panel);
    _widget->setVisible(true);
    _widget->setFixedSize(Eigen::Vector2i(screen->getWidth(), 100));
    _widget->setPosition(Eigen::Vector2i(0, 0));
    _widget->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 5, 5));
    nanogui::Theme *historyTheme = new nanogui::Theme(screen->nvgContext());
    historyTheme->mWindowHeaderHeight = 0;
    historyTheme->mWindowDropShadowSize = 0;
    historyTheme->mBorderDark = nanogui::Color(0, 0);
    historyTheme->mBorderLight = nanogui::Color(0, 0);
    historyTheme->mBorderMedium = nanogui::Color(0, 0);
    historyTheme->mDropShadow = nanogui::Color(0, 0);
    historyTheme->mWindowFillFocused = nanogui::Color(0, 0);
    historyTheme->mWindowFillUnfocused = nanogui::Color(0, 0);
    _widget->setTheme(historyTheme);
    ((nanogui::Window *)_widget)->setTitle("");
    _gui->window()->setPosition(Eigen::Vector2i(0, 0));
}

const int Ucraft::WindowGUI::getPosX() {
    return _pos[0];
}

const int Ucraft::WindowGUI::getPosY() {
    return _pos[1];
}

void Ucraft::WindowGUI::setType(const std::string &type) {
    _type = type;
}

void Ucraft::WindowGUI::printObject() {
    _gui->window()->setVisible(true);
}

void Ucraft::WindowGUI::setWidget(nanogui::Widget *widget) {
    _widget = widget;
}

void Ucraft::WindowGUI::disableObject() {
    _gui->window()->setVisible(false);
    _hasAlreadyBePrinted = false;
}

void Ucraft::WindowGUI::setName(const std::string &name) {
    _name = name;
}

void Ucraft::WindowGUI::resizeInventory(Ucraft::uScreen *screen) {
   int sizeX = ((int) (((float) (screen->getWidth()) / 100.00) * 100));
    int sizeY = (int) (((float) (screen->getHeight()) / 100.00) * 20);
    int otherSizeY = (int) (((float) (screen->getHeight()) / 100.00) * 100);

    _gui->window()->setFixedSize(Eigen::Vector2i(sizeX, otherSizeY));
    _panel->setFixedSize(Eigen::Vector2i(sizeX - 20, otherSizeY));
    _widget->setFixedSize(Eigen::Vector2i(sizeX - 60, 100));
    for (int i = 0; i < _widget->childCount(); i += 1) {
        _widget->childAt(i)->setFixedSize(Eigen::Vector2i(sizeX - 60, 100));
    }
}

const std::string &Ucraft::WindowGUI::getType() {
    return _type;
}

const std::string &Ucraft::WindowGUI::getName() {
    return _name;
}

const int Ucraft::WindowGUI::getSizeX() {
    return _size[0];
}

const int Ucraft::WindowGUI::getSizeY() {
    return _size[1];
}

const bool Ucraft::WindowGUI::getIsPrinted() {
    return _hasAlreadyBePrinted;
}

void Ucraft::WindowGUI::setIsPrinted(bool isPrinted) {
    _hasAlreadyBePrinted = isPrinted;
}

nanogui::Widget *Ucraft::WindowGUI::getWidget() {
    return _widget;
}

nanogui::FormHelper *Ucraft::WindowGUI::getWindow() { return _gui; };