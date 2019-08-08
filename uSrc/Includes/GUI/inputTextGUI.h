//
// Created by Manuel Trambert on 21/05/2018.
//

#ifndef UCRAFT_INPUTTEXT_H
#define UCRAFT_INPUTTEXT_H

#ifdef __linux__
#include <pthread.h>
#endif
#ifdef __WIN32
#include <thread>
#endif

#include <mutex>
#include <iostream>
#include <thread>

#include "ObjectType.h"
#include "GuiText.h"
#include "History.h"

#define UCRAFT_KEY_UNKNOWN            -1

/* Printable keys */
#define UCRAFT_KEY_SPACE              32
#define UCRAFT_KEY_APOSTROPHE         39  /* ' */
#define UCRAFT_KEY_MINUS              61  /* - */
#define UCRAFT_KEY_0                  148
#define UCRAFT_KEY_1                  149
#define UCRAFT_KEY_2                  150
#define UCRAFT_KEY_3                  151
#define UCRAFT_KEY_4                  152
#define UCRAFT_KEY_5                  153
#define UCRAFT_KEY_6                  154
#define UCRAFT_KEY_7                  155
#define UCRAFT_KEY_8                  156
#define UCRAFT_KEY_9                  157

#define UCRAFT_KEY_A_ACCENT                 48
#define UCRAFT_KEY_DOUBLE_COTE                  51
#define UCRAFT_KEY_SIMPLE_COTE                  52
#define UCRAFT_KEY_PARENTHESIS                  53
#define UCRAFT_KEY_STRANGE                  54
#define UCRAFT_KEY_ACCENT_GRAVE                  55
#define UCRAFT_KEY_EXCLAMATION                  56
#define UCRAFT_KEY_CEDILLA                  57
#define UCRAFT_KEY_ESPER                 49
#define UCRAFT_KEY_E_ACCENT                  50

#define UCRAFT_KEY_SEMICOLON          44  /* ; */
#define UCRAFT_KEY_POINT              144  /* ; */
#define UCRAFT_KEY_DOUBLE_POINT       46  /* / */
#define UCRAFT_KEY_LOW_M              59
#define UCRAFT_KEY_EQUAL              47  /* = */
#define UCRAFT_KEY_PLUS               147  /* + */
#define UCRAFT_KEY_LOW_A              81
#define UCRAFT_KEY_LOW_B              66
#define UCRAFT_KEY_LOW_C              67
#define UCRAFT_KEY_LOW_D              68
#define UCRAFT_KEY_LOW_E              69
#define UCRAFT_KEY_LOW_F              70
#define UCRAFT_KEY_LOW_G              71
#define UCRAFT_KEY_LOW_H              72
#define UCRAFT_KEY_LOW_I              73
#define UCRAFT_KEY_LOW_J              74
#define UCRAFT_KEY_LOW_K              75
#define UCRAFT_KEY_LOW_L              76
#define UCRAFT_KEY_COMMA              77  /* , */
#define UCRAFT_KEY_INTER              177  /* , */
#define UCRAFT_KEY_LOW_N              78
#define UCRAFT_KEY_LOW_O              79
#define UCRAFT_KEY_LOW_P              80
#define UCRAFT_KEY_LOW_Q              65
#define UCRAFT_KEY_LOW_R              82
#define UCRAFT_KEY_LOW_S              83
#define UCRAFT_KEY_LOW_T              84
#define UCRAFT_KEY_LOW_U              85
#define UCRAFT_KEY_LOW_V              86
#define UCRAFT_KEY_LOW_W              90
#define UCRAFT_KEY_LOW_X              88
#define UCRAFT_KEY_LOW_Y              89
#define UCRAFT_KEY_LOW_Z              87
#define UCRAFT_KEY_LEFT_BRACKET       91  /* [ */
#define UCRAFT_KEY_BACKSLASH          92  /* \ */
#define UCRAFT_KEY_RIGHT_BRACKET      93  /* ] */
#define UCRAFT_KEY_GRAVE_ACCENT       96  /* ` */

#define UCRAFT_KEY_SLASH              146  /* / */
#define UCRAFT_KEY_M                  159
#define UCRAFT_KEY_Q                  165
#define UCRAFT_KEY_B                  166
#define UCRAFT_KEY_C                  167
#define UCRAFT_KEY_D                  168
#define UCRAFT_KEY_E                  169
#define UCRAFT_KEY_F                  170
#define UCRAFT_KEY_G                  171
#define UCRAFT_KEY_H                  172
#define UCRAFT_KEY_I                  173
#define UCRAFT_KEY_J                  174
#define UCRAFT_KEY_K                  175
#define UCRAFT_KEY_L                  176
#define UCRAFT_KEY_N                  178
#define UCRAFT_KEY_O                  179
#define UCRAFT_KEY_P                  180
#define UCRAFT_KEY_A                  181
#define UCRAFT_KEY_R                  182
#define UCRAFT_KEY_S                  183
#define UCRAFT_KEY_T                  184
#define UCRAFT_KEY_U                  185
#define UCRAFT_KEY_V                  186
#define UCRAFT_KEY_Z                  187
#define UCRAFT_KEY_X                  188
#define UCRAFT_KEY_Y                  189
#define UCRAFT_KEY_W                  190

namespace Ucraft {
    class InputTextGUI : public ObjectType {
    public:
        /**
         *
         * @param name Name of the object
         * @param type Type of the object
         *
         * Constructor to create an InputText object.
         */
        InputTextGUI(const Eigen::Vector2i &pos, const Eigen::Vector2i &size, nanogui::Widget *parent,
                     const std::string &name = "No name", const std::string &type = "No type",
                     nanogui::Widget *screen = nullptr);

        ~InputTextGUI();

        const std::string getText();

        void setText(const std::string &text);

        History *getHistory();

        void sendValueToHistory(const std::string &value);

        void mapKeyboard();

        void WriteOnInput(int key, int scancode, int action, int mods);

        void openPluginEditor();

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
        Ucraft::History *_history;
        std::map<int, std::string> _keyboard;
    };
}

#endif //UCRAFT_INPUTTEXT_H
