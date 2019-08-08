//
// Created by Manuel Trambert on 22/05/2018.
//

#ifndef UCRAFT_GUITEXT_H
#define UCRAFT_GUITEXT_H

#include <string>
#include <nanogui/widget.h>
#include "ObjectType.h"

namespace Ucraft {
    class GuiText : public ObjectType {
    public:

        /**
         *
         * @param name The name of the object
         * @param type The type of object
         *
         * Constructor to add a text to the GUI.
         */
        GuiText(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, nanogui::Widget *parent, int fontSize,
                const std::string &name = "No name", const std::string &type = "No type");

        ~GuiText();

        void printObject();

        void disableObject();

        void setWidget(nanogui::Widget *widget);

        void setCaption(const std::string &value);

        void setType(const std::string &type);

        void setName(const std::string &name);

        const std::string &getType();

        const std::string &getName();

        const bool getIsPrinted();

        void setIsPrinted(const bool isPrinted);

        nanogui::Widget *getWidget();

        const int getPosX();

        const int getPosY();

        const int getSizeX();

        const int getSizeY();

        const std::string &getCaption();

        void setText(const std::string &);

    private:
        int _fontSize;
    };
}

#endif //UCRAFT_GUITEXT_H
