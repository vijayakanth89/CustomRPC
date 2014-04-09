#ifndef __TCP_SERVER_H
#define __TCP_SERVER_H

#include <iostream>
#include <sys/types.h>
#include <fcntl.h>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>


using namespace std;

class TCPServer 
{

        public:
                TCPServer (int port, int listen_q = FD_SETSIZE);
                ~TCPServer ();

                int getDescriptor();

                int acceptClientConnection();
                virtual void createNewClient(int fd) {}
		void ListenOn();

        private:
                int startServer (int port, int listen_q);
		int descriptor;
};
#endif
