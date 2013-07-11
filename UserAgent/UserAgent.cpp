#include "UserAgent.h"
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

using namespace boost;

#ifndef foreach
#define foreach BOOST_FOREACH
#endif

UserAgent::UserAgent(){
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &headerInfo);
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, &header_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseInfo);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_callback);
	curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 0);
	list = NULL;
}
UserAgent::~UserAgent(){
	curl_easy_cleanup(curl);
}
void UserAgent::debug(bool debug){
	if(debug) curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	else curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
}
void UserAgent::timeout(unsigned long timeout_second){
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout_second);
}
void UserAgent::connection_timeout(unsigned long timeout_second){
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeout_second);
}
void UserAgent::proxy(const char *proxy, curl_proxytype type,  const char *user, const char * pwd){
	curl_easy_setopt(curl, CURLOPT_PROXY, proxy);
	switch(type){
		case CURLPROXY_HTTP:
			curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL,true);
			curl_easy_setopt(curl, CURLOPT_PROXYTYPE,CURLPROXY_HTTP);
		break;
		case CURLPROXY_SOCKS4:
			curl_easy_setopt(curl, CURLOPT_PROXYTYPE,CURLPROXY_SOCKS4);
		break;
		case CURLPROXY_SOCKS5:
			curl_easy_setopt(curl, CURLOPT_PROXYTYPE,CURLPROXY_SOCKS5);
		break;
	}
}
CURLcode UserAgent::post(const char * url, const char * content){
	headerInfo.clear();
	responseInfo.clear();
	if(strstr(url,"https://")){
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST,0L);
	}
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_POST,1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
	CURLcode c = curl_easy_perform(curl);
	if(list){
		curl_slist_free_all(list);
		list = NULL;
	}
	return c;
} 
CURLcode UserAgent::get(const char *url){
	headerInfo.clear();
	responseInfo.clear();

	if(strstr(url,"https://")){
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST,0L);
	}
	curl_easy_setopt(curl, CURLOPT_URL, url);
	CURLcode c = curl_easy_perform(curl);
	if(list){
		curl_slist_free_all(list);
		list = NULL;
	}
	return c;
}
size_t UserAgent::header_callback( void *ptr, size_t size, size_t nmemb, std::string *userdata){
	userdata->append((const char *)ptr, size * nmemb);

	return size*nmemb;
}
size_t UserAgent::write_callback( void *ptr, size_t size, size_t nmemb, std::string *response){
	response->append((const char *)ptr, size * nmemb);

	return size*nmemb;
}
string UserAgent::response(){
	if(!headerInfo.empty())
		return trim_copy(responseInfo.substr(headerInfo.length(), responseInfo.length()));
	return responseInfo;
}
long UserAgent::status(){
	long statusCode;
	CURLcode r = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
	return statusCode;
}
const char * UserAgent::header(){
	trim(headerInfo);
	return headerInfo.c_str();
}
string UserAgent::header(const char * field, const char * char_used_to_join){
	vector<string> retVal;
	trim(headerInfo);
	vector<string> splited;
	split(splited, headerInfo, is_any_of("\n"));
	foreach(string line, splited)
		if(line.find(':') != string::npos){
			string search_str(line);
			to_lower(search_str);
			string field_lower_case(field);
			to_lower(field_lower_case);
			size_t index = search_str.find_first_of(":");
			size_t field_index = search_str.find(field_lower_case);
			if( field_index != string::npos && field_index < index ){
				string value(line.replace(0, index + 1, ""));
				trim(value);
				retVal.push_back(value);
			}
		}
	return join(retVal, char_used_to_join);
}
struct curl_slist * UserAgent::header(const char * header){
	list = curl_slist_append(list, header);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
}
