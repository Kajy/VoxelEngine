#pragma once

#include <iostream>
#include "curl/curl.h"

class UCurl
{
public:
	UCurl();
	~UCurl();

	static void	curlFile(const char *url, const char* outfile);
private:

};