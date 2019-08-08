#ifndef _PLUGINSOCKET_H
#define _PLUGINSOCKET_H 1

#include "WebSocketServer.h"
#include <queue>

class PluginSocket : public WebSocketServer {
public:
    PluginSocket(int port);

    ~PluginSocket();

    void sendMessage(int socketID, const string &data);

    virtual void onConnect(int socketID);

    virtual void onMessage(int socketID, const string &data);

    virtual void onDisconnect(int socketID);

    virtual void onError(int socketID, const string &message);

    std::queue<std::string> *getQueue() { return &_messageQueue; }
private:
    std::queue<std::string> _messageQueue;
};

#endif