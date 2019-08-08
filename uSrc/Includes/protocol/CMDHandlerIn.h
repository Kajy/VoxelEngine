#pragma once

#include <sstream>
#include "boost/asio.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/bind.hpp"
#include "boost/array.hpp"
#include "protocol.h"
#include "World.h"
#include "Window.h"

class CMDHandlerIn
{
public:
	CMDHandlerIn();
	~CMDHandlerIn();

	static unsigned int		handleCMDRead(boost::asio::streambuf *read, unsigned int sizeBuff, World *world, Ucraft::Window *win);
private:

};