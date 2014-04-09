#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include <iostream>
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

class TCPClient
{
	private:
	  	int makeConnection (string ip, int port);
		string m_IP;
		int m_Port;
	
	public:
		int descriptor;
		/// Create TCPClient application and connect to `ip' @ `port'.
		TCPClient (string ip, int port);
		/// Create TCPClient with an existing descriptor. The beauty here is this can be used for unix sockets also.
		TCPClient (int fd);
		~TCPClient ();

		bool reconnect();
		bool isConnected();
		void closeConnection();
		int sendData (string data);
	};
#endif /* __TCP_CLIENT_H__ */
