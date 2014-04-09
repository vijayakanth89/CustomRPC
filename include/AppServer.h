#include <stdio.h>
#include <stdint.h>
#include "Thread.h"
#include "TCPServer.h"
#include "ClientHandler.h"

class AppServer:
	public TCPServer,
	public Thread
{
	public:
		AppServer(int port):TCPServer(port, 1000)
		{
		}
		~AppServer(){}

		void Sum(string num1, string num2, string &res ) ;
		void Factorial(string num1, string &res ) ;
		void createNewClient(int fd);
		void run();
};
