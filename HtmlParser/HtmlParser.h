#ifndef _HTML_H_
#define _HTML_H_

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include "ParserDom.h"

#define foreach BOOST_FOREACH

using namespace std;
using namespace boost;

namespace HTML{
	class HtmlParser : public HTML::ParserDom {
		public: //construct declare
			explicit HtmlParser(const char *);
			explicit HtmlParser(const string);
			explicit HtmlParser(const ifstream &);
		public: //member function declare
			string get_html();
			string text();
			size_t size();
			HTML::HtmlParser find_by_tag_name(const string);
			HTML::HtmlParser find_by_attribute(const string&, const string&);
			HTML::HtmlParser find_by_attribute_regex(const string&, const string&);
			string attr(const string&);
			inline tree< HTML::Node >::iterator begin(){ return mHtmlTree.begin(); }
			inline tree< HTML::Node >::iterator end(){ return mHtmlTree.end(); }
		public: //operator overload
			HTML::HtmlParser operator[](int index);
			friend ostream & operator<<(ostream& stream, HTML::HtmlParser const& obj){
				for(tree< HTML::Node >::iterator it = const_cast<HTML::HtmlParser&>(obj).begin(); it != const_cast<HTML::HtmlParser&>(obj).end(); ++it){
					stream<<trim_copy(it->text())<<endl;
				}
				return stream;
			}
		private:
			void walkTree(tree< HTML::Node >::iterator, string&);
	};
}
#endif
