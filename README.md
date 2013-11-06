Libraries
====================
	Encode/Base64 : provide base64 encode & decode.
	Encode/Jsonpp : json cpp class which could parse json data or tranlate data to json format.
	UserAgent			:	something like perl's LWP::UserAgent.
									based on libcurl/boost
	HtmlParser		:	a HTML parser.
									based on boost
	BoostThreadPool:a Thread Pool of boost
									based on boost

##Install:
```bash
	git clone https://github.com/Hacksign/Libraries
	cd Libraries
	make
```
	* NOTE:
	Some of the libs such as UserAgent are based on other library.So you need make sure your lib file is located in your $PATH, otherwise you can add the path in Makefile within $(INCLUDES) variable.
	For example,when compiling UserAgent on Windows, my boost and libcurl are located in 'D:\libs\boost' & 'D:\libs\curl',so add this line to UserAgent/Makefile:
```bash
		INCLUDES := -ID:\libs\boost -ID:\libs\curl
```
	Then rerun make in Libraries directory.

##License:
	Copyright (c) 2013 Hacksign (http://www.hacksign.cn)
	Forbidden for any commercial use.
	Any none-commercial use must be AUTHORIZED.
