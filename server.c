// Saumya Shah
// CSC 255
// Server code

#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define BUF_SIZE 50 
#define PORT 4455 
#define SA struct sockaddr 

// Chat function between client and server. 
void chat(int sockfd)
{
	char buff[BUF_SIZE];
	while(1) 
	{
		bzero(buff, BUF_SIZE);
		// reading and pritnting message from client		
		int num = read(sockfd, buff, sizeof(buff), 0);
		if (num == -1) {
			printf("error in reading");
			exit(1);
		}
		else if (num == 0) {
			printf("%s", buff);
			close(sockfd);
			exit(0);
		}
		printf("%s", buff);
	}
}

int main()
{
	int ss, ns, size;
	struct sockaddr_in servaddr, cli;

	// Creating a Server socket
	ss = socket(AF_INET, SOCK_STREAM, 0);
	if (ss == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	
	bzero(&servaddr, sizeof(servaddr));

	// Configuring IP, PORT 
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	

	// Binding server socket to given IP and PORT
	if ((bind(ss, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket binding failed...\n");
		exit(0);
	}
	

	// For server to listen from clients
	if ((listen(ss, 5)) != 0) {
		printf("Listening failed...\n");
		exit(0);
	}
	
	size = sizeof(cli);

	// Accept the data packet from client in new socket
	ns = accept(ss, (SA*)&cli, &size);
	if (ns < 0) {
		printf("server acccept failed...\n");
		exit(0);
	}

	
	// Function for chatting between client and server 
	chat(ns);

	// After chatting close the socket 
	close(ss);
	return 0;
}
