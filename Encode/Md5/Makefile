CPPFLAGS := -c
CC := g++
AR := ar r
INCLUDES :=

SOURCES := Md5.cpp

.PHONY : all clean

all : libmd5.a

libmd5.a : $(SOURCES:.cpp=.o)
	$(AR) $(OUTPUT_DIR)/$@ $^
%.o : %.cpp
	$(CC) $(CPPFLAGS) $^ -o $@ $(INCLUDES)

clean:
	rm -rf *.o
