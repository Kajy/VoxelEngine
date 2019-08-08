#pragma once

#include <sstream>
#include "protocol.h"
#include "Network.h"

class PkgString
{
public:
	PkgString(Network *client);
	~PkgString();

	void	ReadString();
	void	ReadTinyString();
	void	WriteString(std::string const &);

	char	*getData() const { return _str->data; }

private:
	Network		*_client;
	CMDString	*_size;
	CMDString	*_str;

	CMDTinyString	*_sizeTiny;
	CMDTinyString	*_strTiny;
};