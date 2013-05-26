CPPFLAGS := -g

all : libuseragent.a

libuseragent.a : UserAgent.o
	ar r $@ $^
UserAgent.o : UserAgent.cpp
	g++ -c $^ -o $@ $(CPPFLAGS)

clean:
	rm -rf *.o
	rm -rf *.a
