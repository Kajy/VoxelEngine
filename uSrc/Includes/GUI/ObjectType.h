//
// Created by Manuel Trambert on 22/02/2018.
//

#ifndef UCRAFT_OBJECTTYPE_H
#define UCRAFT_OBJECTTYPE_H

#include <vector>
#include <string>
#include <iostream>

#include <GL/glew.h>
#include <nanogui/widget.h>
#include <nanogui/formhelper.h>

namespace Ucraft {
    class GuiText;

    class ObjectType;

    class InputTextGUI;

    class GUI;

    class History;
}

typedef void *(OnActionFuncButton)(Ucraft::ObjectType *, Ucraft::GUI *);

/**
 * Abstract class to have generic classes for every components of the GUI
 */
namespace Ucraft {
    class ObjectType {
    public:

        virtual ~ObjectType() {};

        virtual const int getPosX() = 0;

        virtual const int getPosY() = 0;

        virtual const int getSizeX() = 0;

        virtual const int getSizeY() = 0;

        virtual const std::string &getType() = 0;

        virtual void setIsPrinted(bool) = 0;

        virtual void setType(const std::string &) = 0;

        virtual void setName(const std::string &) = 0;

        virtual const std::string &getName() = 0;

        virtual const bool getIsPrinted() = 0;

        virtual nanogui::Widget *getWidget() = 0;

        virtual void printObject() = 0;

        virtual void disableObject() = 0;

        virtual void setWidget(nanogui::Widget *) = 0;

    protected:
        Eigen::Vector2i _pos;
        Eigen::Vector2i _size;
        std::string _name;
        std::string _type;
        nanogui::Widget *_widget;
        bool _hasAlreadyBePrinted;
    };
}

#endif //UCRAFT_OBJECTTYPE_H
