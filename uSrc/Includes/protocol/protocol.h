#pragma once

#ifndef _PROTOCOL_H_

#define _PROTOCOL_H_
#define _WIN32_WINNT 0x0501

#include <sstream>
#include <glm/vec3.hpp>

enum CommandType : short {
	handShakeIn = 0,
	receiveSection = 1,
	chunkUnload = 2,
	SpawnPointIn = 3,
	PlayOutPosition = 4,
	PlayOutChat = 5,
	KeepAliveOut = 6,
	StatusInPing = 7,
	EntitySpawn = 8,
	EntityUpdate = 9,
	KeepAliveIn = 10,
	StatusOutPong = 11,
	PlayOutTeleport = 12,
	PlayInChat = 13,
	PlayOutCommand = 14,
	AddBlock = 15,
	BreakBlock = 16,
	Kick = 17,
	PxtReset = 18,
	PxtUpdate = 19,
	Ressource = 20,
	BlockUpdate = 21,
	PacketPlayInTitleMessage = 22
};

struct CMDString {
	//CommandType		commandType;
	short	size;
	char	data[0];
};

struct CMDTinyString {
	//CommandType		commandType;
	char	size;
	char	data[0];
};

struct CubeUpdatePacket {
	glm::ivec3	pos;
	int			id;
	char		data;
};

template <class Type>
std::stringbuf& putStringBuf(std::stringbuf& buf, const Type& var)
{
	buf.sputn(reinterpret_cast<const char*>(&var), sizeof var);

	return buf;
}

template <class Type>
std::stringbuf& putStringBufVar(std::stringbuf& buf, const Type var, size_t size)
{
	buf.sputn(reinterpret_cast<const char*>(var), size);

	return buf;
}

template <class Type>
std::stringbuf& getStringBuf(std::stringbuf& buf, Type& var, size_t size)
{
	buf.sgetn(reinterpret_cast<char*>(&var), size);

	return buf;
}

#endif // !_PROTOCOL_H_