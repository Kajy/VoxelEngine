#include "Network.h"
#include <bitset>

Network::Network(char const *adress, char const *port, World *world, Ucraft::Window *win) :
	_resolver(_io_service),
	_sock(_io_service),
	_world(world),
	_connected(false),
	_logged(false),
	_sizeBuff(0),
    _adress(adress),
    _port(port),
    _win(win)
{
    connect();
}

Network::~Network() {
    std::cout << "Disconnected ?!" << std::endl;
}

void Network::connect() {
    tcp::resolver::query query(_adress, _port);
    tcp::resolver::iterator endpoint_iterator = _resolver.resolve(query);

    boost::asio::async_connect(_sock, endpoint_iterator,
                               boost::bind(&Network::do_connect, this, boost::asio::placeholders::error,
                                           boost::asio::placeholders::iterator));
}

void Network::async_read() {

    boost::asio::async_read(_sock, _read, boost::asio::transfer_at_least(3),
                            boost::bind(&Network::do_read, this, boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
} 

void Network::do_connect(boost::system::error_code const &ec, boost::asio::ip::tcp::resolver::iterator) {
    if (!ec) {
        //	std::cout << "Connected in TCP mod" << std::endl;
        _connected = true;
        async_read();
    } else {
        //std::cout << "Waiting to connect ..." << std::endl;
        connect();
    }
}

void Network::do_read(const boost::system::error_code &error, size_t bytes_transferred) {
    if (!error) {
        _sizeBuff += bytes_transferred;
		//std::cout << "SizeBuff in DoRead :" << _sizeBuff << std::endl;
        _sizeBuff = CMDHandlerIn::handleCMDRead(&_read, _sizeBuff, _world, _win);
        async_read();
    }
};

void Network::runThread(void) {
    try {
        _io_service.run();
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Network::run() {
    _runThread = std::thread(&Network::runThread, this);
}

void Network::disconnect() {
    _runThread.join();
}