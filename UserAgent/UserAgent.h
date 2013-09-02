#ifndef _CURL_H_
#define _CURL_H_
#include <curl/curl.h>
#include <stdarg.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
class UserAgent{
	public:
		UserAgent();
		virtual ~UserAgent();
	//public functions
	public:
		CURLcode post(const char * url,const char * content);
		CURLcode post(const char * url,const char * content, const char * filename);//for upload file use
		CURLcode post(const char * url,const char * content, const char * filename, void* buffer, size_t buffer_size);//for upload file use
		CURLcode get(const char * url);
		string header(const char *, const char *);
		void debug(bool);
		void timeout(unsigned long);
		void connection_timeout(unsigned long);
		struct curl_slist * header(const char *);
		const char * header();
		long status();
		string response(void);
		void proxy(const char *proxy, curl_proxytype type = CURLPROXY_HTTP,  const char *user = NULL, const char * pwd = NULL);


	//private functions
	private:
		static size_t header_callback( void *ptr, size_t size, size_t nmemb, std::string *userdata);
		static size_t write_callback( void *ptr, size_t size, size_t nmemb, std::string *response);
	//private varibales
	private:
		CURL *curl;
		struct curl_slist *list;
		std::string headerInfo;
		std::string responseInfo;

	protected:
};
#endif
