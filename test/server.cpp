#include "TCPServer.h"

int main(int argc, char *argv[])
{
	TCPServer server(10000,20);
	server.ListenOn();
	return 0;
}
