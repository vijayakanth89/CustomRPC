#include "TCPClient.h"

TCPClient::TCPClient(string ip, int port)
{
	m_IP.append( ip );
	m_Port = port;
	descriptor = makeConnection(ip, port);
}

TCPClient::TCPClient(int fd)
{
	descriptor = fd;
}

TCPClient::~TCPClient()
{
	closeConnection();
}

bool TCPClient::reconnect()
{
	descriptor = makeConnection( m_IP, m_Port );
	bool flag = isConnected();
	return flag;
}

int TCPClient::sendData(string data)
{
	data.append("\n");
	int s = write(descriptor, (void*) data.c_str(), data.length());
}

/* For non - blocking io
int TCPClient::readUntilDelimiter(string & data, char c_delimiter)
{
	int ret = 0;
	char c;
	while(1) {
		ret = read(descriptor, &c, 1);
		if( (ret < 1) || (c == c_delimiter) )
			break;
		data.append(&c, 1);
	}
	return ret;
}
*/

bool TCPClient::isConnected()
{
	return (descriptor > 0);
}

int TCPClient::makeConnection(string ip, int port)
{
	struct sockaddr_in serv_addr;
	unsigned long hostAddr;

	hostAddr = inet_addr(ip.c_str());
	if(hostAddr == INADDR_NONE) {
		hostent *hp = gethostbyname(ip.c_str());
		if(!hp) return -1;
		hostAddr = ((in_addr*)(hp->h_addr))->s_addr;
	}
	
	memset(&serv_addr, '\0', sizeof(serv_addr));
	//bzero((char *)&serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = hostAddr;
	serv_addr.sin_port = htons(port);

#if ((__GLIBC__ == 2 && __GLIBC_MINOR__ >= 10) \
    || (__GLIBC__ >= 3 && __GLIBC_MINOR__ >= 0)) \
    && defined SOCK_CLOEXEC
	int fd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC , 0);
#else
	int fd = socket(AF_INET, SOCK_STREAM, 0);
#endif
	if(fd <= 0) return -1;
	if(connect(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		close(fd);
		return -1;
	}
	cout << "Connected to channel" << endl;
	return fd;
}

void TCPClient::closeConnection()
{
	if( descriptor > 2 ) 
		close( descriptor );
	descriptor = -1;
}
