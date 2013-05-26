CPPFLAGS := -g

all : libhtmlparser.a

libhtmlparser.a : Node.o ParserDom.o ParserSax.o HtmlParser.o 
	ar r $@ $^
HtmlParser.o : HtmlParser.cpp
	g++ -c $^ -o $@ $(CPPFLAGS)
Node.o : Node.cpp
	g++ -c $^ -o $@ $(CPPFLAGS)
ParserDom.o : ParserDom.cpp
	g++ -c $^ -o $@ $(CPPFLAGS)
ParserSax.o : ParserSax.cpp
	g++ -c $^ -o $@ $(CPPFLAGS)

clean:
	rm -rf *.o
	rm -rf *.a
