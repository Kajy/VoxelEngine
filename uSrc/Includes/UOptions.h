#pragma once

namespace Ucraft {
    class Options {

    public:
        Options(int w, int h);

        ~Options() {};

        int *getWidth();

        int *getHeight();

        void setSize(const int, const int);

        void setResized(bool);

        bool getResized();

        bool isFromMenu();

        void setFromMenu(bool);

    private:
        int _width;
        int _height;
        bool _resized;
        bool _fromMenu;
    };
};
