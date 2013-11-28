CPPFLAGS := -c
CC := g++
AR := ar r
INCLUDES :=

SOURCES := HtmlParser.cpp ParserDom.cpp ParserSax.cpp Node.cpp

.PHONY : all clean

all : libhtmlparser.a

libhtmlparser.a : $(SOURCES:.cpp=.o)
	$(AR) $(OUTPUT_DIR)/$@ $^
%.o : %.cpp
	$(CC) $(CPPFLAGS) $^ -o $@ $(INCLUDES)

clean:
	rm -rf *.o
