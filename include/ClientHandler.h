#include "TCPClient.h"
#include "Buffer.h"
#include <map>

class ClientHandler:
	public TCPClient,
	public Buffer
{
	public:
		ClientHandler(int fd);
		~ClientHandler();
		void run(); 
		void handleBufferedData(string data);
		void Factorial(string num1, string &result);
		void Sum(string num1,string num2, string &result);
		bool SwitchService(map<string,string> params );
};
