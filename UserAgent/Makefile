SOURCES := UserAgent.cpp

CC := g++
AR := ar r
CPPFLAGS := -c
INCLUDES :=

.PHONY : clean all

all : libuseragent.a

libuseragent.a : $(SOURCES:.cpp=.o)
	$(AR) $(OUTPUT_DIR)/$@ $^
%.o : %.cpp
	$(CC) $(CPPFLAGS) $^ -o $@ $(INCLUDES)

clean:
	rm -rf *.o
