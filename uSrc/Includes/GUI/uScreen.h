#pragma once

#include "World.h"
#include "ModelView.h"
#include <nanogui/screen.h>
#include <glm/glm.hpp>

namespace Ucraft {
    class uScreen : public nanogui::Screen {
    public:
        uScreen(World *world, Model *model, UViewer *camera, int *w, int *h) :
                _world(world),
                _model(model),
                _camera(camera),
                _width(w),
                _height(h) {
            mBackground[0] = 0.53;
            mBackground[1] = 0.81;
            mBackground[2] = 0.98;
            mBackground[3] = 1.00;
            _fov = 100.0f;
        };

        void setModel(Model *model) {
            _model = model;
        }

        const int getWidth() const {
            return *_width;
        }

        const int getHeight() const {
            return *_height;
        }

        void setScreenSize(int w, int h) {
            *_width = w;
            *_height = h;
        }

        const Eigen::Vector2i getScreenSize() {
            return Eigen::Vector2i(*_width, *_height);
        }

        void drawContents() {

            glm::mat4 view = glm::lookAt(_camera->getPosCamera(), _camera->getPosLookAt(), _camera->getUpVector());
            glm::mat4 projection = glm::perspective(glm::radians(_fov), *_width / (float) *_height, 0.1f, 500.f);

            _model->glPushMatrix();
            _world->drawWorld(view, projection);
            _model->glPopMatrix();
        }

        void setFov(float fov) {
            _fov = fov;
        }

        World *getWorld() {
            return _world;
        }

        UViewer *getCamera() {
            return _camera;
        }

    private:
        World *_world;
        Model *_model;
        UViewer *_camera;
        int *_width, *_height;
        glm::mat4 view;
        glm::mat4 projection;
        float _fov;
    };
}