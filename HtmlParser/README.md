## description:
	a library to parse html content
## dependence:
	boost
## usage:
```cpp
	#include "HtmlParser/HtmlParser.h"
	using namespace Spider;

	HtmlParser parser(output);//where output is an html string
	HtmlParser contents = parser.find_by_tag_name("dl");
	HtmlParser tds = contents.find_by_attribute("id", "email_show");
	for(int i = 0; i < tds.size(); ++i) cout<<tds[i].text()<<endl;
	tds.clear();
	tds = contents.find_by_attribute("id", "nameSpan");
	for(int i = 0; i < tds.size(); ++i) cout<<tds[i].text()<<endl;
	tds.clear();
	HtmlParser phone = parser.find_by_attribute_regex("id", "phoneTr\\d+");
	for(int i = 0; i < phone.size(); ++i) cout<<phone[i].text()<<endl;
```
