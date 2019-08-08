#include "PkgString.h"

PkgString::PkgString(Network *client) :
	_client(client)
{
}

void		PkgString::ReadString() {
	_size = (CMDString *)malloc(sizeof(CMDString));
	_client->read((char *)_size, 0, sizeof(CMDString));
	_str = (CMDString *)malloc(sizeof(CMDString) + _size->size);
	memcpy(_str, _size, sizeof(CMDString));
	_client->read((char *)_str, sizeof(CMDString), _size->size);
}

void		PkgString::ReadTinyString() {
	_sizeTiny = (CMDTinyString *)malloc(sizeof(CMDTinyString));
	_client->read((char *)_sizeTiny, 0, sizeof(CMDTinyString));
	_strTiny = (CMDTinyString *)malloc(sizeof(CMDTinyString) + _sizeTiny->size);
	memcpy(_strTiny, _sizeTiny, sizeof(CMDTinyString));
	_client->read((char *)_strTiny, sizeof(CMDTinyString), _sizeTiny->size);
} 

void		PkgString::WriteString(std::string const &str)
{
	CMDTinyString *newTiny = (CMDTinyString *)malloc(sizeof(CMDTinyString) + str.size());
	newTiny->size = (char)(str.size());
	memcpy(newTiny->data, str.data(), str.size());
	_client->write((char *)newTiny, sizeof(CMDTinyString) + str.size());
}


PkgString::~PkgString()
{
}