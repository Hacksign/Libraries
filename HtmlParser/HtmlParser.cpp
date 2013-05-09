#include "HtmlParser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/regex.hpp>

using namespace std;
Spider::HtmlParser::HtmlParser(const char* html){
	string tmp(html);
	HTML::ParserDom parser;
	mHtml = parser.parseTree(tmp);
}
Spider::HtmlParser::HtmlParser(const string html){
	HTML::ParserDom parser;
	mHtml = parser.parseTree(html);
}
Spider::HtmlParser::HtmlParser(const std::ifstream& file){
	std::stringstream out;
	out<<file.rdbuf();
	HTML::ParserDom parser;
	mHtml = parser.parseTree(out.str());
}
Spider::HtmlParser Spider::HtmlParser::find_by_tag_name(const string tagName){
	string tmpHtml;
	for(tree< HTML::Node >::tree::iterator begin = mHtml.begin(); begin != mHtml.end() && mHtml.is_valid(begin); ++begin){
		if(begin->isTag() && begin->tagName() == tagName){//get start tag
			walkTree(begin, tmpHtml);
			if(mHtml.number_of_siblings(begin)) begin = mHtml.next_at_same_depth(begin);
			else break;
		}
	}
	return Spider::HtmlParser(tmpHtml);
}
string Spider::HtmlParser::get_html(){
	string tmpHtml;
	tree< HTML::Node >::iterator begin = mHtml.begin();
	walkTree(begin, tmpHtml);
	return tmpHtml;
}
string Spider::HtmlParser::text(){
	string result;
	for(tree< HTML::Node >::iterator it = mHtml.begin(); it != mHtml.end(); ++it)
		if(!it->isTag() && !it->isComment())
			result += trim_copy(it->text());
	return result;
}
size_t Spider::HtmlParser::size(){
	tree< HTML::Node >::iterator it = mHtml.begin();
	++it;//skip root node
	return mHtml.number_of_siblings(it) + 1;
}
Spider::HtmlParser Spider::HtmlParser::find_by_attribute(const string& attr, const string& value){
	tree< HTML::Node >::iterator it = mHtml.begin();
	++it;//skip root node;
	string finalHtml;
	for(; it != mHtml.end(); ++it){
		it->parseAttributes();
		pair<bool, string> t = it->attribute(attr);
		if(t.first && t.second == value){
			string html;
			walkTree(it, html);
			finalHtml.append(html);	
		}
	}
	return Spider::HtmlParser(finalHtml);
}
Spider::HtmlParser Spider::HtmlParser::find_by_attribute_regex(const string& attr, const string& regex){
	tree< HTML::Node >::iterator it = mHtml.begin();
	++it;//skip root node;
	string finalHtml;
	for(; it != mHtml.end(); ++it){
		it->parseAttributes();
		pair<bool, string> t = it->attribute(attr);
		boost::regex r(regex);
		if(t.first && boost::regex_match(t.second, r)){
			string html;
			walkTree(it, html);
			finalHtml.append(html);	
		}
	}
	return Spider::HtmlParser(finalHtml);
}
Spider::HtmlParser Spider::HtmlParser::attr(const string& attr){
	tree< HTML::Node >::iterator it = mHtml.begin();
	++it;//skip root node;
	string finalHtml;
	for(; it != mHtml.end(); ++it){
		it->parseAttributes();
		pair<bool, string> t = it->attribute(attr);
		if(t.first){
			string html;
			walkTree(it, html);
			finalHtml.append(html);
		}
	}
	return Spider::HtmlParser(finalHtml);
}
void Spider::HtmlParser::walkTree(tree< HTML::Node >::iterator it, string& result){
	result += it->text();
	for(int i = 0; i < mHtml.number_of_children(it); ++i)
		walkTree(mHtml.child(it, i), result);
	result += it->closingText();
}
Spider::HtmlParser Spider::HtmlParser::operator[](int index){
	string tmpHtml;
	tree< HTML::Node >::iterator it = mHtml.begin();
	++it;//skip root node
	for(int i = 0; i < index; ++i) it = mHtml.next_sibling(it);
	walkTree(it, tmpHtml);
	return Spider::HtmlParser(tmpHtml);
}
