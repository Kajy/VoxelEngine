#include "PkgHandShakeIn.h"

void PkgHandShakeIn::sendHandShakeIn(Network *_client, int protocolVersion, std::string const &adress, int purpose)
{
	try {
		std::stringbuf out;

		putStringBuf<short>(out, CommandType::handShakeIn);
		putStringBuf<int>(out, protocolVersion);
		char sizeString = adress.size();
		putStringBuf<char>(out, sizeString);
		putStringBufVar<const char *>(out, adress.c_str(), adress.size());
		putStringBuf<int>(out, purpose);

		writeCMD(_client, out);
	}
	catch (const boost::system::system_error& ex)
	{
		std::cout << "Error ShakeIn : " << ex.what() << std::endl;
	}
} 

void		PkgHandShakeIn::writeCMD(Network *client, std::stringbuf &out)
{
	uint8_t	*packetSizeVarInt = new uint8_t;
	out.pubseekpos(0);
	std::streamsize packetSize = out.in_avail();
	size_t VarIntSize = encodeVarint<int>(packetSize, packetSizeVarInt);

	char *toSend = new char[packetSize];
	out.sgetn(toSend, packetSize);

	client->write((char *)packetSizeVarInt, VarIntSize);
	client->write(toSend, packetSize);
}