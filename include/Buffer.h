#include <iostream>
#include <stdlib.h>
using namespace std;

class Buffer:
	public string
{
	public:
		Buffer(char delimiter);
		~Buffer();

		void receive_data(void *data, size_t len ) ;
		virtual void handleBufferedData( string data ){
			cout << "data: " << data << endl;
		};
		char delim;
};
