CPPFLAGS := -c
CC := g++
AR := ar r

SOURCES := json_reader.cpp json_value.cpp json_writer.cpp

.PHONY : all clean

all : libjson.a

libjson.a : $(SOURCES:.cpp=.o)
	$(AR) $(OUTPUT_DIR)/$@ $^
%.o : %.cpp
	$(CC) $(CPPFLAGS) $^ -o $@

clean:
	rm -rf *.o
