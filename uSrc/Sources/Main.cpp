#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <iomanip>

#ifdef __linux__
#include <pthread.h>
#endif
#ifdef __WIN32
#include <thread>
#endif

#include <chrono>
#include <ctime>
#include <ratio>

#include "PluginSocket.h"
#include "Event.h"
#include "Network.h"
#include "protocol/CMDHandlerOut.h"
#include "UZipPack.h"


void StartPluginSocket(PluginSocket *pluginEditorSocket) {
    pluginEditorSocket->run();
}

void
HandlePackage(World *world, Ucraft::Window *win, Network *net, PluginSocket *pluginEditorSocket, const char *path) {
    GLFWwindow *window = win->getGLWwindow();

    net->run();

    while (!(net->isLogged())) {
        UZipPack::setTexturePack("/Ressources/TexturePackTest.zip", world, win->getGui(), path);

        CMDHandlerOut::handleCMDWrite(net, CommandType::handShakeIn, win, pluginEditorSocket, world);
        net->setLogged();
    }

    double maxWorkingTimePerFrame = 1000 / 10;

    std::chrono::high_resolution_clock::time_point lastStartTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {

        std::chrono::duration<double> elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(
                std::chrono::high_resolution_clock::now() - lastStartTime);
        lastStartTime = std::chrono::high_resolution_clock::now();

        if (win->getKeepAlive() != -1)
            CMDHandlerOut::handleCMDWrite(net, CommandType::KeepAliveOut, win, pluginEditorSocket, world);
        if (world->getQueueBreak()->size() > 0)
            CMDHandlerOut::handleCMDWrite(net, CommandType::BreakBlock, win, pluginEditorSocket, world);
        if (world->getQueueAdd()->size() > 0)
            CMDHandlerOut::handleCMDWrite(net, CommandType::AddBlock, win, pluginEditorSocket, world);
        if (win->getGui()->getQueueMessageOut()->size() > 0)
            CMDHandlerOut::handleCMDWrite(net, CommandType::PlayOutChat, win, pluginEditorSocket, world);
        if (win->getGui()->getQueueCommandOut()->size() > 0)
            CMDHandlerOut::handleCMDWrite(net, CommandType::PlayOutCommand, win, pluginEditorSocket, world);
        if (pluginEditorSocket->getQueue()->size() > 0)
            CMDHandlerOut::handleCMDWrite(net, CommandType::PxtUpdate, win, pluginEditorSocket, world);
        CMDHandlerOut::handleCMDWrite(net, CommandType::PlayOutPosition, win, pluginEditorSocket, world);

        std::chrono::duration<double> processingTimeForCurrentFrame = std::chrono::duration_cast<std::chrono::duration<double>>(
                std::chrono::high_resolution_clock::now() - lastStartTime);
        if (processingTimeForCurrentFrame.count() < maxWorkingTimePerFrame) {
#ifdef _WIN32
            Sleep(maxWorkingTimePerFrame - processingTimeForCurrentFrame.count());
#endif
#ifdef __linux__
            int time = maxWorkingTimePerFrame - processingTimeForCurrentFrame.count() * 1000;
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
                //usleep(maxWorkingTimePerFrame - processingTimeForCurrentFrame.count());
#endif
#ifdef __APPLE__
            sleep((maxWorkingTimePerFrame - processingTimeForCurrentFrame.count()) / 1000);
#endif
        }
    }

    net->disconnect();
}

void CatchEvents(Event &catchEvents, Ucraft::Window *win, Network *net) {
    while (!(net->isLogged())) {
#ifdef _WIN32
        Sleep(2);
#endif
#ifdef __linux__
        sleep(2);
#endif
#ifdef __APPLE__
        sleep(2);
#endif
    }

    GLFWwindow *window = win->getGLWwindow();

    double oldTime = glfwGetTime();
    double currentTime;
    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        catchEvents.keybordEvents(currentTime - oldTime);
        catchEvents.mouseDragging(*(win->getWindowW()), *(win->getWindowH()));
        oldTime = currentTime;
    }
}


int main(int ac, char **av) {


    std::string path;
    int sizeX = 1366;
    int sizeY = 780;

    if (ac < 2) {
        path = "..";
    } else if (ac == 4) {
        path = av[1];
        sizeX = std::stoi(av[2]);
        sizeY = std::stoi(av[3]);
    } else
        path = av[1];

    Ucraft::Options *options = new Ucraft::Options(sizeX, sizeY);
    Ucraft::Window *win = new Ucraft::Window(options);
    World *world = new World(path.c_str(), win->getCamera());
    win->setWorld(world, path.c_str());

    PluginSocket pluginEditorSocket = PluginSocket(9999);
    Network net("127.0.0.1", "26656", world, win);

    Event catchEvents(win, world);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glfwSetInputMode(win->getGLWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    catchEvents.AllCallback();

    GLFWwindow *window = win->getGLWwindow();

    std::thread thEvent(CatchEvents, std::ref(catchEvents), win, &net);
    std::thread th(HandlePackage, world, win, &net, &pluginEditorSocket, path.c_str());
    std::thread thPlugin(StartPluginSocket, &pluginEditorSocket);

    GLenum err;
    while (!(net.isLogged())) {
#ifdef _WIN32
        Sleep(2);
#endif
#ifdef __linux__
        sleep(2);
#endif
#ifdef __APPLE__
        sleep(2);
#endif
    }
    world->setWorldInfos();
    win->getGui()->load();
    while (!glfwWindowShouldClose(window)) {
        win->printAll();

        glfwPollEvents();

        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec
            // ago printf and reset timer
            std::stringstream ss;
            ss << "FPS: " << nbFrames;// << " ---- ";

            glfwSetWindowTitle(window, ss.str().c_str());
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
    exit(EXIT_SUCCESS);
    thPlugin.join();
    thEvent.join();
    th.join();
    glfwDestroyWindow(win->getGLWwindow());

    glfwTerminate();
    return 0;
}
