#pragma once

#include <iostream>
#include <string>


#include "GUI.hpp"
#include "Loader.h"
#include "ModelView.h"
#include "CubeFactory.h"
#include "World.h"
#include "UOptions.h"
#include "UViewer.h"
#include "uScreen.h"

#include <nanogui/nanogui.h> 

namespace Ucraft {

    class Window {
    public:
        Window(Ucraft::Options *);

        void setSize(int w, int h) {
            _options->setSize(w, h);
            _options->setResized(true);
        }

        void setWorld(World *world, char const *path);

        float getAspect() const;

        GLFWwindow *getGLWwindow() const;

        UViewer *getCamera() { return &_camera; }

        int *getWindowW() { return &display_w; }

        int *getWindowH() { return &display_h; }

        int getWidth() { return *(_options->getWidth()); };

        int getHeight() { return *(_options->getHeight()); };

        int getKeepAlive() const { return _keepAlive; }

        Ucraft::Options *getOptions() { return _options; }

        void setKeepAlive(int keepAlive) { _keepAlive = keepAlive; }

        void printAll();

        void updateInfo(ObjectType *);

        GUI *getGui() { return _gui; }

        typedef void (GUI::*GuiFunc)(ObjectType *, GUI *);

        typedef std::map<std::string, GuiFunc> GuiFuncMap;

        uScreen *getNanoGUIScreen() { return _uScreen; }

        void pickingBlock();

    private:
        GLFWwindow *window;
        ShaderProgram *m_shaderProgram;
        GUI *_gui;

        UViewer _camera;
        uScreen *_uScreen;

        Ucraft::Options *_options;

        int setup();

        World *_world;
        int display_w;
        int display_h;

        int _keepAlive;

    public:
        Model m_model;

    };

}
