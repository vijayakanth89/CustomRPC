all:
	g++ test/appserver.cpp src/*.cpp -I ./include -o bin/appserver.o -lpthread
server:
	echo "server test."
	g++ src/*.cpp -I ./include test/server.cpp -o bin/server.o -lpthread
appserver:
	g++ test/appserver.cpp src/*.cpp -I ./include -o bin/appserver.o -lpthread
