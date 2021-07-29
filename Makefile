CXX=clang++
CXXFLAGS=-std=c++11 -I.
DEPS = httplib.h

all: server client

server: server.o	
	$(CXX) server.o -o server $(CXXFLAGS)

client: client.o	
	$(CXX) client.o -o client $(CXXFLAGS)

*.o: *.cpp $(DEPS)
	$(CXX) -c *.cpp $(CXXFLAGS)
	
clean: 
	rm *.o server client