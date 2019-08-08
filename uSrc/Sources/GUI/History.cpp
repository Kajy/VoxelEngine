//
// Created by Manuel Trambert on 12/11/2018.
//
#include "History.h"


Ucraft::History::History(nanogui::Widget *parent, Ucraft::ObjectType *inputParent, const unsigned int theme)
        : _parent(parent), _inputParent(inputParent) {
    _vscroll = new nanogui::VScrollPanel(parent);
    int sizeX = ((int) (((float) (((uScreen *) parent)->getWidth()) / 100.00) * 50));
    int sizeY = (int) (((float) (((uScreen *) parent)->getHeight()) / 100.00) * 10);
    int sizeInputY = (int) (((float) (((uScreen *) parent)->getHeight()) / 100.00) * _inputParent->getSizeY());
    int posX = (int) (((float) (((uScreen *) parent)->getHeight()) / 100) * inputParent->getPosX() + 2);
    int posY = (int) (((float) (((uScreen *) parent)->getHeight())) - sizeInputY - sizeY - 5);
    _pos = Eigen::Vector2i(posX, posY);
    _size = Eigen::Vector2i(sizeX, sizeY);
    _vscroll->setFixedSize(_size);
    _vscroll->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Fill, 0, 0));
    _vscroll->setVisible(true);
    _vscroll->setPosition(_pos);
    ((nanogui::VScrollPanel *) _vscroll)->setScroll(1);
    _stacked = new nanogui::Window(_vscroll);
    ((nanogui::Window *) _stacked)->setTitle("");
    nanogui::Theme *historyTheme = new nanogui::Theme(((uScreen *) parent)->nvgContext());
    historyTheme->mWindowHeaderHeight = 0;
    historyTheme->mWindowDropShadowSize = 0;
    historyTheme->mBorderDark = nanogui::Color(0, 0);
    historyTheme->mBorderLight = nanogui::Color(0, 0);
    historyTheme->mBorderMedium = nanogui::Color(0, 0);
    historyTheme->mDropShadow = nanogui::Color(0, 255);
    historyTheme->mWindowFillFocused = nanogui::Color(0, 0);
    historyTheme->mWindowFillUnfocused = nanogui::Color(60, 60);
    _stacked->setTheme(historyTheme);
    _stacked->setFixedSize(_size);
    _stacked->setPosition(_pos);
    _stacked->setLayout(
            new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 2, 2));
    ((nanogui::VScrollPanel *) _vscroll)->setScroll(1);
    addLine("Welcome in uCraft!");
    //addLine("Welcome in uCraft!");
    //addLine("Welcome in uCraft!");
};

Ucraft::History::~History() {};

void Ucraft::History::printObject() {
    _vscroll->setVisible(true);
}

void Ucraft::History::disableObject() {
    _vscroll->setVisible(false);
}

void Ucraft::History::sendLine(const std::string &value) {
    if (value.size() == 0) {
        return;
    }
    if (value[0] == '/') {
        _gui->getQueueCommandOut()->push_back(value);
    } else {
        _gui->getQueueMessageOut()->push_back(value);
    }
}

void Ucraft::History::onUnfocus() {
    int sizeInputY = (int) (((float) (((uScreen *) _parent)->getHeight()) / 100.00) * _inputParent->getSizeY());

    _size[1] = (int) (((float) (((uScreen *) _parent)->getHeight()) / 100.00) * 10);
    _pos[1] = (int) (((float) (((uScreen *) _parent)->getHeight())) - sizeInputY - _size[1]);
    _vscroll->setFixedSize(_size);
    _stacked->setFixedSize(_size);
    _vscroll->setPosition(_pos);
    _stacked->setPosition(_pos);
}

void Ucraft::History::onFocus() {
    int sizeInputY = (int) (((float) (((uScreen *) _parent)->getHeight()) / 100.00) * _inputParent->getSizeY());

    _size[1] = (int) (((float) (((uScreen *) _parent)->getHeight()) / 100.00) * 30);
    _pos[1] = (int) (((float) (((uScreen *) _parent)->getHeight())) - sizeInputY - _size[1]);
    _vscroll->setFixedSize(_size);
    _stacked->setFixedSize(_size);
    _vscroll->setPosition(_pos);
    _stacked->setPosition(_pos);
}

void Ucraft::History::resize() {
    int sizeInputY = (int) (((float) (((uScreen *) _parent)->getHeight()) / 100.00) * _inputParent->getSizeY());

    _size[1] = (int) (((float) (((uScreen *) _parent)->getHeight()) / 100.00) * 10);
    _size[0] = (int) (((float) (((uScreen *) _parent)->getWidth()) / 100.00) * 50);
    _pos[0] = (int) (((float) (((uScreen *) _parent)->getHeight()) / 100) * _inputParent->getPosX() + 2);
    _pos[1] = (int) (((float) (((uScreen *) _parent)->getHeight())) - sizeInputY - _size[1]);
    _vscroll->setFixedSize(_size);
    _stacked->setFixedSize(_size);
    _vscroll->setPosition(_pos);
    _stacked->setPosition(_pos);
}

const std::string &getHour(const std::string &currentTime) {
    return currentTime.substr(11, 5);
}

void Ucraft::History::addLine(const std::string &value) {
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();

    std::time_t t = std::chrono::system_clock::to_time_t(p);
    std::string toPrint("");

   // toPrint.append(getHour(std::ctime(&t)));
   // toPrint.append("] ");

    toPrint.append(value);
    nanogui::Label *test = new nanogui::Label(_stacked, toPrint, "sans-bold");
    test->setFontSize(25);
    _list.push_back(test);
    if (_list.size() >= 3) {
        ((nanogui::VScrollPanel *) _vscroll)->setScroll(1);
    }
};

void Ucraft::History::setPointerToGui(GUI *gui) {
    _gui = gui;
}