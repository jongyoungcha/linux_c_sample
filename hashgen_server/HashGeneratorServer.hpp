#ifndef __HASH_GENERATOR_SERVER_HPP__
#define __HASH_GENERATOR_SERVER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
// #include <sys/epoll.h>
#include <netinet/in.h>

#include <iostream>
#include <string>

using namespace std;

class HashGeneratorServer{
private:
protected:
	// mutable
	int Initialize();
	int StartListen();
	int Accept(int);

	// inmutable
	int Connect();
public:
	HashGeneratorServer(const char * server_ip);
	virtual ~HashGeneratorServer();
};
	

#endif


