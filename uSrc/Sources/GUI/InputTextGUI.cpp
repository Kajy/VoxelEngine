#include "inputTextGUI.h"

Ucraft::InputTextGUI::InputTextGUI(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, nanogui::Widget *parent,
                                   const std::string &name, const std::string &type, nanogui::Widget *screen) {
    setType(type);
    _size = size;
    _pos = pos;
    _name = name;
    _hasAlreadyBePrinted = false;
    _history = new History(screen, this, 1);
    _widget = new nanogui::TextBox(parent);
    ((nanogui::TextBox *) _widget)->setAlignment(nanogui::TextBox::Alignment::Left);
    ((nanogui::TextBox *) _widget)->setFontSize(25);
    if (_name != "History") {
        ((nanogui::TextBox *) _widget)->setEditable(true);
    }
    ((nanogui::TextBox *) _widget)->setValue("");
    ((nanogui::TextBox *) _widget)->setPlaceholder(_name);

    ((nanogui::TextBox *) _widget)->setCallback([this](const std::string &value) {
        std::istringstream iss(value);
        std::string w, result;

        if (iss >> w) { result += w; }
        while (iss >> w) { result += ' ' + w; }
        if (result == "/pluginEditor") {
            openPluginEditor();
            _history->onUnfocus();
            ((nanogui::TextBox *) _widget)->setValue("");
        } else {
            sendValueToHistory(result);
            _history->onUnfocus();
            ((nanogui::TextBox *) _widget)->setValue("");
        }
        return true;
    });
    ((nanogui::TextBox *) _widget)->setVisible(false);
    mapKeyboard();
};

Ucraft::InputTextGUI::~InputTextGUI() {};

void Ucraft::InputTextGUI::mapKeyboard() {
    _keyboard[UCRAFT_KEY_A_ACCENT] = "à";
    _keyboard[UCRAFT_KEY_DOUBLE_COTE] = "\"";
    _keyboard[UCRAFT_KEY_SIMPLE_COTE] = "'";
    _keyboard[UCRAFT_KEY_PARENTHESIS] = "(";
    _keyboard[UCRAFT_KEY_STRANGE] = "§";
    _keyboard[UCRAFT_KEY_ACCENT_GRAVE] = "è";
    _keyboard[UCRAFT_KEY_EXCLAMATION] = "!";
    _keyboard[UCRAFT_KEY_CEDILLA] = "ç";
    _keyboard[UCRAFT_KEY_ESPER] = "&";
    _keyboard[UCRAFT_KEY_E_ACCENT] = "é";

    _keyboard[UCRAFT_KEY_EQUAL] = "=";
    _keyboard[UCRAFT_KEY_SEMICOLON] = ";";
    _keyboard[UCRAFT_KEY_9] = "9";
    _keyboard[UCRAFT_KEY_8] = "8";
    _keyboard[UCRAFT_KEY_7] = "7";
    _keyboard[UCRAFT_KEY_6] = "6";
    _keyboard[UCRAFT_KEY_5] = "5";
    _keyboard[UCRAFT_KEY_4] = "4";
    _keyboard[UCRAFT_KEY_3] = "3";
    _keyboard[UCRAFT_KEY_2] = "2";
    _keyboard[UCRAFT_KEY_1] = "1";
    _keyboard[UCRAFT_KEY_0] = "0";
    _keyboard[UCRAFT_KEY_SLASH] = "/";
    _keyboard[UCRAFT_KEY_POINT] = ".";
    _keyboard[UCRAFT_KEY_DOUBLE_POINT] = ":";
    _keyboard[UCRAFT_KEY_PLUS] = "+";
    _keyboard[UCRAFT_KEY_MINUS] = "-";
    _keyboard[UCRAFT_KEY_COMMA] = ",";
    _keyboard[UCRAFT_KEY_INTER] = "?";
    _keyboard[UCRAFT_KEY_APOSTROPHE] = "'";
    _keyboard[UCRAFT_KEY_SPACE] = " ";

    _keyboard[UCRAFT_KEY_RIGHT_BRACKET] = "]";
    _keyboard[UCRAFT_KEY_BACKSLASH] = "\\";
    _keyboard[UCRAFT_KEY_LEFT_BRACKET] = "[";
    _keyboard[UCRAFT_KEY_Z] = "Z";
    _keyboard[UCRAFT_KEY_LOW_Z] = "z";
    _keyboard[UCRAFT_KEY_Y] = "Y";
    _keyboard[UCRAFT_KEY_LOW_Y] = "y";
    _keyboard[UCRAFT_KEY_X] = "X";
    _keyboard[UCRAFT_KEY_LOW_X] = "x";
    _keyboard[UCRAFT_KEY_W] = "W";
    _keyboard[UCRAFT_KEY_LOW_W] = "w";
    _keyboard[UCRAFT_KEY_V] = "V";
    _keyboard[UCRAFT_KEY_LOW_V] = "v";
    _keyboard[UCRAFT_KEY_U] = "U";
    _keyboard[UCRAFT_KEY_LOW_U] = "u";
    _keyboard[UCRAFT_KEY_T] = "T";
    _keyboard[UCRAFT_KEY_LOW_T] = "t";
    _keyboard[UCRAFT_KEY_S] = "S";
    _keyboard[UCRAFT_KEY_LOW_S] = "s";
    _keyboard[UCRAFT_KEY_R] = "R";
    _keyboard[UCRAFT_KEY_LOW_R] = "r";
    _keyboard[UCRAFT_KEY_Q] = "Q";
    _keyboard[UCRAFT_KEY_LOW_Q] = "q";
    _keyboard[UCRAFT_KEY_P] = "P";
    _keyboard[UCRAFT_KEY_LOW_P] = "p";
    _keyboard[UCRAFT_KEY_O] = "O";
    _keyboard[UCRAFT_KEY_LOW_O] = "o";
    _keyboard[UCRAFT_KEY_N] = "N";
    _keyboard[UCRAFT_KEY_LOW_N] = "n";
    _keyboard[UCRAFT_KEY_M] = "M";
    _keyboard[UCRAFT_KEY_LOW_M] = "m";
    _keyboard[UCRAFT_KEY_L] = "L";
    _keyboard[UCRAFT_KEY_LOW_L] = "l";
    _keyboard[UCRAFT_KEY_K] = "K";
    _keyboard[UCRAFT_KEY_LOW_K] = "k";
    _keyboard[UCRAFT_KEY_J] = "J";
    _keyboard[UCRAFT_KEY_LOW_J] = "j";
    _keyboard[UCRAFT_KEY_I] = "I";
    _keyboard[UCRAFT_KEY_LOW_I] = "i";
    _keyboard[UCRAFT_KEY_H] = "H";
    _keyboard[UCRAFT_KEY_LOW_H] = "h";
    _keyboard[UCRAFT_KEY_G] = "g";
    _keyboard[UCRAFT_KEY_LOW_G] = "g";
    _keyboard[UCRAFT_KEY_F] = "F";
    _keyboard[UCRAFT_KEY_LOW_F] = "f";
    _keyboard[UCRAFT_KEY_E] = "E";
    _keyboard[UCRAFT_KEY_LOW_E] = "e";
    _keyboard[UCRAFT_KEY_D] = "D";
    _keyboard[UCRAFT_KEY_LOW_D] = "d";
    _keyboard[UCRAFT_KEY_C] = "C";
    _keyboard[UCRAFT_KEY_LOW_C] = "c";
    _keyboard[UCRAFT_KEY_B] = "B";
    _keyboard[UCRAFT_KEY_LOW_B] = "b";
    _keyboard[UCRAFT_KEY_A] = "A";
    _keyboard[UCRAFT_KEY_LOW_A] = "a";
}

void Ucraft::InputTextGUI::openPluginEditor() {
    std::thread pluginStart(system, "npm start --prefix './uSrc/Sources/PluginEditor'");
    pluginStart.join();
}

void Ucraft::InputTextGUI::WriteOnInput(int key, int scancode, int action, int mods) {
    if (mods == 1) {
        key += 100;
    }

    if (key < 191 && key > 31) {
        ((nanogui::TextBox *) _widget)->setTempValue(((nanogui::TextBox *) _widget)->tempValue() + _keyboard[key]);
        ((nanogui::TextBox *) _widget)->moveCursor(1);
    }
}

Ucraft::History *Ucraft::InputTextGUI::getHistory() {
    return _history;
}

void Ucraft::InputTextGUI::sendValueToHistory(const std::string &value) {
    _history->sendLine(value);
}

void Ucraft::InputTextGUI::printObject() {
    _history->printObject();
    ((nanogui::TextBox *) _widget)->setVisible(true);
}

void Ucraft::InputTextGUI::disableObject() {
    _history->disableObject();
    ((nanogui::TextBox *) _widget)->setVisible(false);
    _hasAlreadyBePrinted = false;
}

void Ucraft::InputTextGUI::setWidget(nanogui::Widget *widget) {
    _widget = widget;
}

void Ucraft::InputTextGUI::setType(const std::string &type) {
    _type = type;
}

void Ucraft::InputTextGUI::setName(const std::string &name) {
    _name = name;
}

const std::string &Ucraft::InputTextGUI::getType() {
    return _type;
}

const std::string &Ucraft::InputTextGUI::getName() {
    return _name;
}

const bool Ucraft::InputTextGUI::getIsPrinted() {
    return _hasAlreadyBePrinted;
}

void Ucraft::InputTextGUI::setIsPrinted(bool isPrinted) {
    _hasAlreadyBePrinted = isPrinted;
}

nanogui::Widget *Ucraft::InputTextGUI::getWidget() {
    return _widget;
}

const int Ucraft::InputTextGUI::getPosX() { return _pos[0]; };

const int Ucraft::InputTextGUI::getPosY() { return _pos[1]; };

const int Ucraft::InputTextGUI::getSizeX() { return _size[0]; };

const int Ucraft::InputTextGUI::getSizeY() { return _size[1]; };