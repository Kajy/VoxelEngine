//
// Created by Manuel Trambert on 21/05/2018.
//

#ifndef UCRAFT_BUTTONGUI_H
#define UCRAFT_BUTTONGUI_H

#include <functional>
#include <nanogui/popup.h>
#include <nanogui/popupbutton.h>
#include "WindowGUI.h"

namespace Ucraft {
    class ButtonGUI : public ObjectType {
    public:

        /**
         *
         * @param name The name of the button
         * @param type The type of object (ObjectType is abstract)
         * @param onAction The function that will be executed when the button is pressed
         * @param linked the InputText that is linked to the button
         *
         * ButtonGUI is a button that will be added to the current window.
         */
        ButtonGUI(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, const char *icon, const std::string &name,
                  const std::string &type, OnActionFuncButton *onAction, GUI *gui, WindowGUI *parent);

        void printObject();

        void disableObject();

        void setType(const std::string &type);

        void setName(const std::string &name);

        const std::string &getType();

        const std::string &getName();

        const bool getIsPrinted();

        void setIsPrinted(bool isPrinted);

        void setWidget(nanogui::Widget *widget);

        nanogui::Widget *getWidget();

        const int getPosX();

        const int getPosY();

        const int getSizeX();

        const int getSizeY();

        const std::function<void()> buttonFunc();

    private:
        OnActionFuncButton *_ptrFunc;
        GUI *_gui;
        WindowGUI *_parent;
        char *_icon;
    };
}

#endif //UCRAFT_BUTTONGUI_H
