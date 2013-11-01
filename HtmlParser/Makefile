CPPFLAGS := -c
CC := g++
AR := ar r

SOURCES := HtmlParser.cpp ParserDom.cpp ParserSax.cpp

.PHONY : all clean

all : libhtmlparser.a

libhtmlparser.a : $(SOURCES:.cpp=.o)
	$(AR) $(OUTPUT_DIR)/$@ $^
%.o : %.cpp
	$(CC) $(CPPFLAGS) $^ -o $@

clean:
	rm -rf *.o
