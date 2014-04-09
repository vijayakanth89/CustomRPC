#include "TCPServer.h"

TCPServer::TCPServer(int port, int listen_q)
{
	int status = startServer( port, listen_q );
	if ( status < 0 ) {
		fprintf(stderr, "server connection is not established\n",__LINE__);
		exit(1);
	}
}

TCPServer::~TCPServer()
{
	close(descriptor);
}

int TCPServer::acceptClientConnection()
{
	int nClients = 0;
	while(1) {
		struct sockaddr_in client_address;
		unsigned int sockaddr_in_len = (sizeof(struct sockaddr_in));
		int clientId = accept4(descriptor, (struct sockaddr *) &client_address, &sockaddr_in_len, SOCK_CLOEXEC);
		if( clientId > 0 )
			createNewClient( clientId );
		else
			break;
		nClients++;
	}
	return nClients;
}

void TCPServer::ListenOn()
{
	while(1){
		acceptClientConnection();
	}
}

int TCPServer::startServer(int port, int listen_q)
{
	struct sockaddr_in serv_address;
	int check_ret;
	descriptor = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
	if(descriptor < 0) {
		cout << "unable to create socket: " << strerror(errno) << endl;
		descriptor = -1;
		return -1;
	}
	serv_address.sin_family = AF_INET;
	serv_address.sin_port = htons(port);
	serv_address.sin_addr.s_addr = INADDR_ANY;
	memset(&serv_address.sin_zero, '\0', 8);

	check_ret = bind(descriptor, (struct sockaddr *) &serv_address, sizeof(struct sockaddr));
	if( check_ret < 0 ) {
		cout << "unable to bind socket" << endl;
		descriptor = -1;
		return -1;
	}
	check_ret = listen(descriptor, listen_q);
	if(check_ret < 0) {
		close(descriptor);
		descriptor = -1;
		return -1;
	}
	return 0;
}
