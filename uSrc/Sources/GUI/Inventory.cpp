//
// Created by Manuel Trambert on 28/11/2018.
//

#include "Inventory.h"

/**
 *
 * @param name The name of the object
 * @param type The type of object
 *
 * Constructor to add a text to the GUI.
 */
Ucraft::Inventory::Inventory(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, uScreen *parent,
                             const std::string &name, const std::string &type, const std::string &_path) {
    setType(type);
    _parent = parent;
    int sizeX = ((int) (((float) (parent->getWidth()) / 100.00) * size[0]));
    int sizeY = (int) (((float) (parent->getHeight()) / 100.00) * size[1]);

    int posX = ((int) (((float) (parent->getWidth()) / 100.00) * pos[0]));
    int posY = (int) (((float) (parent->getHeight()) / 100.00) * pos[1]);

    _name = name;
    _pos = pos;
    _size = size;
    _widget = new nanogui::VScrollPanel(parent);
    _widget->setPosition(Eigen::Vector2i(posX, posY));
    _widget->setFixedSize(Eigen::Vector2i(sizeX, sizeY));
    _widget->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Fill, 5, 5));
    _img = new nanogui::ImagePanel(_widget);
    _hasAlreadyBePrinted = false;
    _widget->setVisible(false);

    _img->setCallback([this](int i) {
        this->_parent->getWorld()->_valueAddBlock = this->getCorrectId(i);
    });
};

Ucraft::Inventory::Inventory(Ucraft::WindowGUI *parent, const std::string &name, const std::string &type,
                             const std::string &_path) {
    setType(type);

    parent->getWidget()->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 5, 5));
    nanogui::Label *title = new nanogui::Label(parent->getWidget(), name, "sans-bold", 26);
    _widget = new nanogui::VScrollPanel(parent->getWidget());
    _widget->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 5, 5));
    _widget->setFixedSize(Eigen::Vector2i(1200, 100));
    _widget->setVisible(true);
};

void resetListCubeId(std::map<int, short> *listCubeId) {
    int i = 0;
    for (std::map<int, short>::iterator it = listCubeId->begin(); it != listCubeId->end(); it++) {
        (*listCubeId)[i] = (*it).second;
        i += 1;
    }
}

void deleteMultipleTexture(std::vector<std::pair<int, std::string>> *icons) {
	//std::vector<std::pair<int, std::string>> toDelete;
	for (std::vector<std::pair<int, std::string>>::iterator it = icons->begin();
		it != icons->end(); it++) {
		for (std::vector<std::pair<int, std::string>>::iterator itBis = icons->begin();
			itBis != icons->end(); itBis++) {
			if ((*it).second != (*itBis).second) {
				std::string first((*it).second);
				std::string second((*itBis).second);
				if (first.find("_side.png") != std::string::npos) {
					first.replace(first.find("_side.png"), 9, "");
				}
				if (first.find("_top.png") != std::string::npos) {
					first.replace(first.find("_top.png"), 8, "");
				}
				if (second.find("_side") != std::string::npos) {
					second.replace(second.find("_side"), 5, "");
				}
				if (second.find("_top") != std::string::npos) {
					second.replace(second.find("_top"), 4, "");
				}
				std::size_t found = first.find(second);
				if (found != std::string::npos) {
					icons->erase(itBis);
					//toDelete.push_back(*it);
					itBis = icons->begin();
				}
			}
		}
	}
}

void Ucraft::Inventory::loadInventory(const std::string &pluginName, Ucraft::uScreen *parent, const std::string &path,
                                      std::vector<std::pair<std::string, std::pair<std::string, short>>> listBlockId) {
    if (pluginName != "all") {
        _listCubeId.clear();
    }
    try {
        std::vector<std::pair<int, std::string>> icons =
                nanogui::loadImageDirectory(parent->nvgContext(), path + "/Ressources/cacheTexture/" + pluginName);

        deleteMultipleTexture(&icons);
        for (std::vector<std::pair<int, std::string>>::iterator itI = icons.begin();
             itI != icons.end(); itI++) {
            for (std::vector<std::pair<std::string, std::pair<std::string, short>>>::iterator it = listBlockId.begin();
                 it != listBlockId.end(); it++) {
                if ((*it).second.first.find("_side.png") != std::string::npos) {
                    (*it).second.first.replace((*it).second.first.find("_side.png"), 9, "");
                }
                if ((*it).second.first.find("_top.png") != std::string::npos) {
                    (*it).second.first.replace((*it).second.first.find("_top.png"), 8, "");
                }
                if ((*itI).second.find("_side") != std::string::npos) {
                    (*itI).second.replace((*itI).second.find("_side"), 5, "");
                }
                if ((*itI).second.find("_top") != std::string::npos) {
                    (*itI).second.replace((*itI).second.find("_top"), 4, "");
                }
                std::size_t found = (*it).second.first.find((*itI).second);
                if (found != std::string::npos) {
                    _listCubeId[(*itI).first - 2] = (*it).second.second;
                }
            }
        }

        resetListCubeId(&_listCubeId);

        _listIcons.insert(_listIcons.end(), icons.begin(), icons.end());
        _img->setImages(_listIcons);
    } catch (std::exception &e) {
        _listIcons.clear();
        _img->setImages(_listIcons);
        std::cout << "Repository doesn't exist: " << e.what() << std::endl;
    }
}

void Ucraft::Inventory::clearListIcons() {
    _listIcons.clear();
}

void Ucraft::Inventory::setCallback(uScreen *screen, const std::string &path, const std::string &pluginName,
                                    std::vector<std::pair<std::string, std::pair<std::string, short>>> listBlockId) {
    int sizeX = ((int) (((float) (screen->getWidth()) / 100.00) * 100));
    int sizeY = (int) (((float) (screen->getHeight()) / 100.00) * 100);
    int sizeBisY = (int) (((float) (screen->getHeight()) / 100.00) * 20);
    int posX = ((int) (((float) (screen->getWidth()) / 100.00) * 0));
    int posY = ((int) (((float) (screen->getHeight()) / 100.00) * 0));

    for (int i = 0; i < _widget->childCount(); i += 1) {
        _widget->removeChild(_widget->childAt(0));
    }
    _size = Eigen::Vector2i(sizeX, 0);
    nanogui::ImagePanel *imgPanel = new nanogui::ImagePanel(_widget);
    try {
        std::vector<std::pair<int, std::string>> icons = nanogui::loadImageDirectory(
                ((nanogui::Screen *) screen)->nvgContext(),
                path + "/Ressources/cacheTexture/" + pluginName);

        for (std::vector<std::pair<int, std::string>>::iterator itI = icons.begin();
             itI != icons.end(); itI++) {
            for (std::vector<std::pair<std::string, std::pair<std::string, short>>>::iterator it = listBlockId.begin();
                 it != listBlockId.end(); it++) {
                std::size_t found = (*itI).second.find((*it).second.first);
                if (found != std::string::npos) {
                    _listCubeId[(*itI).first] = (*it).second.second;
                }
            }
        }

        deleteMultipleTexture(&icons);
        for (std::vector<std::pair<int, std::string>>::iterator itI = icons.begin();
             itI != icons.end(); itI++) {
            for (std::vector<std::pair<std::string, std::pair<std::string, short>>>::iterator it = listBlockId.begin();
                 it != listBlockId.end(); it++) {
                if ((*it).second.first.find("_side.png") != std::string::npos) {
                    (*it).second.first.replace((*it).second.first.find("_side.png"), 9, "");
                }
                if ((*it).second.first.find("_top.png") != std::string::npos) {
                    (*it).second.first.replace((*it).second.first.find("_top.png"), 8, "");
                }
                if ((*itI).second.find("_side") != std::string::npos) {
                    (*itI).second.replace((*itI).second.find("_side"), 5, "");
                }
                if ((*itI).second.find("_top") != std::string::npos) {
                    (*itI).second.replace((*itI).second.find("_top"), 4, "");
                }
                std::size_t found = (*it).second.first.find((*itI).second);
                if (found != std::string::npos) {
                    _listCubeId[(*itI).first - 2] = (*it).second.second;
                }
            }
        }

        resetListCubeId(&_listCubeId);

        imgPanel->setImages(icons);
        imgPanel->setCallback([this, screen](int i) {
            screen->getWorld()->_valueAddBlock = this->getCorrectId(i);
        });
    } catch (std::exception const &e) {
        std::cout << "error on loading texture for inventory : " << e.what() << std::endl;
    }
    imgPanel->setFixedSize(Eigen::Vector2i(1220, 0));
    imgPanel->setVisible(true);
}

Ucraft::Inventory::~Inventory() {};

const int Ucraft::Inventory::getCorrectId(const int id) {
    if (_listCubeId.count(id) > 0) {
        return _listCubeId[id];
    }
    return 101;
}

void Ucraft::Inventory::printObject() {
    _widget->setVisible(true);
}

void Ucraft::Inventory::disableObject() {
    _widget->setVisible(false);
    _hasAlreadyBePrinted = false;
}

void Ucraft::Inventory::setWidget(nanogui::Widget *widget) {
    _widget = widget;
}

void Ucraft::Inventory::setType(const std::string &type) {
    _type = type;
}

void Ucraft::Inventory::setName(const std::string &name) {
    _name = name;
}

const std::string &Ucraft::Inventory::getType() {
    return _type;
}

const std::string &Ucraft::Inventory::getName() {
    return _name;
}

const bool Ucraft::Inventory::getIsPrinted() {
    return _hasAlreadyBePrinted;
}

void Ucraft::Inventory::setIsPrinted(bool isPrinted) {
    _hasAlreadyBePrinted = isPrinted;
}

nanogui::Widget *Ucraft::Inventory::getWidget() {
    return _widget;
}

const int Ucraft::Inventory::getPosX() { return _pos[0]; };

const int Ucraft::Inventory::getPosY() { return _pos[1]; };

const int Ucraft::Inventory::getSizeX() { return _size[0]; };

const int Ucraft::Inventory::getSizeY() { return _size[1]; };
