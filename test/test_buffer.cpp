#include "Buffer.h"

int main(int argc, char *argv[])
{
	char d = 0; 
	Buffer buffer('#');
	while(1){
		d = random()%255;
		if (d == '#' || (d > 'A' && d < 'z'))
			buffer.receive_data(&d,1);
		usleep(4);
	}
	return 0;
}	
