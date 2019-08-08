//
// Created by Manuel Trambert on 21/04/2018.
//

#ifndef UCRAFT_WINDOWGUI_H
#define UCRAFT_WINDOWGUI_H

#include "ObjectType.h"
#include "GuiText.h"
#include "uScreen.h"

#include <nanogui/vscrollpanel.h>
#include <nanogui/stackedwidget.h>

namespace Ucraft {
    class WindowGUI : public ObjectType {
    public:
        /**
         *
         * @param posX The position of the window on the main screen on the X
         * @param posY The position of the window on the main screen on the Y
         * @param sizeX The size of the window on the main screen on the X
         * @param sizeY The size of the window on the main screen on the Y
         * @param name The name of the window
         * @param type The type of object (Abstract from ObjectType)
         *
         * Main component. It's the constructor for a window. When you create a new context of a window you have to use a "WindowGUI" object.
         */
        WindowGUI(const Eigen::Vector2i &, const Eigen::Vector2i &, const std::string &name, const std::string &type,
                  uScreen *screen);

        WindowGUI(float posX, float posY, const std::string &name, const std::string &type, uScreen *screen);

        const int getPosX();

        const int getPosY();

        void setType(const std::string &type);

        void printObject();

        void setWidget(nanogui::Widget *widget);

        void disableObject();

        void setName(const std::string &name);

        void resizeInventory(Ucraft::uScreen *screen);

        const std::string &getType();

        const std::string &getName();

        const int getSizeX();

        const int getSizeY();

        const bool getIsPrinted();

        void setIsPrinted(bool isPrinted);

        nanogui::Widget *getWidget();

        nanogui::FormHelper *getWindow();

    private:
        nanogui::FormHelper *_gui;
        nanogui::VScrollPanel *_panel;
    };
}

#endif //UCRAFT_WINDOWGUI_H
