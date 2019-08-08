#pragma once

#include "Network.h"
#include "World.h"
#include "protocol.h"
#include "protocol/PkgString.h"
#include "protocol/PkgHandShakeIn.h"
#include "protocol/PkgChunk.h"

class CMDHandler {
public:
	CMDHandler(Network *);

	void handleCMDRead(World *, Ucraft::Window *);
	void handleCMDWrite(CommandType, Ucraft::Window *);

private:
	Network *_client;
};