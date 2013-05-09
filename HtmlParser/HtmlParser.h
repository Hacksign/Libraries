#ifndef _Spider_HTML_H_
#define _Spider_HTML_H_

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include "ParserDom.h"

#define foreach BOOST_FOREACH

using namespace std;
using namespace htmlcxx;
using namespace boost;

namespace Spider{
	class HtmlParser{
		public: //construct declare
			explicit HtmlParser(const char *);
			explicit HtmlParser(const string);
			explicit HtmlParser(const ifstream &);
		public: //member function declare
			string get_html();
			string text();
			size_t size();
			Spider::HtmlParser find_by_tag_name(const string);
			Spider::HtmlParser find_by_attribute(const string&, const string&);
			Spider::HtmlParser find_by_attribute_regex(const string&, const string&);
			Spider::HtmlParser attr(const string&);
			inline tree< HTML::Node >::iterator begin(){ return mHtml.begin(); }
			inline tree< HTML::Node >::iterator end(){ return mHtml.end(); }
		public: //operator overload
			Spider::HtmlParser operator[](int index);
			friend ostream & operator<<(ostream& stream, Spider::HtmlParser const& obj){
				for(tree< HTML::Node >::iterator it = const_cast<Spider::HtmlParser&>(obj).begin(); it != const_cast<Spider::HtmlParser&>(obj).end(); ++it){
					stream<<trim_copy(it->text())<<endl;
				}
				return stream;
			}
		private:
			tree< HTML::Node > mHtml;
			void walkTree(tree< HTML::Node >::iterator, string&);
	};
}
#endif
