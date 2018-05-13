#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

#include <HashGeneratorServer.hpp>

using namespace std;


int main(int argc, char* argv[])
{
	// int fd_epoll = 0;
	// bool test = true;

	// if (fd_epoll)
	// {
	// 	fprintf(stderr, "epoll_create() was failed..\n");
	// 	return -1;
	// }

	HashGeneratorServer* generator = new HashGeneratorServer("127.0.0.1");

	std::cout << "test" << endl;
	// [](){std::cout << "Hello world" << endl;}();
	
	return 0;
}











