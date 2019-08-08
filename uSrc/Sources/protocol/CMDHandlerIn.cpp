#include "CMDHandlerIn.h"

CMDHandlerIn::CMDHandlerIn() {
}

CMDHandlerIn::~CMDHandlerIn() {
}

unsigned int
CMDHandlerIn::handleCMDRead(boost::asio::streambuf *read, unsigned int sizeBuff, World *world, Ucraft::Window *win) {
    char const *packet = boost::asio::buffer_cast<char const *>(read->data());
    CommandType type = (*(CommandType *) packet);

    if (type == CommandType::receiveSection) {
        //std::cout << "Receive Section" << std::endl;
        if (sizeBuff > 14) {
            int x, y, z;
            x = (*(int *) (packet + 2));
            y = (*(int *) (packet + 6));
            z = (*(int *) (packet + 10));
            if (sizeBuff < (14 + (4096 * sizeof(short)) + (4096 * sizeof(char))))
                return (sizeBuff);
            else {
                short *ids = new short[4096];
                char *values = new char[4096];

                memcpy(ids, (short *) (packet + 14), sizeof(short) * 4096);
                PkgSection newSection(x << 4, y << 4, z << 4);
                newSection.setIds(ids);
                world->addEvent(newSection);
                //std::cout << "Receive chunk [" << x << "," << y << "," << z << "]" << std::endl;
                read->consume(14 + (4096 * sizeof(short)) + (4096 * sizeof(char)));
                sizeBuff -= (14 + (4096 * sizeof(short)) + (4096 * sizeof(char)));
                return (sizeBuff);
            }
        } else
            return (sizeBuff);
    } else if (type == CommandType::chunkUnload) {
        if (sizeBuff > 10) {

            int x, y, z;
            x = (*(int *) (packet + 2));
            y = (*(int *) (packet + 6));
            z = (*(int *) (packet + 10));

            world->unloadChunk(glm::ivec3(x * 16, y * 16, z * 16));
            //std::cout << "Receive chunk unload [" << x << "," << y << "," << z << "]" << std::endl;
            read->consume(14);
            sizeBuff -= 14;
            return (sizeBuff);
        }
    } else if (type == CommandType::SpawnPointIn) {
        double spawn_x, spawn_y, spawn_z;
        spawn_x = (*(double *) (packet + 2));
        spawn_y = (*(double *) (packet + 10));
        spawn_z = (*(double *) (packet + 18));
        read->consume(26);
        sizeBuff -= 26;
        return (sizeBuff);
    } else if (type == CommandType::EntitySpawn) {
        int entity_id;
        long long mostBits, leastBits;
        boost::uuids::uuid test;

        double entity_x, entity_y, entity_z;
        entity_id = (*(int *) (packet + 2));
        mostBits = (*(long long *) (packet + 6));
        mostBits = (*(long long *) (packet + 14));
        entity_x = (*(double *) (packet + 22));
        entity_y = (*(double *) (packet + 30));
        entity_z = (*(double *) (packet + 38));
        read->consume(46);
        sizeBuff -= 46;
        return (sizeBuff);
    } else if (type == CommandType::EntityUpdate) {
        int entity_id;

        double entity_x, entity_y, entity_z;
        entity_id = (*(int *) (packet + 2));
        entity_x = (*(double *) (packet + 6));
        entity_y = (*(double *) (packet + 14));
        entity_z = (*(double *) (packet + 22));
        read->consume(30);
        sizeBuff -= 30;
        return (sizeBuff);
    } else if (type == CommandType::KeepAliveIn) {
        sizeBuff -= 6;
        int int_test = (*(int *) (packet + 2));
        win->setKeepAlive(int_test);
        read->consume(6);
        std::cout << "Receive Keep Alive ! [" << int_test << "]" << std::endl;
        return (sizeBuff);
    } else if (type == CommandType::StatusOutPong) {
        long long pong;

        pong = (*(long long *) (packet + 2));
        read->consume(10);
        sizeBuff -= 10;
        return (sizeBuff);
    } else if (type == CommandType::PlayOutTeleport) {
        double tp_x, tp_y, tp_z;

        tp_x = (*(double *) (packet + 2));
        tp_y = (*(double *) (packet + 10));
        tp_z = (*(double *) (packet + 18));
        read->consume(26);
        sizeBuff -= 26;
        return (sizeBuff);
    } else if (type == CommandType::PlayInChat) {
        short size = (*(short *) (packet + 2));
        char *tmp = strdup((char *) (packet + 4));
        tmp[size] = '\0';
        std::string message(tmp);
        win->getGui()->getQueueMessageIn()->push_back(message);
        read->consume(size + 4);
        sizeBuff -= size + 4;
        free(tmp);
        return (sizeBuff);
    } else if (type == CommandType::Kick) {
        short size;

        size = (*(short *) (packet + 2));
        char *reason = new char[size];

        memcpy(reason, (char *) (packet + 4), size);
        read->consume(4 + size);
        sizeBuff -= size + 4;
        return (sizeBuff);
    } else if (type == CommandType::BlockUpdate) {
        if (sizeBuff > 16) {
            CubeUpdatePacket update;

            update.pos.x = (*(int *) (packet + 2));
            update.pos.y = (*(int *) (packet + 6));
            update.pos.z = (*(int *) (packet + 10));

            update.id = (*(short *) (packet + 14));
            update.data = (*(char *) (packet + 15));
            world->getQueueUpdate()->push(update);
            read->consume(17);
            sizeBuff -= 17;
            return (sizeBuff);
        }
    } else if (type == CommandType::Ressource) {
        short size;

        size = (*(short *) (packet + 2));
        char *ressource = new char[size];

        memcpy(ressource, (char *) (packet + 4), size);
        read->consume(4 + size);
        sizeBuff -= size + 4;
        return (sizeBuff);
    } else if (type == CommandType::PacketPlayInTitleMessage) {
        short size;

        size = (*(short *) (packet + 2));
        char *tmp = strdup((char *) (packet + 4));
        tmp[size] = '\0';

        long duration;

        duration = (*(long *) (packet + size + 4));
        win->getGui()->PrintTitle(std::string(tmp), duration / 1000);
        win->getGui()->_isTitle = true;

        //std::cout << "Duration : " << duration << std::endl;
        //std::cout << "Message : " << tmp << std::endl;
        sizeBuff -= 2 + size + sizeof(long) + sizeof(short);
        read->consume(2 + size + sizeof(long) + sizeof(short));
        return (sizeBuff);

    } else {
        std::cout << "Unknown Package :" << (short) type << std::endl;
        return (sizeBuff);
    }
    return (sizeBuff);
}

