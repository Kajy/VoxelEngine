#include "ObjectType.h"
#include "WindowGUI.h"
#include "Texture.h"
#include "inputTextGUI.h"
#include "ButtonGUI.h"
#include "PopupButtonGUI.h"
#include "UOptions.h"
#include "Window.h"
#include "Slider.h"
#include "uScreen.h"
#include "Inventory.h"
#include "nlohmann/json.hpp"

#include <time.h>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <nanogui/entypo.h>
#include <nanogui/theme.h>

#ifndef UGUI_HEADER
#define UGUI_HEADER

namespace Ucraft {
class GUI {
public:
    GUI(uScreen *, Ucraft::Options *options, char const *);

    virtual ~GUI();

    void GetGui();

    void initMap();

    void addPlugin(const std::string &);

    void setPluginName(const std::string &);

    const std::string &getPluginName();

    void reloadInventory();

    void load();

    void newWindow(Ucraft::ObjectType *, Ucraft::GUI *);

    void closeWindow(Ucraft::ObjectType *, Ucraft::GUI *);

    void addInputText(Ucraft::ObjectType *, Ucraft::GUI *);

    void addButton(Ucraft::ObjectType *, Ucraft::GUI *);

    void addRadioButton(Ucraft::ObjectType *, Ucraft::GUI *);

    void addPopupButton(Ucraft::ObjectType *, Ucraft::GUI *);

    void addSlider(Ucraft::ObjectType *, Ucraft::GUI *);

    void addInventory(Ucraft::ObjectType *, Ucraft::GUI *);

    void addGrid(Ucraft::ObjectType *, Ucraft::GUI *);

    void addText(Ucraft::ObjectType *, Ucraft::GUI *);

    void addBlock(const std::string &, const std::string &, short);

    void readJson(const std::string &);

    void printGUI();

    void addPause();

    bool isPluginLoaded(const std::string &pluginName);

    void setGuiActivated(bool);

    std::vector<std::string> *getQueueMessageOut();

    std::vector<std::string> *getQueueCommandOut();

    std::vector<std::string> *getQueueMessageIn();

    void PrintTitle(const std::string &message, long duration);

    void InitTitle(const std::string &message);

    void reduceAlpha();

    void DeleteTitle();

    typedef void (Ucraft::GUI::*GuiFunc)(Ucraft::ObjectType *, Ucraft::GUI *);

    typedef std::map<std::string, GuiFunc> GuiFuncMap;

    Ucraft::Options *getOptions() {
        return _options;
    }

    const bool getGuiActivated() {
        return GuiActivated;
    }

    std::vector<Ucraft::ObjectType *> *getComponents();

    const std::string &getGuiName() {
        return _guiName;
    }

    void setGuiName(const char *name);

    uScreen *getWindow() {
        return storeWindow;
    }

    bool hasChanged() {
        return _hasChanged;
    }

    void setChanged(bool state) {
        _hasChanged = true;
    }

    const int getIcon(const std::string iconName) {
        return _iconList[iconName];
    }

    std::vector<Ucraft::ObjectType *> *getCurrentGui() {
        return _listGui[_guiName];
    }
    Ucraft::ObjectType *getParent() { return nullptr; };

    const void initIconMap() {
        _iconList["infinite"] = ENTYPO_ICON_500PX;
        _iconList["arrow_up"] = ENTYPO_ICON_ARROW_UP;
        _iconList["arrow_right"] = ENTYPO_ICON_ARROW_RIGHT;
        _iconList["arrow_left"] = ENTYPO_ICON_ARROW_LEFT;
        _iconList["arrow_down"] = ENTYPO_ICON_ARROW_DOWN;
        _iconList["validate"] = ENTYPO_ICON_CHECK;
        _iconList["cross"] = ENTYPO_ICON_CROSS;
        _iconList["reload"] = ENTYPO_ICON_CW;
        _iconList["play"] = ENTYPO_ICON_CONTROLLER_PLAY;
    }

    GuiFuncMap *getFuncMap() {
        return &GuiComponents;
    }
    int _duration = 0;
    bool _isTitle = false;

private:
    GuiFuncMap GuiComponents;
    bool _init = false;
    bool debug = false;
    bool GuiActivated = false;
    bool _hasChanged = true;
    uScreen *storeWindow;
    std::map<std::string,std::vector<Ucraft::ObjectType *> *> _listGui;
    std::map<std::string, int> _iconList;
    std::map<std::string, OnActionFuncButton*> _listFunc;
    nanogui::Window *_titleWindow;
    nanogui::Label *_title;
    Ucraft::Options *_options;
    std::string	_path;
    std::string _guiName;
    std::string _pluginName;
    std::vector<std::string> *_listMessageOut;
    std::vector<std::string> *_listCommandOut;
    std::vector<std::string> *_listMessageIn;
    std::vector<std::string> _loadedPlugins;
    std::list<std::string> _listPlugins;
    std::vector<std::pair<std::string, std::pair<std::string, short>>> _listBlockId;
    nanogui::Theme *_templateTheme;
    nanogui::Theme *_messageTheme;
    int _alpha = 100;
    int _mDropShadow  = 255;
    int _mTextShadow  = 255;
    std::chrono::high_resolution_clock::time_point TitleTime;
    float _lastPointTitle = 0.00;
};
}

#endif