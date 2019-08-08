#pragma once

#include "PluginSocket.h"
#include "Network.h"
#include "Window.h"
#include "protocol.h"
#include "protocol/PkgString.h"
#include "protocol/PkgHandShakeIn.h"
#include "varInt.h"


class CMDHandlerOut {
public:
	CMDHandlerOut();

	static void handleCMDWrite(Network *client, CommandType, Ucraft::Window *, PluginSocket *pluginEditorSocket, World *world);

private:
	static void	writeCMD(Network *client, std::stringbuf &out);

};