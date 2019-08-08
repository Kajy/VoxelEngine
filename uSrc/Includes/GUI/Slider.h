//
// Created by Manuel Trambert on 21/05/2018.
//

#ifndef UCRAFT_SLIDER_H
#define UCRAFT_SLIDER_H

#include <nanogui/slider.h>
#include "uScreen.h"
#include "WindowGUI.h"
#include "ObjectType.h"

namespace Ucraft {
    class Slider :
            public ObjectType {
    public:
        /**
         *
         * @param name Name of the object
         * @param type Type of the object
         *
         * Constructor to create an InputText object.
         */
        Slider(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, const Eigen::Vector2f &, WindowGUI *parent, uScreen *, const std::string &name = "No name",
               const std::string &type = "No type");

        ~Slider();

        std::string getText();

        void setText(std::string text);

        History *getHistory();

        void getValueFromChat(const std::string &value);

        void printObject();

        void disableObject();

        void setWidget(nanogui::Widget *widget);

        void setType(const std::string &type);

        void setName(const std::string &name);

        const std::string &getType();

        const std::string &getName();

        const bool getIsPrinted();

        void setIsPrinted(bool isPrinted);

        nanogui::Widget *getWidget();

        const int getPosX();

        const int getPosY();

        const int getSizeX();

        const int getSizeY();

    private:
        nanogui::Label *_title;
        Eigen::Vector2f _range;
        uScreen *_infos;
        WindowGUI *_parent;
    };
}

#endif //UCRAFT_widget_H
