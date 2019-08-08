#include "Event.h"

Event *g_event;

Event::Event() {
}

Event::Event(Ucraft::Window *window, World *world) {
    m_win = window;
    m_world = world;
    g_event = this;
    _movementSpeedCam = 10;

    for (int i = 0; i < 512; ++i)
        keybordButtons[i] = false;
    g_event->m_lastMouseX = g_event->m_win->getWidth();
    g_event->m_lastMouseY = g_event->m_win->getHeight();

    g_event->cx = g_event->m_win->getWidth();
    g_event->cy = g_event->m_win->getHeight();
    _guiState = false;
}

Event::~Event() {
}

void Event::AllCallback() {
    glfwSetKeyCallback(m_win->getGLWwindow(), key_callback);
    glfwSetWindowSizeCallback(m_win->getGLWwindow(), window_size_callback);
    glfwSetMouseButtonCallback(m_win->getGLWwindow(), mouse_button_callback);
    glfwSetCursorPosCallback(m_win->getGLWwindow(), cursor_pos_callback);
}

void Event::window_size_callback(GLFWwindow *window, int width, int height) {
    g_event->m_win->setSize(width, height);
    for (std::vector<Ucraft::ObjectType *>::iterator it = g_event->m_win->getGui()->getComponents()->begin();
         it != g_event->m_win->getGui()->getComponents()->end(); it++) {
        (*it)->disableObject();
    }
    g_event->m_win->getGui()->setGuiName("components");
    g_event->_guiState = false;
    g_event->m_win->getGui()->setGuiActivated(false);
    glfwSetInputMode(g_event->m_win->getGLWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Event::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    g_event->_guiState = g_event->m_win->getGui()->getGuiActivated();
    if (key >= 0 && key < 512) {
        if (!g_event->_guiState && action == GLFW_PRESS && key != GLFW_KEY_ESCAPE) {
            g_event->keybordButtons[key] = true;
        } else if (!g_event->_guiState && action == GLFW_RELEASE && key != GLFW_KEY_ESCAPE) {
            g_event->keybordButtons[key] = false;
        } else if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
            if (!g_event->_guiState) {
                for (std::vector<Ucraft::ObjectType *>::iterator it = g_event->m_win->getGui()->getComponents()->begin();
                     it != g_event->m_win->getGui()->getComponents()->end(); it++) {
                    (*it)->disableObject();
                }
                g_event->m_win->getGui()->setGuiName("pause");
                g_event->_guiState = true;
                g_event->m_win->getGui()->setGuiActivated(true);
                glfwSetInputMode(g_event->m_win->getGLWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            } else {
                for (std::vector<Ucraft::ObjectType *>::iterator it = g_event->m_win->getGui()->getComponents()->begin();
                     it != g_event->m_win->getGui()->getComponents()->end(); it++) {
                    (*it)->disableObject();
                }
                g_event->m_win->getGui()->setGuiName("components");
                g_event->_guiState = false;
                g_event->m_win->getGui()->setGuiActivated(false);
                glfwSetInputMode(g_event->m_win->getGLWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }
        if (action == GLFW_PRESS && g_event->_guiState && (key == GLFW_KEY_ENTER || key == GLFW_KEY_BACKSPACE)) {
            g_event->m_win->getNanoGUIScreen()->keyCallbackEvent(key, scancode, action, mods);
            if (key == GLFW_KEY_ENTER) {
                g_event->_guiState = false;
                g_event->m_win->getGui()->setGuiActivated(false);
                glfwSetInputMode(g_event->m_win->getGLWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                g_event->m_win->getNanoGUIScreen()->requestFocus();
            }
        } else if (action == GLFW_PRESS && g_event->_guiState) {
            int i = 0;
            for (std::vector<Ucraft::ObjectType *>::iterator it = g_event->m_win->getGui()->getComponents()->begin();
                 i < g_event->m_win->getGui()->getComponents()->size(); it++, i += 1) {
                if ((*it)->getType() == "InputText") {
                    ((Ucraft::InputTextGUI *) (*it))->WriteOnInput(key, scancode, action, mods);
                }
            }
        } else if (action == GLFW_PRESS && !g_event->_guiState && key == GLFW_KEY_ENTER) {
            int i = 0;
            for (std::vector<Ucraft::ObjectType *>::iterator it = g_event->m_win->getGui()->getComponents()->begin();
                 i < g_event->m_win->getGui()->getComponents()->size(); it++, i += 1) {
                if ((*it)->getType() == "InputText") {
                    (*it)->getWidget()->requestFocus();
                    glfwSetInputMode(g_event->m_win->getGLWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    ((Ucraft::InputTextGUI *) (*it))->getHistory()->onFocus();
                    g_event->_guiState = true;
                    g_event->m_win->getGui()->setGuiActivated(true);
                }
            }
        }
        if (!g_event->_guiState && action == GLFW_PRESS && key == GLFW_KEY_I) {
            if (g_event->m_win->getGui()->getGuiName() == "inventory") {
                for (std::vector<Ucraft::ObjectType *>::iterator it = g_event->m_win->getGui()->getComponents()->begin();
                     it != g_event->m_win->getGui()->getComponents()->end(); it++) {
                    (*it)->disableObject();
                }
                g_event->m_win->getGui()->setGuiName("components");
                g_event->_guiState = false;
                g_event->m_win->getGui()->setGuiActivated(false);
                glfwSetInputMode(g_event->m_win->getGLWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            } else {
                for (std::vector<Ucraft::ObjectType *>::iterator it = g_event->m_win->getGui()->getComponents()->begin();
                     it != g_event->m_win->getGui()->getComponents()->end(); it++) {
                    (*it)->disableObject();
                }
                g_event->m_win->getGui()->setGuiName("inventory");
                for (std::vector<Ucraft::ObjectType *>::iterator it = g_event->m_win->getGui()->getComponents()->begin();
                     it != g_event->m_win->getGui()->getComponents()->end(); it++) {
                    ((Ucraft::WindowGUI *) (*it))->resizeInventory(g_event->m_win->getNanoGUIScreen());
                }
                g_event->_guiState = true;
                g_event->m_win->getGui()->setGuiActivated(true);
                glfwSetInputMode(g_event->m_win->getGLWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
    }
    if (key == GLFW_KEY_PAGE_UP) {
        g_event->m_world->_valueAddBlock++;
        g_event->m_world->_valueAddBlock %= 5;
    } else if (key == GLFW_KEY_PAGE_DOWN) {
        g_event->m_world->_valueAddBlock--;
        g_event->m_world->_valueAddBlock %= 5;
    }
}

void Event::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == 0 && action == GLFW_RELEASE && !g_event->_guiState) {
        g_event->m_world->addBreakBlockEvent(glm::ivec4(g_event->m_world->getPlayerInfos()->getPlayerPickingBlock()._cubePos, 0));
    }
    if (button == 1 && action == GLFW_RELEASE && !g_event->_guiState) {
        g_event->m_world->addAddBlockEvent(glm::ivec4(
                g_event->m_world->getPlayerInfos()->getPlayerPickingBlock()._cubePos +
                g_event->m_world->getPlayerInfos()->getPlayerPickingBlock()._normale, 0));
    }
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    g_event->m_lastMouseX = xpos;
    g_event->m_lastMouseY = ypos;
    if (g_event->_guiState)
        g_event->m_win->getNanoGUIScreen()->mouseButtonCallbackEvent(button, action, mods);
}

void Event::cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {
    g_event->cx = xpos;
    g_event->cy = ypos;
    g_event->m_win->getNanoGUIScreen()->cursorPosCallbackEvent(xpos, ypos);
}

void Event::keybordEvents(double deltaTime) {
    if (keybordButtons[GLFW_KEY_W]) {
        glm::dvec3 direction = m_win->getCamera()->getVectorDir();

        if (!m_world->getEntity(0)->isMoving()) {
            m_world->getEntity(0)->resetVelocity();
            m_world->getEntity(0)->setVelocity(direction);
        }
    }
    if (keybordButtons[GLFW_KEY_S]) {
        /*double speed = _movementSpeedCam * deltaTime;
        glm::dvec3 direction = m_win->getCamera()->getVectorDir();
        glm::dvec3 pos = m_world->getEntity(0)->getEntityPosition();
        if (m_world->checkCollisionAABB(pos, glm::dvec3(-speed * direction.x, 0.0, 0.0)))
            direction.x = 0;
        if (m_world->checkCollisionAABB(pos, glm::dvec3(0.0, -speed * direction.y, 0.0)))
            direction.y = 0;
        if (m_world->checkCollisionAABB(pos, glm::dvec3(0.0, 0.0, -speed * direction.z)))
            direction.z = 0;
        m_world->getPlayerInfos()->updateInfos(m_world->getEntity(0)->movePlayerPos(-speed, direction),
            floor(m_win->getCamera()->getVectorDir() * 2.0) / 2.0);
        glm::dvec3 newPos = m_world->getEntity(0)->getEntityPosition();
        if (m_world->checkCollision(newPos))
        {
            m_world->getEntity(0)->movePlayerPos(speed, direction);
        }*/
    }
    if (keybordButtons[GLFW_KEY_UP]) {
        glm::dvec4 tmpLight = m_world->getLightPos();
        m_world->setLightPos(glm::dvec3(tmpLight.x, tmpLight.y, tmpLight.z + 0.000005));
    }
    if (keybordButtons[GLFW_KEY_DOWN]) {
        glm::dvec4 tmpLight = m_world->getLightPos();
        m_world->setLightPos(glm::dvec3(tmpLight.x, tmpLight.y, tmpLight.z - 0.000005));
    }
    if (keybordButtons[GLFW_KEY_LEFT]) {
        glm::dvec4 tmpLight = m_world->getLightPos();
        m_world->setLightPos(glm::dvec3(tmpLight.x + 0.000005, tmpLight.y, tmpLight.z));
    }
    if (keybordButtons[GLFW_KEY_RIGHT]) {
        glm::dvec4 tmpLight = m_world->getLightPos();
        m_world->setLightPos(glm::dvec3(tmpLight.x - 0.000005, tmpLight.y, tmpLight.z));
    }
    if (keybordButtons[GLFW_KEY_DELETE]) {
        exit(EXIT_SUCCESS);
    }
    if (keybordButtons[GLFW_KEY_SPACE]) {
        m_world->getEntity(0)->setVelocity(glm::dvec3(0.0, 4.0, 0.0));
    }
#ifdef _WIN32
    Sleep(1);
#endif
#ifdef __linux__
    usleep(1);
#endif
    //if (m_world->getQueueEvent()->size() == 0)
    m_world->updateEntities(deltaTime);
}

void Event::mouseDragging(double width, double height) {
    double deltaX = (cx - m_lastMouseX) / (g_event->m_win->getWidth() / 200.0);
    double deltaY = (cy - m_lastMouseY) / (g_event->m_win->getHeight() / 200.0);

    if ((deltaX != 0 || deltaY != 0) && !_guiState) {
        m_win->getCamera()->rotateCamera(-deltaX, -deltaY, glm::dvec3(0.0, -1.0, 0.0));
        m_win->pickingBlock();
    }

    m_lastMouseX = cx;
    m_lastMouseY = cy;
} 