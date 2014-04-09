#include "AppServer.h"
#include "stdlib.h"

using namespace std;

int main(int argc, char *argv[])
{
	int port = atoi(argv[1]);
	AppServer server(port);
	server.ListenOn();
	return 0;
}
