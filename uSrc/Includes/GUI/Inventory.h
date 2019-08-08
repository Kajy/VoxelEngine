//
// Created by Manuel Trambert on 22/05/2018.
//

#ifndef UCRAFT_INVENTORY_H
#define UCRAFT_INVENTORY_H

#include <string>
#include <nanogui/vscrollpanel.h>
#include <nanogui/imagepanel.h>
#include <nanogui/stackedwidget.h>
#include "ObjectType.h"
#include "WindowGUI.h"

namespace Ucraft {
    class Inventory : public ObjectType {
    public:

        /**
         *
         * @param name The name of the object
         * @param type The type of object
         *
         * Constructor to add a text to the GUI.
         */
        Inventory(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, uScreen *parent, const std::string &name,
                  const std::string &type, const std::string &_path);

        Inventory(WindowGUI *parent, const std::string &name = "No name", const std::string &type = "No type",
                  const std::string &_path = "..");

        ~Inventory();

        std::vector<char *> *getHistoryList();

        void printObject();

        void clearListIcons();

        void loadInventory(const std::string &, Ucraft::uScreen *, const std::string &,
                           std::vector<std::pair<std::string, std::pair<std::string, short>>>);

        void setCallback(uScreen *screen, const std::string &, const std::string &,
                         std::vector<std::pair<std::string, std::pair<std::string, short>>> listBlockId);

        void disableObject();

        void setWidget(nanogui::Widget *widget);

        void setValue(const std::string &value);

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

        const int getCorrectId(const int id);

    private:
        uScreen *_parent;
        std::vector<std::pair<int, std::string>> _listIcons;
        std::map<int, short> _listCubeId;
        nanogui::ImagePanel *_img;
    };
}

#endif //UCRAFT_GUITEXT_H
