CXX=clang++
CXXFLAGS=-std=c++11 -I.
DEPS = httplib.h json.hpp errors.h

all: server client

server: server.o Game.o Board.o Pawn.o
	$(CXX) $^ -o server $(CXXFLAGS)

client: client.o clientClass.o Board.o Pawn.o
	$(CXX) $^ -o client $(CXXFLAGS)

*.o: *.cpp $(DEPS)
	$(CXX) -c *.cpp $(CXXFLAGS)
	
clean: 
	rm *.o server client