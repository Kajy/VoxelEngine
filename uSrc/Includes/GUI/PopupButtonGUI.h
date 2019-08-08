//
// Created by Manuel Trambert on 21/05/2018.
//

#ifndef UCRAFT_POPUPBUTTONGUI_H
#define UCRAFT_POPUPBUTTONGUI_H

#include <functional>
#include <nanogui/popup.h>
#include <nanogui/popupbutton.h>
#include <nanogui/vscrollpanel.h>
#include <nanogui/stackedwidget.h>
#include "GUI.hpp"
#include "WindowGUI.h"

namespace Ucraft {
    class PopupButtonGUI : public ObjectType {
    public:

        /**
         *
         * @param name The name of the button
         * @param type The type of object (ObjectType is abstract)
         * @param onAction The function that will be executed when the button is pressed
         * @param linked the InputText that is linked to the button
         *
         * PopupButtonGUI is a button that will be added to the current window.
         */
        PopupButtonGUI(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, const char *icon, const std::string &name,
                       const std::string &type, GUI *gui, uScreen *parent);

        void printObject();

        void disableObject();

        void setType(const std::string &type);

        void setName(const std::string &name);

        const std::string &getType();

        const std::string &getName();

        void addPlugin(const std::string &pluginName);

        const bool getIsPrinted();

        void setIsPrinted(bool isPrinted);

        void setWidget(nanogui::Widget *widget);

        nanogui::Widget *getWidget();

        const int getPosX();

        const int getPosY();

        const int getSizeX();

        const int getSizeY();

    private:
        OnActionFuncButton *_ptrFunc;
        nanogui::Popup *_popup;
        nanogui::Window *_stacked;
        GUI *_gui;
        nanogui::Widget *_parent;
        std::pair<nanogui::Button *, std::string> _onPluginChange;
        char *_icon;
    };
}

#endif //UCRAFT_POPUPBUTTONGUI_H
