#include "ClientHandler.h"

ClientHandler::ClientHandler(int fd):TCPClient(fd),Buffer::Buffer('#')
{
}

ClientHandler::~ClientHandler()
{
}

void ClientHandler::run()
{
	while(1){
		char buffer[1000] = {0};
		int st = recv(descriptor,buffer,1000, 0 );
		if( st > 0){
			this->receive_data(buffer,st );
		} else if (st < 0 ) {
			break;
		}
	}
}

void ClientHandler::handleBufferedData( string request ) 
{
	request.append("|");
	map<string,string> params;
	string::iterator iter_b = request.begin();

	string buffer("");
	string key("");
	string value("");

	while(iter_b != request.end()){
		char ch = *iter_b;
		if (ch == '='){
			key = buffer;
			buffer.clear();
		} else if (ch == '|') {
			value = buffer;
			buffer.clear();
			if ((!key.empty()) && (!value.empty())){
				params.insert(make_pair(key,value));
			}
		} else {
			buffer.append(&ch,1);
		}

		iter_b++;
	}
	if (params.size() == 0){
		this->sendData("invalid params");
	} else {
		SwitchService(params);
	}
}
bool ClientHandler::SwitchService(map<string,string> params ) 
{
	map<string,string>::iterator iter_params = params.begin();

	if (strcasecmp(iter_params->first.c_str(), "func") == 0 ) {
		if (strcasecmp(iter_params->second.c_str(), "sum") == 0 ) {

			iter_params = params.find("num1");
			string num1,num2;

			if (iter_params == params.end()){
				this->sendData(string("error=invalid params#"));
				return false;
			} else {
				num1 = iter_params->second;
			}
			
			iter_params = params.find("num2");

			if (iter_params == params.end()){
				this->sendData(string("error=invalid params#"));
				return false;
			} else {
				num2 = iter_params->second;
			}

			string res("");
			this->Sum(num1,num2,res);
			this->sendData("result="+res+"#");
		} else if (strcasecmp(iter_params->second.c_str(), "factorial") == 0 ){
			iter_params = params.find("num1");
			string num1;
			if (iter_params == params.end()){
				this->sendData(string("error=invalid params#"));
				return false;
			} else {
				num1 = iter_params->second;
			}

			string res("");
			this->Factorial(num1,res);
			this->sendData("result="+res+"#");
		}
	}
}

void ClientHandler::Sum(string num1, string num2, string &res ) 
{
	int64_t sum = atoi(num1.c_str() ) + atoi(num2.c_str());

	char buf[1000] = {0};
	sprintf(buf,"%ld",sum);
	res.append( string(buf));
}

void ClientHandler::Factorial(string num1, string &res ) 
{
	int n = atoi(num1.c_str());	

	if (n > 20){
		res = "Number too large";
	} else {
		int64_t f = 1;
		while(n--){
			if (n != 0) f*= n;
		}

		char buf[10000] = {0};
		sprintf(buf, "%ld",f ) ;
		res = string(buf);
	}
}
