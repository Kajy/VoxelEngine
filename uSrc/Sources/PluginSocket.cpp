#include "PluginSocket.h"

PluginSocket::PluginSocket( int port ) : WebSocketServer( port )
{
}

PluginSocket::~PluginSocket( )
{
}

void PluginSocket::onConnect( int socketID )
{
    std::cout << "New connection" << std::endl;
}

void PluginSocket::onMessage( int socketID, const string& data )
{
    _messageQueue.push(data);
}

void PluginSocket::sendMessage( int socketID, const string& data )
{
    this->send( socketID, data );
}

void PluginSocket::onDisconnect( int socketID )
{
    std::cout << "Disconnect" << std::endl;
}

void PluginSocket::onError( int socketID, const string& message )
{
    std::cout << "Error" << std::endl;
}

