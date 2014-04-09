#include "AppServer.h"

void AppServer::createNewClient(int fd)
{
	printf("fd: %p, thread_id: %lu\n", &fd,pthread_self());
	this->start(&fd);
	usleep(10);
}

void AppServer::run()
{
	int *d = (int*) thread_data;
	int fd = *d;
	ClientHandler client(fd);
	client.run();
}
