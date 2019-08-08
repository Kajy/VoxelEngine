#pragma once
#include <iostream>
#include <thread>

#include "boost/asio/ip/tcp.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/array.hpp"

#include "World.h"
#include "Window.h"
#include "CMDHandlerIn.h"
#include "protocol.h"

using boost::asio::ip::tcp; 

class Network
{
public:
	Network(char const *adress, char const *port, World *world, Ucraft::Window *win);
	~Network();

	template<typename T>
	void write(T data) {
		_sock.write_some(boost::asio::buffer((char*)&data, sizeof(T)));
	}

	template<typename T>
	T *read() {

		boost::array<T, sizeof(T)> buf;
		_sock.read_some(boost::asio::buffer(buf, sizeof(T)));

		return buf.data();
	}

	void	read(char *data, size_t offset, size_t size) {
		size_t	new_off = offset;
		int		finalStep = size;
		boost::asio::mutable_buffers_1 mbuf = boost::asio::mutable_buffers_1(data + offset, size);
		while (finalStep > 0) {
			boost::asio::mutable_buffers_1 mbuf = boost::asio::mutable_buffers_1(data + new_off, finalStep);
			new_off += _sock.read_some(mbuf);
			finalStep = size - new_off;
		}
	}

	void write(char *data, size_t size) {
		_sock.write_some(boost::asio::buffer(data, size));
	}

public:

	bool	isConnected() { return _connected; }

	void	connect();
	void	run();
	void	disconnect();
	void	runThread();

	void	async_read();

	void	do_connect(boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator);
	void	do_read(const boost::system::error_code &error, std::size_t bytes_transferred);

	bool	isLogged() { return  _logged; }
	void	setLogged() { _logged = true; }

private:
	std::string				_adress;
	std::string				_port;
	bool					_connected;
	unsigned int			_sizeBuff;

	std::thread				_runThread;

	boost::asio::io_service	_io_service;
	tcp::resolver			_resolver;
	tcp::socket				_sock;

	boost::asio::streambuf	_read;

	World					*_world;
	Ucraft::Window			*_win;

	bool					_logged;

};