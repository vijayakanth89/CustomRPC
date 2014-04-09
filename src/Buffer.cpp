#include "Buffer.h"
Buffer::Buffer(char _delmitter ) 
{
	delim = _delmitter;
}

Buffer::~Buffer()
{
}

void Buffer::receive_data(void *data, size_t len ) 
{
	char *d = (char*) data;

	while(len--){
		if (*d == delim ) {
			this->handleBufferedData((string)(*this));
			this->clear();
		} else if (*d == '\r'){
		} else if (*d == '\n'){
		} else {
			this->append(d,1);
		}
		d++;
	}

}
