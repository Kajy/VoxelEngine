#include "protocol/CMDHandlerOut.h"

CMDHandlerOut::CMDHandlerOut() {}

void	CMDHandlerOut::handleCMDWrite(Network *client, CommandType command, Ucraft::Window *win, PluginSocket *pluginEditorSocket,World *world) {
    if (command == CommandType::handShakeIn) {
        PkgHandShakeIn::sendHandShakeIn(client, 1, "127.0.0.1", 2);
    } else if (command == CommandType::PlayOutPosition) {
        try {
			std::stringbuf out;
            glm::dvec3 pos = win->getCamera()->getPosCamera();

            putStringBuf<short>(out, command);
            putStringBuf<glm::dvec3>(out, pos);

            writeCMD(client, out);
        }
        catch (const boost::system::system_error &ex) {
            //std::cout << "Error PlayOutPosition : " << ex.what() << std::endl;
        }
    } else if (command == CommandType::KeepAliveOut) {
        try {
			std::stringbuf out;

            int keepAlive = win->getKeepAlive();
            std::cout << "Send KeepAlive : " << keepAlive << std::endl;
            putStringBuf<short>(out, command);
            putStringBuf<int>(out, keepAlive);
            writeCMD(client, out);
            win->setKeepAlive(-1);
        }
        catch (const boost::system::system_error &ex) {
            std::cout << "Error KeepAliveOut : " << ex.what() << std::endl;
        }
	}
	else if (command == CommandType::StatusInPing) {
		try {
			std::stringbuf out;

			long time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			putStringBuf<short>(out, command);
			putStringBuf<long>(out, time);
			writeCMD(client, out);
		}
		catch (const boost::system::system_error &ex) {
			std::cout << "Error StatusInPing : " << ex.what() << std::endl;
		}
	}
	else if (command == CommandType::BreakBlock) {
        try {
            std::queue<glm::ivec4> *queue = world->getQueueBreak();
                std::stringbuf out;

                glm::ivec3 pos = queue->front();
                std::cout << "Send BreakBlock : " << pos.x << " " << pos.y << " " << pos.z << " | Queue size : " << queue->size() << std::endl;
                putStringBuf<short>(out, command);
                putStringBuf<int>(out, pos.x);
                putStringBuf<int>(out, pos.y);
                putStringBuf<int>(out, pos.z);
                writeCMD(client, out);
                queue->pop();
        }
        catch (const boost::system::system_error &ex) {
            std::cout << "Error BreakBlock : " << ex.what() << std::endl;
        }
    } else if (command == CommandType::PlayOutChat) {
        try {
            std::stringbuf out;

            putStringBuf<short>(out, command);

            short sizeString = win->getGui()->getQueueMessageOut()->back().size();
            putStringBuf<short>(out, sizeString);

            putStringBufVar<const char *>(out, win->getGui()->getQueueMessageOut()->back().c_str(),
                                          win->getGui()->getQueueMessageOut()->back().size());
            writeCMD(client, out);
            win->getGui()->getQueueMessageOut()->pop_back();
        }
        catch (const boost::system::system_error &ex) {
            std::cout << "Error Chat : " << ex.what() << std::endl;
        }
    } else if (command == CommandType::PlayOutCommand) {
        try {
            std::stringbuf out;

            putStringBuf<short>(out, command);

            short sizeString = win->getGui()->getQueueCommandOut()->back().size();
            putStringBuf<short>(out, sizeString);

            putStringBufVar<const char *>(out, win->getGui()->getQueueCommandOut()->back().c_str(),
                                          win->getGui()->getQueueCommandOut()->back().size());
            writeCMD(client, out);
            win->getGui()->getQueueCommandOut()->pop_back();
        }
        catch (const boost::system::system_error &ex) {
            // std::cout << "Error Chat : " << ex.what() << std::endl;
        }
    } else if (command == CommandType::AddBlock) {
        try {
            std::queue<glm::ivec4> *queue = world->getQueueAdd();
            for (int i = 0; i < queue->size(); ++i) {
                std::stringbuf out;

                glm::ivec4 pos = queue->front();
                std::cout << "Send AddBlock : " << pos.x << " " << pos.y << " " << pos.z << " ID [" << pos.w << "]" << std::endl;
                putStringBuf<short>(out, command);
                putStringBuf<int>(out, pos.x);
                putStringBuf<int>(out, pos.y);
                putStringBuf<int>(out, pos.z);
                putStringBuf<short>(out, (short)pos.w);
                putStringBuf<char>(out, (char) 0);
                writeCMD(client, out);
                queue->pop();
            }
        }
        catch (const boost::system::system_error &ex) {
            std::cout << "Error AddBlock : " << ex.what() << std::endl;
        }
	}
	else if (command == CommandType::PxtReset) {
		std::stringbuf out;
		putStringBuf<short>(out, command);
		writeCMD(client, out);
	}
	else if (command == CommandType::PxtUpdate) {
        std::queue<std::string> *queue = pluginEditorSocket->getQueue();
        for (int i = 0; i < queue->size(); ++i) {
            std::stringbuf out;
            std::string msg = queue->front();
            putStringBuf<short>(out, command);
            putStringBuf<short>(out, msg.size());
            putStringBufVar<const char *>(out, msg.c_str(), msg.size());
		    writeCMD(client, out);
            queue->pop();
            std::cout << "Sending Msg Makecode :" << msg << std::endl;
        }
	}
}


void CMDHandlerOut::writeCMD(Network *client, std::stringbuf &out) {
    uint8_t *packetSizeVarInt = new uint8_t;
    out.pubseekpos(0);
    std::streamsize packetSize = out.in_avail();
    size_t VarIntSize = encodeVarint<int>(packetSize, packetSizeVarInt);

    char *toSend = new char[packetSize];
    out.sgetn(toSend, packetSize);

    client->write((char *) packetSizeVarInt, VarIntSize);
    client->write(toSend, packetSize);
}


