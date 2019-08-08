//
// Created by Manuel Trambert on 05/12/2017.
//

#include <boost/lexical_cast.hpp>
#include "GUI.hpp"

using namespace nanogui;

/**
 * @param Window class with all of the main window attribute.
 * Constructor of the Ucraft::GUI class which initialise the templates of functions and read the XML to render.
 */
Ucraft::GUI::GUI(uScreen *window, Ucraft::Options *options, char const *path)
        : storeWindow(window), _options(options), _path(path) {
    initMap();
    _templateTheme = new nanogui::Theme(window->nvgContext());
    _messageTheme = new nanogui::Theme(window->nvgContext());
    readJson(path);

    _listGui["components"] = new std::vector<Ucraft::ObjectType *>();
    _listGui["pause"] = new std::vector<Ucraft::ObjectType *>();
    _listGui["options"] = new std::vector<Ucraft::ObjectType *>();
    _listGui["inventory"] = new std::vector<Ucraft::ObjectType *>();
    _guiName = "components";

    GetGui();
    this->initIconMap();
    _path = path;
    _listMessageOut = new std::vector<std::string>;
    _listCommandOut = new std::vector<std::string>;
    _listMessageIn = new std::vector<std::string>;
    _titleWindow = new nanogui::Window(storeWindow, "");
    _titleWindow->setTheme(_messageTheme);
    _titleWindow->setVisible(false);
    _title = new nanogui::Label(_titleWindow, "Bonjour", "sans-bold", 50);
    _loadedPlugins.push_back("all");

}

Ucraft::GUI::~GUI() {

}

void Ucraft::GUI::load() {

    _pluginName = _listPlugins.front();
    _loadedPlugins.push_back(_pluginName);

    /// Inventory components

    Ucraft::Inventory *inGameInventory = new Ucraft::Inventory(Eigen::Vector2i(93, 15), Eigen::Vector2i(7, 80),
                                                               storeWindow, "Inventory", "Inventory", _path);
    _listGui["components"]->push_back(inGameInventory);
    Ucraft::PopupButtonGUI *listPlugins = new PopupButtonGUI(Eigen::Vector2i(93, 3), Eigen::Vector2i(7, 5),
                                                             "arrow_left", "Plugins",
                                                             "PopupButton", this, storeWindow);
    _listGui["components"]->push_back(listPlugins);

    /// Inventory

    WindowGUI *inventory = new WindowGUI(Eigen::Vector2i(0, 0), Eigen::Vector2i(100, 100), "Inventory", "WindowOpen",
                                         storeWindow);
    inventory->getWindow()->window()->setTheme(_templateTheme);
    for (std::list<std::string>::iterator it = _listPlugins.begin();
         it != _listPlugins.end(); it++) {
        listPlugins->addPlugin((*it));
    }

    listPlugins->addPlugin("all");

    inGameInventory->loadInventory(_pluginName, storeWindow, _path, _listBlockId);
    Ucraft::Inventory *tmp = new Inventory(inventory, _pluginName, "Inventory", _path);
    tmp->setCallback(storeWindow, _path, _pluginName, _listBlockId);
    tmp->getWidget()->setTheme(_templateTheme);

    _listGui["inventory"]->push_back(inventory);
}

bool Ucraft::GUI::isPluginLoaded(const std::string &pluginName) {
    for (std::vector<std::string>::iterator it = _loadedPlugins.begin(); it != _loadedPlugins.end(); ++it) {
        if ((*it) == pluginName || (*it) == "all") {
            return true;
        }
    }
    return false;
}

void Ucraft::GUI::reloadInventory() {
    if (_pluginName != "all") {
        for (std::vector<Ucraft::ObjectType *>::iterator it = _listGui["components"]->begin();
             it != _listGui["components"]->end(); it++) {
            if ((*it)->getName() == "Inventory" && (*it)->getType() == "Inventory") {
                Ucraft::ObjectType *tmp = (*it);
                ((Ucraft::Inventory *) tmp)->clearListIcons();
                ((Ucraft::Inventory *) tmp)->loadInventory(_pluginName, storeWindow, _path, _listBlockId);
            }
        }

        if (!isPluginLoaded(_pluginName)) {
            Ucraft::ObjectType *tmp = _listGui["inventory"]->front();
            Ucraft::Inventory *tmpInvent = new Inventory(((Ucraft::WindowGUI *) tmp), _pluginName, "Inventory", _path);
            tmpInvent->setCallback(storeWindow, _path, _pluginName, _listBlockId);
            tmpInvent->getWidget()->setTheme(_templateTheme);
            _loadedPlugins.push_back(_pluginName);
        }

    } else {
        Ucraft::ObjectType *tmp = _listGui["inventory"]->front();
        int i = 0;

        for (std::list<std::string>::iterator itPlugins = _listPlugins.begin();
             itPlugins != _listPlugins.end(); itPlugins++) {
            if ((*itPlugins) != "all" && i != 0) {
                for (std::vector<Ucraft::ObjectType *>::iterator it = _listGui["components"]->begin();
                     it != _listGui["components"]->end(); it++) {
                    if ((*it)->getName() == "Inventory" && (*it)->getType() == "Inventory") {
                        Ucraft::ObjectType *tmp = (*it);
                        ((Ucraft::Inventory *) tmp)->loadInventory((*itPlugins), storeWindow, _path, _listBlockId);
                    }
                }
                Ucraft::Inventory *tmpInvent = new Inventory(((Ucraft::WindowGUI *) tmp), (*itPlugins), "Inventory",
                                                             _path);
                tmpInvent->setCallback(storeWindow, _path, (*itPlugins), _listBlockId);
                tmpInvent->getWidget()->setTheme(_templateTheme);
            }
            i += 1;
        }
    }
}

void Ucraft::GUI::addBlock(const std::string &pluginName, const std::string &blockName, short id) {
    std::pair<std::string, short> tmp(blockName, id);
    _listBlockId.push_back(std::pair<std::string, std::pair<std::string, short>>(pluginName, tmp));
}

void Ucraft::GUI::addPlugin(const std::string &name) {
    _listPlugins.push_back(name);
    _listPlugins.unique();
}

void Ucraft::GUI::setPluginName(const std::string &pluginName) {
    _pluginName = pluginName;
}

const std::string &Ucraft::GUI::getPluginName() {
    return _pluginName;
}

std::vector<std::string> *Ucraft::GUI::getQueueMessageOut() {
    return _listMessageOut;
}

std::vector<std::string> *Ucraft::GUI::getQueueCommandOut() {
    return _listCommandOut;
}

std::vector<std::string> *Ucraft::GUI::getQueueMessageIn() {
    return _listMessageIn;
}

/**
 *
 * @param obj The object to render.
 * @param Ucraft::GUI The current scope of the GUI
 *
 * Function to add an Input text to the current instance of a window. It also prints the history of the chat.
 */
void Ucraft::GUI::addInputText(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    if (!obj->getIsPrinted()) {
        ((InputTextGUI *) obj)->getHistory()->setPointerToGui(gui);
        ((InputTextGUI *) obj)->printObject();
        int posY = (int) (((double) *(_options->getHeight()) / 100.00) * obj->getPosY());
        int posX = (int) (((float) *(_options->getWidth()) / 100.00) * obj->getPosX());
        int sizeY = (int) (((float) *(_options->getHeight()) / 100.00) * obj->getSizeY());
        int sizeX = ((int) (((float) *(_options->getWidth()) / 100.00) * obj->getSizeX()));
        ((InputTextGUI *) obj)->getWidget()->setFixedWidth(sizeX);
        ((InputTextGUI *) obj)->getWidget()->setFixedHeight(sizeY);
        ((InputTextGUI *) obj)->getWidget()->setPosition(Eigen::Vector2i(posX, posY - sizeY));
        ((InputTextGUI *) obj)->setIsPrinted(true);
    }
    if (_options->getResized()) {
        int sizeY = (int) (((float) *(_options->getHeight()) / 100.00) * obj->getSizeY());
        int posY = (int) (((double) *(_options->getHeight()) / 100.00) * obj->getPosY());
        int posX = (int) (((float) *(_options->getWidth()) / 100.00) * obj->getPosX());
        ((InputTextGUI *) obj)->getHistory()->resize();
    }
    if (!(gui->getQueueMessageIn()->empty())) {
        ((InputTextGUI *) obj)->getHistory()->addLine(gui->getQueueMessageIn()->back());
        gui->getQueueMessageIn()->pop_back();
        ((InputTextGUI *) obj)->printObject();
    }
}

/**
 *
 * @param obj The object to render.
 * @param Ucraft::GUI The current scope of the GUI
 *
 * Function to add an Input text to the current instance of a window. It also prints the history of the chat.
 */
void Ucraft::GUI::addText(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    if (!((GuiText *) obj)->getIsPrinted()) {
        int posY = (int) (((double) *(_options->getHeight()) / 100.00) * ((GuiText *) obj)->getPosY());
        int posX = (int) (((float) *(_options->getWidth()) / 100.00) * ((GuiText *) obj)->getPosX());
        ((GuiText *) obj)->getWidget()->setPosition(Eigen::Vector2i(posX, posY));
        ((GuiText *) obj)->printObject();
        ((GuiText *) obj)->setIsPrinted(true);
    }
}

/**
 *
 * @param obj The object to render.
 * @param Ucraft::GUI The current scope of the GUI
 *
 * Function that create a new instance of a window with his associated theme, position and size.
 */
void Ucraft::GUI::newWindow(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    if (!(((WindowGUI *) obj)->getIsPrinted())) {
        int posY = (int) (((float) *(_options->getHeight()) / 100.00) * ((WindowGUI *) obj)->getPosY());
        int posX = (int) (((float) *(_options->getWidth()) / 100.00) * ((WindowGUI *) obj)->getPosX());
        int sizeY = (int) (((float) *(_options->getHeight()) / 100.00) * ((WindowGUI *) obj)->getSizeY());
        int sizeX = (int) (((float) *(_options->getWidth()) / 100.00) * ((WindowGUI *) obj)->getSizeX());
        ((WindowGUI *) obj)->getWidget()->setPosition(Eigen::Vector2i(posX, posY));
        ((WindowGUI *) obj)->getWidget()->setFixedSize(Eigen::Vector2i(sizeX, sizeY));
        ((WindowGUI *) obj)->printObject();
        ((WindowGUI *) obj)->setIsPrinted(true);
    }
}

/**
 *
 * @param obj The object to render.
 * @param Ucraft::GUI The current scope of the GUI
 *
 * Function that close the current context of a window.
 */
void Ucraft::GUI::closeWindow(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    if (debug) {
        std::cout << "Close window" << std::endl;
    }
    // END OF CONTEXT OF CURRENT WINDOW
}

void Ucraft::GUI::addSlider(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    if (!((Ucraft::Slider *) obj)->getIsPrinted()) {
        ((Ucraft::Slider *) obj)->printObject();
        ((Ucraft::Slider *) obj)->setIsPrinted(true);
    }
}

void Ucraft::GUI::addInventory(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    if (!((Ucraft::Inventory *) obj)->getIsPrinted()) {
        ((Ucraft::Inventory *) obj)->printObject();
        ((Ucraft::Inventory *) obj)->setIsPrinted(true);
    }
    if (_options->getResized()) {
        int posX = (int) (((float) *(_options->getWidth()) / 100.00) * ((Ucraft::Inventory *) obj)->getPosX());
        int posY = (int) (((double) *(_options->getHeight()) / 100.00) * ((Ucraft::Inventory *) obj)->getPosY());
        ((Ucraft::Inventory *) obj)->getWidget()->setPosition(Eigen::Vector2i(posX, posY));
    }

}

/**
 *
 * @param obj The object to render.
 * @param Ucraft::GUI The current scope of the GUI
 *
 * Function that add a button to the current context of a window.
 */
void Ucraft::GUI::addButton(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    if (!(((Ucraft::ButtonGUI *) obj)->getIsPrinted())) {
        ((Ucraft::ButtonGUI *) obj)->getWidget()->setFixedHeight(((Ucraft::ButtonGUI *) obj)->getSizeX());
        ((Ucraft::ButtonGUI *) obj)->getWidget()->setFixedWidth(((Ucraft::ButtonGUI *) obj)->getSizeY());
        ((Ucraft::ButtonGUI *) obj)->getWidget()->setPosition(
                Eigen::Vector2i(((Ucraft::ButtonGUI *) obj)->getPosX(), ((Ucraft::ButtonGUI *) obj)->getPosY()));
        ((Ucraft::ButtonGUI *) obj)->setIsPrinted(true);
    }
}

/**
 *
 * @param obj The object to render.
 * @param Ucraft::GUI The current scope of the GUI
 *
 * Function that add a button to the current context of a window.
 */
void Ucraft::GUI::addRadioButton(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    if (!((Ucraft::ButtonGUI *) obj)->getIsPrinted()) {
        ((nanogui::Button *) ((Ucraft::ButtonGUI *) obj)->getWidget())->setFlags(nanogui::Button::RadioButton);
        ((Ucraft::ButtonGUI *) obj)->setIsPrinted(true);
    }
}

void Ucraft::GUI::addPopupButton(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    if (gui->getOptions()->getResized()) {
        int posX = (int) (((float) *(gui->getOptions()->getWidth()) / 100.00) *
                          ((Ucraft::PopupButtonGUI *) obj)->getPosX());
        int posY = (int) (((double) *(gui->getOptions()->getHeight()) / 100.00) *
                          ((Ucraft::PopupButtonGUI *) obj)->getPosY());
        obj->getWidget()->setPosition(Eigen::Vector2i(posX, posY));
    }
    if (!((Ucraft::PopupButtonGUI *) obj)->getIsPrinted()) {
        ((Ucraft::PopupButtonGUI *) obj)->printObject();
        ((Ucraft::PopupButtonGUI *) obj)->setIsPrinted(true);
    }
}

void *ExitProcess(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    exit(EXIT_SUCCESS);
    return NULL;
}

void *options(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    for (std::vector<Ucraft::ObjectType *>::iterator it = gui->getComponents()->begin();
         it != gui->getComponents()->end(); it++) {
        (*it)->disableObject();
        (*it)->setIsPrinted(false);
    }
    gui->setGuiName("options");
    return NULL;
}

void *resize(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    gui->getOptions()->setSize(obj->getPosX(), obj->getPosY());
    gui->getOptions()->setFromMenu(true);
    for (std::vector<Ucraft::ObjectType *>::iterator it = gui->getComponents()->begin();
         it != gui->getComponents()->end(); it++) {
        (*it)->disableObject();
        (*it)->setIsPrinted(false);
    }
    gui->setGuiName("components");
    gui->setGuiActivated(false);
    return nullptr;
}

void Ucraft::GUI::setGuiName(const char *name) {
    _hasChanged = true;
    _guiName = name;
}

void *showPauseMenu(Ucraft::ObjectType *obj, Ucraft::GUI *gui) {
    gui->setGuiName("pause");
    return nullptr;
}

void Ucraft::GUI::InitTitle(const std::string &message) {
    _title->setCaption(message);
    _title->setPosition((Eigen::Vector2i(10, 10)));
    _alpha = 100;
    _mDropShadow = 255;
    _mTextShadow = 255;
    _messageTheme->mWindowFillFocused = nanogui::Color(0, _alpha);
    _messageTheme->mWindowFillUnfocused = nanogui::Color(0, _alpha);
    _messageTheme->mDropShadow = nanogui::Color(92, _mDropShadow);
    _messageTheme->mBorderDark = nanogui::Color(92, _mDropShadow);
    _messageTheme->mTextColor = nanogui::Color(255, _mTextShadow);
    _messageTheme->mDropShadow = nanogui::Color(0, 0);
    _messageTheme->mWindowCornerRadius = 10;
    _title->setTheme(_messageTheme);
    _title->setFont("sans-bold");
    _title->setFontSize(50);
}

void Ucraft::GUI::PrintTitle(const std::string &message, long duration) {
    InitTitle(message);
    _duration = duration;
    TitleTime = std::chrono::high_resolution_clock::now();
    _isTitle = true;
    _lastPointTitle = 0.00;
    _titleWindow->setTheme(_messageTheme);
}

void Ucraft::GUI::reduceAlpha() {
    _titleWindow->setPosition(Eigen::Vector2i(storeWindow->getWidth() / 2 - _title->size()[0] / 2,
                                              storeWindow->getHeight() / 100 * 10));
    _titleWindow->setFixedSize(Eigen::Vector2i(_title->size()[0] + 20, _title->size()[1] + 20));
    _titleWindow->setVisible(true);
    float duration = floorf(std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::high_resolution_clock::now() - TitleTime).count() * 100) / 100;
    if (_isTitle && (_duration - duration < 5) && duration < _duration && _lastPointTitle != duration) {
        _lastPointTitle = duration;
        _alpha -= 0.05;
        _mDropShadow -= 1;
        _mTextShadow -= 2;
        _messageTheme->mWindowFillFocused = nanogui::Color(0, _alpha);
        _messageTheme->mWindowFillUnfocused = nanogui::Color(0, _alpha);
        _messageTheme->mTextColor = nanogui::Color(255, _mTextShadow);
        _title->setTheme(_messageTheme);
        _title->setFont("sans-bold");
        _title->setFontSize(50);
        _titleWindow->setTheme(_messageTheme);
    }
    if (_isTitle && std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::high_resolution_clock::now() - TitleTime).count() > _duration) {
        DeleteTitle();
    }
}

void Ucraft::GUI::DeleteTitle() {
    _alpha = 100;
    _titleWindow->setVisible(false);
    _isTitle = false;
}

/**
 * Function to init the different templates of function inside a map.
 */
void Ucraft::GUI::initMap() {
    GuiComponents["WindowOpen"] = &Ucraft::GUI::newWindow;
    GuiComponents["WindowClose"] = &Ucraft::GUI::closeWindow;
    GuiComponents["InputText"] = &Ucraft::GUI::addInputText;
    GuiComponents["Text"] = &Ucraft::GUI::addText;
    GuiComponents["Button"] = &Ucraft::GUI::addButton;
    GuiComponents["RadioButton"] = &Ucraft::GUI::addRadioButton;
    GuiComponents["Slider"] = &Ucraft::GUI::addSlider;
    GuiComponents["Inventory"] = &Ucraft::GUI::addInventory;
    GuiComponents["PopupButton"] = &Ucraft::GUI::addPopupButton;
    _listFunc["exit"] = &ExitProcess;
    _listFunc["pause"] = &showPauseMenu;
    _listFunc["resize"] = &resize;
    _listFunc["options"] = &options;
}

bool specialStrcmp(char *str, std::string cmp) {
    if (strlen(str) != cmp.length())
        return false;
    for (int i = 0; i < cmp.length(); i += 1) {
        if (cmp.at(i) != str[i])
            return false;
    }
    return true;
}

std::vector<Ucraft::ObjectType *> *Ucraft::GUI::getComponents() {
    return _listGui[_guiName];
}

void Ucraft::GUI::readJson(const std::string &path) {
    nlohmann::json jsonFile;

    _messageTheme->mWindowHeaderHeight = 0;
    _messageTheme->mWindowCornerRadius = 0;
    _messageTheme->mWindowFillFocused = nanogui::Color(0, _alpha);
    _messageTheme->mWindowFillUnfocused = nanogui::Color(0, _alpha);
    try {
        std::ifstream i(path + "/Ressources/theme.json");
        i >> jsonFile;
        _templateTheme->mWindowHeaderHeight = jsonFile["window"]["headerHeight"];
        _templateTheme->mWindowCornerRadius = jsonFile["window"]["radius"];
        _templateTheme->mWindowFillFocused = nanogui::Color((int) jsonFile["window"]["colorFocused"]["intensity"],
                                                            (int) jsonFile["window"]["colorFocused"]["alpha"]);
        _templateTheme->mWindowFillUnfocused = nanogui::Color((int) jsonFile["window"]["colorUnfocused"]["intensity"],
                                                              (int) jsonFile["window"]["colorUnfocused"]["alpha"]);
    } catch (std::exception &e) {
        std::cout << "Exception on json read :" << e.what() << std::endl;
    }
}

void Ucraft::GUI::GetGui() {

    /// Options section
    Ucraft::WindowGUI *tmpOptions = new Ucraft::WindowGUI(49, 49, "", "WindowOpen", storeWindow);
    tmpOptions->getWindow()->window()->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical,
                                                                        nanogui::Alignment::Middle, 20, 20));

    tmpOptions->getWindow()->window()->setTheme(_templateTheme);
    _listGui["options"]->push_back(tmpOptions);
    _listGui["options"]->push_back(new ButtonGUI(Eigen::Vector2i(860, 480), Eigen::Vector2i(50, 150),
                                                 "validate", "860x480", "RadioButton", _listFunc["resize"], this,
                                                 tmpOptions));
    _listGui["options"]->push_back(new ButtonGUI(Eigen::Vector2i(1280, 720), Eigen::Vector2i(50, 150),
                                                 "validate", "1280x720", "RadioButton", _listFunc["resize"], this,
                                                 tmpOptions));
    _listGui["options"]->push_back(new ButtonGUI(Eigen::Vector2i(1920, 1200), Eigen::Vector2i(50, 150),
                                                 "validate", "1920x1200", "RadioButton", _listFunc["resize"], this,
                                                 tmpOptions));
    _listGui["options"]->push_back(
            new Ucraft::Slider(Eigen::Vector2i(0, 0), Eigen::Vector2i(0, 0), Eigen::Vector2f(70.0, 100.0), tmpOptions,
                               storeWindow, "FOV",
                               "Slider"));

    /// Pause section
    Ucraft::WindowGUI *tmp = new Ucraft::WindowGUI(50, 50, "", "WindowOpen", storeWindow);
    tmp->getWindow()->window()->setTheme(_templateTheme);
    tmp->getWindow()->window()->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical,
                                                                 nanogui::Alignment::Middle, 20, 20));
    _listGui["pause"]->push_back(tmp);
    _listGui["pause"]->push_back(new ButtonGUI(Eigen::Vector2i(0, 0), Eigen::Vector2i(50, 150),
                                               "validate", "Options", "Button", _listFunc["options"], this, tmp));
    _listGui["pause"]->push_back(new ButtonGUI(Eigen::Vector2i(0, 0), Eigen::Vector2i(50, 150),
                                               "cross", "Exit", "Button", _listFunc["exit"], this, tmp));

    /// Components section
    _listGui["components"]->push_back(new InputTextGUI(
            Eigen::Vector2i(1, 100), Eigen::Vector2i(50, 5),
            storeWindow, "Chat", "InputText", storeWindow));
    _listGui["components"]->push_back(new GuiText(Eigen::Vector2i(50, 50),
                                                  Eigen::Vector2i(0, 0), storeWindow, 50, "+", "Text"));
}

void Ucraft::GUI::setGuiActivated(bool act) {
    GuiActivated = act;
}