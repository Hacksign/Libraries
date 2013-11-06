## description:
	similar with perl's LWP::UserAgent which is used to send/receive package through a simpler way ;)
## dependence:
	libcurl boost
## usage:
```cpp
	UserAgent ua;
	string url = "http://www.google.com";
	ua.get(url.c_str());
	if(ua.status() == 200){
		cout<<ua.response();
		cout<<ua.header("Host:", ":");
	}
	ua.header("Cookie: xxxxx");
	ua.post(url.c_str(), "param1=111&param2=222");
```
