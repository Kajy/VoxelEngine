#include "UCurl.h"


UCurl::UCurl()
{
}

UCurl::~UCurl()
{
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

void		UCurl::curlFile(const char *url, const char *outfilename) {
	CURL *curl;
	FILE *fp;
	CURLcode res;
	//char *url = "localhost://";
	//char outfilename[FILENAME_MAX] = "C:/Users/kjwii/Documents/TestCurlFile/texturePack.zip";
	curl = curl_easy_init();
	if (curl)
	{
		if ((fp = fopen(outfilename, "wb")) == NULL)
			std::cout << "Error open file" << std::endl;
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}
}