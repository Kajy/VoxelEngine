#include <boost/lexical_cast.hpp>
#include "Window.h"

Ucraft::Window::Window(Ucraft::Options *options) :
        _camera(glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0)),
        _keepAlive(-1),
        _world(NULL),
        _options(options) {
    setup();
}

int Ucraft::Window::setup() {
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    } 

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(*(_options->getWidth()), *(_options->getHeight()), "OpenGL FrameWork", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    /* Make the window's context current */

    //glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        // Problem: glewInit failed, something is seriously wrong.
        std::cout << "glewInit failed, aborting." << std::endl;
        return -1;
    }

    printf("OpenGL %s, GLSL %s, Renderer %s\n", glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION), glGetString(GL_RENDERER));

    glfwSwapInterval(0);  //enable vsync

    bool show_test_window = true;
    bool show_another_window = false;

    glfwSetWindowTitle(window, "uCraft");
    glfwGetWindowSize(window, _options->getWidth(), _options->getHeight());
    glEnable(GL_MULTISAMPLE);
    return 0;
}

void Ucraft::Window::setWorld(World *world, char const *path) {
    _world = world;
    _uScreen = new uScreen(_world, &m_model, &_camera, _options->getWidth(), _options->getHeight());
    
    _uScreen->initialize(window, true);
    _gui = new GUI(_uScreen, _options, path);
	_world->getEntity(0)->attachCameraToEntity(&_camera);
}

void Ucraft::Window::updateInfo(Ucraft::ObjectType *obj) {
    std::string str;
    if (strncmp(obj->getName().c_str(), "Targeted block", 14) == 0) {
        str = std::string("Targeted block : " +
                          boost::lexical_cast<std::string>(glm::round(_uScreen->getCamera()->getPosLookAt().x)) +
                          " : " +
                          boost::lexical_cast<std::string>(glm::round(_uScreen->getCamera()->getPosLookAt().y)) +
                          " : " +
                          boost::lexical_cast<std::string>(glm::round(_uScreen->getCamera()->getPosLookAt().z)));
    } else if (strncmp(obj->getName().c_str(), "Player position", 15) == 0) {
        str = std::string("Player position : " +
                          boost::lexical_cast<std::string>(glm::round(_uScreen->getCamera()->getPosCamera().x)) +
                          " : " +
                          boost::lexical_cast<std::string>(glm::round(_uScreen->getCamera()->getPosCamera().y)) +
                          " : " +
                          boost::lexical_cast<std::string>(glm::round(_uScreen->getCamera()->getPosCamera().z)));
    } else if (strncmp(obj->getName().c_str(), "Player section", 14) == 0) {
        str = std::string("Player section : " + boost::lexical_cast<std::string>(
                glm::round(_uScreen->getWorld()->getPlayerInfos()->getPlayerPosInSection().x)) + " : " +
                          boost::lexical_cast<std::string>(
                                  glm::round(_uScreen->getWorld()->getPlayerInfos()->getPlayerPosInSection().y)) +
                          " : " +
                          boost::lexical_cast<std::string>(
                                  glm::round(_uScreen->getWorld()->getPlayerInfos()->getPlayerPosInSection().z)));

    } else {
        return;
    }
    obj->setName(str);
}

void Ucraft::Window::printAll() {
    int i = 0;
    if (_options->getResized() && _options->isFromMenu()) {
        glfwSetWindowSize(window, *(_options->getWidth()), *(_options->getHeight()));
        _options->setFromMenu(false);
    }
    if (_options->getResized() || _gui->hasChanged()) {
        for (std::vector<Ucraft::ObjectType *>::iterator it = _gui->getComponents()->begin();
             i < _gui->getComponents()->size(); it++, i += 1) {
            updateInfo((*it));
            if (_options->getResized()) {
                (*it)->getWidget()->setPosition(Eigen::Vector2i(
                        (*(_options->getWidth()) / 100) * (*it)->getPosX(),
                        (*(_options->getHeight()) / 100) * (*it)->getPosY()
                ));
                (*it)->getWidget()->setSize(Eigen::Vector2i(
                        (*(_options->getWidth()) / 100) * (*it)->getSizeX(),
                        (*(_options->getHeight()) / 100) * (*it)->getSizeY()
                ));
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                _gui->setGuiActivated(false);
            }
            GuiFuncMap::iterator func = _gui->getFuncMap()->find((*it)->getType());
            if (func != _gui->getFuncMap()->end()) {
                (_gui->*(func->second))(_gui->getComponents()->at(i), _gui);
            }
            if (_gui->_isTitle) {
                _gui->reduceAlpha();
            }
        }
        _gui->setChanged(false);
        _options->setResized(false);
    }
	_uScreen->performLayout();
    _uScreen->drawAll();
}

float Ucraft::Window::getAspect() const { return (*(_options->getWidth()) / (float) *(_options->getHeight())); }

GLFWwindow *Ucraft::Window::getGLWwindow() const { return (window); }

void Ucraft::Window::pickingBlock() {
    std::vector<UViewer::Intersection> intersections = _camera.getIntersections();
    for (auto const &it : intersections) {
        if (_world->checkCollision(it._cubePos + _world->getPlayerInfos()->getPlayerSection())) {
            UViewer::Intersection goodInter;

            goodInter._cubePos = it._cubePos + _world->getPlayerInfos()->getPlayerSection();
            goodInter._normale = it._normale;
            _world->getPlayerInfos()->setPlayerPickingBlock(goodInter);
            break;
        }
    }
}