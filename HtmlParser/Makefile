all : libhtmlparser.a

libhtmlparser.a : Node.o ParserDom.o ParserSax.o HtmlParser.o 
	ar r $@ $^
HtmlParser.o : HtmlParser.cpp
	g++ -c $^ -o $@
Node.o : Node.cpp
	g++ -c $^ -o $@
ParserDom.o : ParserDom.cpp
	g++ -c $^ -o $@
ParserSax.o : ParserSax.cpp
	g++ -c $^ -o $@

clean:
	rm -rf *.o
	rm -rf *.a
