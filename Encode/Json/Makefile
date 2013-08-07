INCLUDE_FLAG :=
LD_FLAG :=
LIBS :=

all : libjson.a

libjson.a : json_reader.o json_value.o json_writer.o
	ar r $@ $^
json_reader.o : json_reader.cpp
	g++ -c $^ -o $@	$(INCLUDE_FLAG)
json_value.o : json_value.cpp
	g++ -c $^ -o $@	$(INCLUDE_FLAG)
json_writer.o : json_writer.cpp
	g++ -c $^ -o $@	$(INCLUDE_FLAG)

clean:
	rm -rf *.o
	rm -rf *.a
