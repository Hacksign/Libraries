#include "HtmlParser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/regex.hpp>

using namespace std;
HTML::HtmlParser::HtmlParser(const char* html){
	string tmp(html);
	mHtmlTree = parseTree(tmp);
}
HTML::HtmlParser::HtmlParser(const string html){
	mHtmlTree = parseTree(html);
}
HTML::HtmlParser::HtmlParser(const std::ifstream& file){
	std::stringstream out;
	out<<file.rdbuf();
	mHtmlTree = parseTree(out.str());
}
HTML::HtmlParser HTML::HtmlParser::find_by_tag_name(const string tagName){
	string tmpHtml;
	for(tree< HTML::Node >::tree::iterator begin = mHtmlTree.begin(); begin != mHtmlTree.end() && mHtmlTree.is_valid(begin);){
		if(begin->isTag() && begin->tagName() == tagName){//get start tag
			walkTree(begin, tmpHtml);
			if(mHtmlTree.number_of_siblings(begin)) begin = mHtmlTree.next_at_same_depth(begin);
			else  break;
		}else ++begin;
	}
	return HTML::HtmlParser(tmpHtml);
}
string HTML::HtmlParser::get_html(){
	string tmpHtml;
	tree< HTML::Node >::iterator begin = mHtmlTree.begin();
	walkTree(begin, tmpHtml);
	return tmpHtml;
}
string HTML::HtmlParser::text(){
	string result;
	for(tree< HTML::Node >::iterator it = mHtmlTree.begin(); it != mHtmlTree.end(); ++it)
		if(!it->isTag() && !it->isComment())
			result += trim_copy(it->text());
	return result;
}
size_t HTML::HtmlParser::size(){
	tree< HTML::Node >::iterator it = mHtmlTree.begin();
	return mHtmlTree.number_of_children(it);
}
HTML::HtmlParser HTML::HtmlParser::find_by_attribute(const string& attr, const string& value){
	tree< HTML::Node >::iterator it = mHtmlTree.begin();
	string finalHtml;
	for(; it != mHtmlTree.end(); ++it){
		it->parseAttributes();
		pair<bool, string> t = it->attribute(attr);
		if(t.first && t.second == value){
			string html;
			walkTree(it, html);
			finalHtml.append(html);	
		}
	}
	return HTML::HtmlParser(finalHtml);
}
HTML::HtmlParser HTML::HtmlParser::find_by_attribute_regex(const string& attr, const string& regex){
	tree< HTML::Node >::iterator it = mHtmlTree.begin();
	string finalHtml;
	for(; it != mHtmlTree.end(); ++it){
		it->parseAttributes();
		pair<bool, string> t = it->attribute(attr);
		boost::regex r(regex);
		if(t.first && boost::regex_match(t.second, r)){
			string html;
			walkTree(it, html);
			finalHtml.append(html);	
		}
	}
	return HTML::HtmlParser(finalHtml);
}
string HTML::HtmlParser::attr(const string& attr){
	tree< HTML::Node >::iterator it = mHtmlTree.begin();
	for(; it != mHtmlTree.end(); ++it){
		it->parseAttributes();
		pair<bool, string> t = it->attribute(attr);
		if(t.first){
			return t.second;
		}
	}
	return string();
}
void HTML::HtmlParser::walkTree(tree< HTML::Node >::iterator it, string& result){
	result += it->text();
	for(int i = 0; i < mHtmlTree.number_of_children(it); ++i)
		walkTree(mHtmlTree.child(it, i), result);
	result += it->closingText();
}
HTML::HtmlParser HTML::HtmlParser::operator[](int index){
	string tmpHtml;
	tree< HTML::Node >::iterator it = mHtmlTree.begin();
	++it;//skip root node
	for(int i = 0; i < index; ++i) it = mHtmlTree.next_sibling(it);
	walkTree(it, tmpHtml);
	return HTML::HtmlParser(tmpHtml);
}
