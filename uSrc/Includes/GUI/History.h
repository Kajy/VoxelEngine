//
// Created by Manuel Trambert on 12/11/2018.
//
#include <chrono>
#include <ctime>
#include <list>
#include "GUI.hpp"

#ifndef UCRAFT_HISTORY_H
#define UCRAFT_HISTORY_H

namespace Ucraft {
class History {
public:
    History(nanogui::Widget *parent, Ucraft::ObjectType *, const unsigned int theme = 0);

    ~History();

    void printObject();

    void disableObject();

    void sendLine(const std::string &value);

    void onUnfocus();

    void onFocus();

    void addLine(const std::string &value);

    void setPointerToGui(GUI *gui);

    void resize();

private:
    std::list<nanogui::Label *> _list;
    Eigen::Vector2i _pos;
    Eigen::Vector2i _size;
    nanogui::Widget *_parent;
    nanogui::Widget *_vscroll;
    nanogui::Widget *_stacked;
    Ucraft::ObjectType *_inputParent;
    GUI *_gui;
};
}

#endif //UCRAFT_HISTORY_H
