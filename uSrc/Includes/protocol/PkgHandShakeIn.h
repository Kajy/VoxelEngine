#pragma once

#include "protocol.h"
#include "PkgString.h"
#include "Network.h"
#include "varInt.h"

class PkgHandShakeIn
{
public:
	PkgHandShakeIn();
	~PkgHandShakeIn();

	static void sendHandShakeIn(Network *_client, int protocolVersion, std::string const &adress, int purpose);

	static void	writeCMD(Network *client, std::stringbuf &out);
private:

};